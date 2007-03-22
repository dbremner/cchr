/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| gio.c - guard iteration order optimizer                                    |
| written by Pieter Wuille                                                   |
\****************************************************************************/

#include <stdint.h>
#include <stdlib.h>

#include "gio.h"
#include "analyse.h"
#include "alist.h"

int static gio_test_idxeq(sem_rule_t *rule, int cot, int rem, sem_expr_t *expr, gio_entry_t *gioe);

void static gio_entry_init(gio_entry_t *entry, gio_type_t type) {
  entry->type=type;
  if (type==GIO_TYPE_IDXITER) {
    alist_init(entry->data.idxiter.args);
  }
}

void static gio_entry_destruct(gio_entry_t *entry) {
  if (entry->type==GIO_TYPE_IDXITER) {
    alist_free(entry->data.idxiter.args);
  }
}

void static gio_init(gio_t *gio) {
  alist_init(gio->order);
}

void gio_destruct(gio_t *gio) {
  for (int i=0; i<alist_len(gio->order); i++) {
    gio_entry_destruct(alist_ptr(gio->order,i));
  }
  alist_free(gio->order);
}

int static gio_checkcdep(uint32_t *order, int n, sem_cdeps_t *cdp) {
  for (int c=0; c<alist_len(cdp->co); c++) {
    int search=alist_get(cdp->co,c);
    int found=0;
    for (int k=0; k<n; k++) {
      if (search==order[k]) {found=1; break;}
    }
    if (!found) return 0;
  }
  return 1;
}

void static gio_genorder(sem_cchr_t *chr, sem_rule_t *rule, uint32_t *order, gio_t *out) {
  int size=alist_len(rule->head[SEM_RULE_LEVEL_REM])+alist_len(rule->head[SEM_RULE_LEVEL_KEPT]);
  int n=1;
  int nguards=alist_len(rule->out[0]);
  int *gd=malloc(sizeof(int)*nguards);
  for (int i=0; i<nguards; i++) gd[i]=1;
  do {
    for (int p=0; p<nguards; p++) {
      if (gd[p]) {
	if (gio_checkcdep(order,n,&(alist_get(rule->out[0],p).cdeps))) {
	  gd[p]=0;
	  gio_entry_t entry;
	  gio_entry_init(&entry,GIO_TYPE_OUT);
	  entry.data.out=p;
	  alist_add(out->order,entry);
	}
      }
    }
    if (n<size) {
      uint32_t cot=order[n];
      int rem=0;
      if (cot & (1<<31)) {
        cot ^= (1<<31);
	rem=1;
      }
      sem_conocc_t *co=alist_ptr(rule->head[rem ? SEM_RULE_LEVEL_REM : SEM_RULE_LEVEL_KEPT],cot);
      gio_entry_t entry;
      gio_entry_init(&entry,GIO_TYPE_IDXITER);
      entry.data.idxiter.cot=order[n];
      alist_ensure(entry.data.idxiter.args,alist_len(co->args));
      int haveidx=0;
      for (int i=0; i<alist_len(co->args); i++) alist_add(entry.data.idxiter.args,NULL);
      for (int g=0; g<nguards; g++) { /* loop over all guards */
        if (gd[g]) { /* if this particular guard is still to be checked */
	  sem_out_t *sot=alist_ptr(rule->out[0],g);
	  if (sot->type==SEM_OUT_TYPE_EXP) { /* if it is a real guard (not a var or stm) */
	    if (gio_checkcdep(order,n+1,&(sot->cdeps))) { /* and we have all prerequisites */
	      if (gio_test_idxeq(rule,cot,rem,&(sot->data.exp),&entry)) {
	        gd[g]=0;
		haveidx=1;
	      }
	    }
	  }
	}
      }
      if (!haveidx) { /* no indices used, use normal (linked list) iterator */
        gio_entry_destruct(&entry);
	gio_entry_init(&entry,GIO_TYPE_ITER);
	entry.data.iter.cot=order[n];
      }
      alist_add(out->order,entry);
      for (int i=0; i<n; i++) { /* loop for DIFF's */
        uint32_t cot2=order[i];
	int rem2=0;
	if (cot2 & (1<<31)) {
	  cot2 ^= (1<<31);
	  rem=1;
	}
	sem_conocc_t *co2=alist_ptr(rule->head[rem2 ? SEM_RULE_LEVEL_REM : SEM_RULE_LEVEL_KEPT],cot2);
	if (co->constr == co2->constr) {
	  gio_entry_t entry2;
	  gio_entry_init(&entry2,GIO_TYPE_DIFF);
	  entry2.data.diff.cot[0]=order[i];
	  entry2.data.diff.cot[1]=order[n];
	  alist_add(out->order,entry2);
	}
      }
      for (int i=0; i<alist_len(co->args); i++) { /* so we go on, define variables from this conocc */
        gio_entry_t entry3;
	gio_entry_init(&entry3,GIO_TYPE_VAR),
	entry3.data.var=alist_get(co->args,i);
	alist_add(out->order,entry3);
      }
    }
    n++;
  } while(n<=size);
  free(gd);
}

