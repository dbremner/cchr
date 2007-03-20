/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| gio.c - guard iteration order optimizer                                    |
| written by Pieter Wuille                                                   |
\****************************************************************************/

#include <stdint.h>
#include <stdlib.h>

#include "gio.h"
#include "alist.h"

void static gio_entry_init(gio_entry_t *entry, gio_type_t type) {
  entry->type=type;
  if (type==GIO_TYPE_IDXITER) {
    alist_init(entry->data.idxiter.argp);
    alist_init(entry->data.idxiter.args);
  }
}

void static gio_entry_destruct(gio_entry_t *entry) {
  if (entry->type==GIO_TYPE_IDXITER) {
    alist_free(entry->data.idxiter.argp);
    alist_free(entry->data.idxiter.args);
  }
}

void gio_init(gio_t *gio) {
  alist_init(gio->order);
}

void gio_destruct(gio_t *gio) {
  for (int i=0; i<alist_len(gio->order); i++) {
    gio_entry_destruct(alist_ptr(gio->order,i));
  }
  alist_free(gio->order);
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
        sem_cdeps_t *cdp=&(alist_get(rule->out[0],p).cdeps);
	int cont=1;
	for (int c=0; c<alist_len(cdp->co); c++) {
	  int search=alist_get(cdp->co,c);
	  int found=0;
	  for (int k=0; k<n; k++) {
	    if (search==order[k]) {found=1; break;}
	  }
	  if (!found) {cont=0;break;}
	}
	if (cont) {
	  gd[p]=0;
	  gio_entry_t entry;
	  gio_entry_init(&entry,GIO_TYPE_OUT);
	  entry.data.out=p;
	  alist_add(out->order,entry);
	}
      }
    }
    if (n<size) {
      gio_entry_t entry;
      gio_entry_init(&entry,GIO_TYPE_ITER);
      entry.data.iter.cot=order[n];
      alist_add(out->order,entry);
    }
    n++;
  } while(n<=size);
}

double static gio_score(sem_cchr_t *chr, sem_rule_t *rule, gio_t *gio) {
  return 1.0;
}

void static gio_iterate(sem_cchr_t *chr, sem_rule_t *rule, uint32_t *order, int *used, int left, gio_t *out, double *score) {
  if (left==0) {
    gio_t ngio;
    gio_init(&ngio);
    gio_genorder(chr,rule,order,&ngio);
    double nscr=gio_score(chr,rule,&ngio);
    if (nscr<*score) {
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
    for (int s=0; s<alist_len(rule->head[p ? SEM_RULE_LEVEL_REM : SEM_RULE_LEVEL_KEPT]); s++) {
      if (!used[k]) {
        used[k]=1;
	order[left-1]=s+(p<<31);
	gio_iterate(chr,rule,order,used,left-1,out,score);
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
  order[size-1]=activ;
  double score=1.0/0.0;
  gio_iterate(chr,rule,order,used,size-1,gio,&score);
  return;
}