int static gio_test_idxeq(sem_rule_t *rule, int cot, int rem, sem_expr_t *expr, gio_entry_t *gioe) {
  if (alist_len(expr->parts)!=1) return 0;
  sem_exprpart_t *ep=alist_ptr(expr->parts,0);
  if (ep->type==SEM_EXPRPART_TYPE_FUN) {
    if (!strcmp(ep->data.fun.name,"alt")) {
      for (int i=0; i<alist_len(ep->data.fun.args); i++) {
        if (gio_test_idxeq(rule,cot,rem,alist_ptr(ep->data.fun.args,i),gioe)) return 1;
      }
      return 0;
    }
    if (!strcmp(ep->data.fun.name,"eq") && alist_len(ep->data.fun.args)==2) {
      sem_expr_t *e[2];
      e[0]=alist_ptr(ep->data.fun.args,0);
      e[1]=alist_ptr(ep->data.fun.args,1);
      for (int k=0; k<2; k++) {
        if (alist_len(e[k]->parts)==1 && alist_get(e[k]->parts,0).type==SEM_EXPRPART_TYPE_VAR) {
	  int varid=alist_get(e[k]->parts,0).data.var;
	  sem_var_t *var=alist_ptr(rule->vt.vars,varid);
	  if (!var->local && var->occ[SEM_RULE_LEVEL_REM]==rem && var->pos==cot) {
	    alist_get(gioe->data.idxiter.args,var->poss)=e[1-k];
	    return 1;
	  }
	}
      }
      return 0;
    }
  }
  return 0;
}

double static gio_score(sem_cchr_t *chr, sem_rule_t *rule, gio_t *gio) {
  return 1.0;
}

void static gio_iterate(sem_cchr_t *chr, sem_rule_t *rule, uint32_t *order, int *used, int done, gio_t *out, double *score) {
  int sizeK=alist_len(rule->head[SEM_RULE_LEVEL_KEPT]);
  int sizeR=alist_len(rule->head[SEM_RULE_LEVEL_REM]);
  if (done==sizeK+sizeR) {
    gio_t ngio;
    gio_init(&ngio);
    gio_genorder(chr,rule,order,&ngio);
    double nscr=gio_score(chr,rule,&ngio);
    if ((*score)==0.0 || nscr<(*score)) {
      gio_destruct(out);
      *out=ngio;
      *score=nscr;
    } else {
      gio_destruct(&ngio);
    }
    return;
  }
  int k=0;
  for (int p=0; p<2; p++) {
    for (int s=0; s<(p?sizeR:sizeK); s++) {
      if (!used[k]) {
        used[k]=1;
	order[done]=s+(p<<31);
	gio_iterate(chr,rule,order,used,done+1,out,score);
	used[k]=0;
      }
      k++;
    }
  }
}

void gio_generate(sem_cchr_t *chr, sem_rule_t *rule, gio_t *gio, int activ) {
  int size=alist_len(rule->head[SEM_RULE_LEVEL_REM])+alist_len(rule->head[SEM_RULE_LEVEL_KEPT]);
  uint32_t *order=malloc(sizeof(uint32_t)*size);
  int *used=malloc(sizeof(int)*size);
  for (int i=0; i<size; i++) used[i]=0;
  int arem=0;
  int apos=activ;
  if (activ & 1<<31) {
    arem=1;
    apos = (apos ^ (1<<31)) + alist_len(rule->head[SEM_RULE_LEVEL_KEPT]);
  }
  used[apos]=1;
  order[0]=activ;
  double score=0.0;
  gio_init(gio);
  gio_iterate(chr,rule,order,used,1,gio,&score);
  return;
}
