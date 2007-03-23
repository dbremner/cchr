/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| codegen.c - Conversion of semantic tree to C output (using CSM)            |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "semtree.h"
#include "alist.h"
#include "output.h"
#include "gio.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

typedef struct {
  char *code;
  int use;
} csm_varuse_t;

typedef struct {
  alist_declare(int,list);
} csm_hashdef_t;

void static csm_hashdef_init(csm_hashdef_t *def) {
  alist_init(def->list);
}

void static csm_hashdef_destruct(csm_hashdef_t *def) {
  alist_free(def->list);
}

typedef struct {
  alist_declare(csm_hashdef_t,defs);
} csm_hashdefs_t;

void static csm_hashdefs_init(csm_hashdefs_t *hd) {
  alist_init(hd->defs);
}

void static csm_hashdefs_destroy(csm_hashdefs_t *hd) {
  for (int i=0; i<alist_len(hd->defs); i++) {
    csm_hashdef_destruct(alist_ptr(hd->defs,i));
  }
  alist_free(hd->defs);
}

/* will either destruct def, or add it to hd */
void static csm_hashdefs_add(csm_hashdefs_t *hd,csm_hashdef_t *def) {
  for (int k=0; k<alist_len(hd->defs); k++) {
    csm_hashdef_t *chk=alist_ptr(hd->defs,k);
    if (alist_len(chk->list) == alist_len(def->list)) {
      int ok=1;
      for (int l=0; l<alist_len(def->list); l++) {
        if (alist_get(chk->list,l) != alist_get(def->list,l)) { ok=0; break; }
      }
      if (ok) {
        csm_hashdef_destruct(def);
	return;
      }
    }
  }
  alist_add(hd->defs,*def);
}

char static *csm_hashdef_strify(csm_hashdef_t *def) {
  char *ret=malloc(4+(alist_len(def->list)+4)/5);
  strcpy(ret,"idx");
  char hex[]="0123456789ABCDEFGHIJKLMNOPQRSTUV";
  for (int i=0; i<(alist_len(def->list)+4)/5; i++) {
    int dig=0;
    for (int k=5*i; k<5*(i+1); k++) {
      if (k<alist_len(def->list)) {
        dig=2*dig+!!alist_get(def->list,k);
      }
    }
    ret[i+3]=hex[dig];
    ret[i+4]=0;
  }
  return ret;
}

/* do something sprintf-like, but put the output in a malloc'ed block */
char static *make_message(const char *fmt, ...) {
  int n, size = 100;
  char *p, *np;
  va_list ap;
  if ((p = malloc (size)) == NULL) return NULL;
  while (1) {
    va_start(ap, fmt);
    n = vsnprintf (p, size, fmt, ap);
    va_end(ap);
    if (n > -1 && n < size) return p;
    if (n > -1) {
      size = n+1;
    } else {
      size *= 2;
    }
    if ((np = realloc (p, size)) == NULL) {
      free(p);
      return NULL;
    } else {
      p = np;
    }
  }
}

/* get output name for a constraint (put it in 'out' buffer) */
int static csm_constr_getname(sem_cchr_t *cchr,int cons,char *out,int size) {
  sem_constr_t *ptr=alist_ptr(cchr->cons,cons);
  return snprintf(out,size,"%s_%i",ptr->name,alist_len(ptr->types));
}

/* get output name for a rule (put it in 'out' buffer) */
int static csm_rule_getname(sem_cchr_t *cchr,int rule,char *out,int size) {
  sem_rule_t *ptr=alist_ptr(cchr->rules,rule);
  if (ptr->name) {
    return snprintf(out,size,"%s",ptr->name);
  } else {
    return snprintf(out,size,"%iR",rule+1);
  }
}

/* get output name for a constraint occurence (put it in 'out' buffer) */
int static csm_conocc_getname(sem_cchr_t *cchr,int cons,int occ,char *out,int size) {
  sem_constr_t *ptr=alist_ptr(cchr->cons,cons);
  int tsize=0;
  sem_ruleocc_t *ro=alist_ptr(ptr->occ,occ);
  tsize+=csm_constr_getname(cchr,cons,out+tsize,size-tsize);
  tsize+=snprintf(out+tsize,size-tsize,"_");
  tsize+=csm_rule_getname(cchr,ro->rule,out+tsize,size-tsize);
  tsize+=snprintf(out+tsize,size-tsize,"_%s%i",ro->type==SEM_RULE_LEVEL_REM ? "R" : "K",ro->pos+1);
  return tsize;
}

csm_varuse_t static *csm_generate_vartable_constr(sem_cchr_t *chr,int coni) {
  sem_constr_t *co=alist_ptr(chr->cons,coni);
  char c[256];
  csm_constr_getname(chr,coni,c,256);
  csm_varuse_t *tbl=malloc(sizeof(csm_varuse_t)*alist_len(co->types));
  for (int i=0; i<alist_len(co->types); i++) {
    tbl[i].code=make_message("_arg_%i",i+1);
    tbl[i].use=0;
  }
  return tbl;
}

/* generate variable-access table (array of char*'s, each pointing to the code to be used for accessing variable corresponding to array index) */ 
csm_varuse_t static *csm_generate_vartable_rule(sem_cchr_t *chr,sem_rule_t *rule,int arem,int aid) {
  csm_varuse_t *tbl=malloc(sizeof(csm_varuse_t)*alist_len(rule->vt.vars));
  for (int i=0; i<alist_len(rule->vt.vars); i++) {
    sem_var_t *var=alist_ptr(rule->vt.vars,i);
    if (var->local) { /* local variables are accessed as LOCAL's in CSM */
      tbl[i].code=make_message("CSM_LOCAL(%s)",var->name);
      tbl[i].use=0;
    } else { /* variable defined by head of rule */
      sem_rule_level_t isrem=var->occ[SEM_RULE_LEVEL_REM] ? SEM_RULE_LEVEL_REM : SEM_RULE_LEVEL_KEPT;
      int j=var->pos; /* what constraint occurrence in the rule defines it */
      sem_conocc_t *co=alist_ptr(rule->head[isrem],j);
      int k=var->poss; /* search which argument of that constraint defines it */
      char cona[256];
      csm_constr_getname(chr,co->constr,cona,256);
      if (arem==isrem && j==aid) { /* if this is the active rule, use ARG instead of LARG */
      	tbl[i].code=make_message("CSM_ARG(%s,arg%i)",cona,k+1);
        tbl[i].use=0;
      } else {
        tbl[i].code=make_message("CSM_LARG(%s,%s%i,arg%i)",cona,isrem ? "R" : "K",j+1,k+1);
	tbl[i].use=0;
      } 
    }
  }
  return tbl;
}

csm_varuse_t static *csm_generate_vartable_rule_cached(sem_cchr_t *chr,sem_rule_t *rule,int arem,int aid) {
  csm_varuse_t *tbl=malloc(sizeof(csm_varuse_t)*alist_len(rule->vt.vars));
  for (int i=0; i<alist_len(rule->vt.vars); i++) {
    sem_var_t *var=alist_ptr(rule->vt.vars,i);
    tbl[i].code=make_message("CSM_LOCAL(%s)",var->name);
    tbl[i].use=0;
  }
  return tbl;
}

/* nice destructor for the variable table */
void static csm_destruct_vartable_rule(sem_rule_t *rule,csm_varuse_t *tbl) {
  for (int u=0; u<alist_len(rule->vt.vars); u++) free(tbl[u].code);
  free(tbl);
}

/* nice destructor for the variable table */
void static csm_destruct_vartable_constr(sem_constr_t *con,csm_varuse_t *tbl) {
  for (int u=0; u<alist_len(con->types); u++) free(tbl[u].code);
  free(tbl);
}

/* generate code for an expression (as a C expression) */
void static csm_generate_expr(sem_expr_t *expr,csm_varuse_t *tbl,output_t *out) {
  int dos=0;
  for (int t=0; t<alist_len(expr->parts); t++) {
    if (dos) output_fmt(out," ");
    dos=1;
    sem_exprpart_t *ep=alist_ptr(expr->parts,t);
    char *str=ep->data.lit;
    switch (ep->type) {
      case SEM_EXPRPART_TYPE_LIT:
      case SEM_EXPRPART_TYPE_FUN: 
      str=ep->data.fun.name; {
        if (!strcmp(ep->data.lit,"}")) {output_unindent(out);dos=0;}
	output_fmt(out,"%s",str);
	if (!strcmp(ep->data.lit,"}")) {output_string(out," \\\n");}
	if (!strcmp(ep->data.lit,";")) {output_string(out," \\\n");dos=0;}
	if (!strcmp(ep->data.lit,"{")) {output_indent(out," \\","");dos=0;}
	break;
      }
      case SEM_EXPRPART_TYPE_VAR: {
        output_fmt(out,"%s",tbl[ep->data.var].code);
	tbl[ep->data.var].use++;
	break;
      }
    }
    if (ep->type==SEM_EXPRPART_TYPE_FUN) {
      output_string(out,"(");
      for (int i=0; i<alist_len(ep->data.fun.args); i++) {
        if (i) output_string(out,",");
        csm_generate_expr(alist_ptr(ep->data.fun.args,i),tbl,out);
      }
      output_string(out,")");
    }
  }
}

void static csm_generate_out(sem_cchr_t *chr,sem_rule_t *rule,csm_varuse_t *tbl,output_t *out,sem_out_t *so) {
  switch (so->type) {
    case SEM_OUT_TYPE_CON: {
      char coo[256];
      csm_constr_getname(chr,so->data.con.constr,coo,256);
      if (alist_len(so->data.con.args)==0) {
        output_fmt(out,"CSM_ADDE(%s) \\\n",coo);
      } else {
        output_fmt(out,"CSM_ADD(%s",coo);					
        for (int j=0; j<alist_len(so->data.con.args); j++) {
          output_fmt(out,",");
          csm_generate_expr(alist_ptr(so->data.con.args,j),tbl,out);
        }
        output_fmt(out,") \\\n");
      }
      break;
    }
    case SEM_OUT_TYPE_EXP: {
      output_fmt(out,"CSM_IF(");
      csm_generate_expr(&(so->data.exp),tbl,out);
      output_indent(out,", \\",") \\");
      break;
    }
    case SEM_OUT_TYPE_STM: {
      output_indent(out,"CSM_NATIVE( { \\","} ) \\\n");
      csm_generate_expr(&(so->data.exp),tbl,out);
      output_unindent(out);
      break;
    }
    case SEM_OUT_TYPE_VAR: {
      sem_var_t *var=alist_ptr(rule->vt.vars,so->data.var);
      if (alist_len(var->def.parts)>0) {
        output_fmt(out,"CSM_DEFLOCAL(%s,%s,",var->type,var->name);
        csm_generate_expr(&(var->def),tbl,out);
        output_fmt(out,") \\\n");
      } else {
        output_fmt(out,"CSM_DECLOCAL(%s,%s) \\\n",var->type,var->name);
      }
      break;
    }
  }
}

void static csm_generate_body(sem_cchr_t *chr,sem_rule_t *rule,csm_varuse_t *tbl,output_t *out) {
  int l=0;
  int *conocc_td=malloc(sizeof(int)*alist_len(rule->head[SEM_RULE_LEVEL_REM]));
  for (int j=0; j<alist_len(rule->head[SEM_RULE_LEVEL_REM]); j++) conocc_td[j]=1;
  while(1) {
    sem_out_t *so=alist_ptr(rule->out[1],l);
    for (int k=0; k<alist_len(rule->head[SEM_RULE_LEVEL_REM]); k++) { /* destruction of conocc's whose variables are completely used */
      sem_conocc_t *co=alist_ptr(rule->head[SEM_RULE_LEVEL_REM],k);
      char cc[256];
      csm_constr_getname(chr,co->constr,cc,256);
      int ok=conocc_td[k];
      int w=0;
      while (ok && w<alist_len(co->args)) {
        sem_var_t *var=alist_ptr(rule->vt.vars,alist_get(co->args,w));
        if (tbl[alist_get(co->args,w)].use != var->occ[SEM_RULE_LEVEL_BODY]+var->occ[SEM_RULE_LEVEL_GUARD]) ok=0;
        w++;
      }
      if (ok) {
        output_fmt(out,alist_len(co->args) ? "CSM_DESTRUCT(%s" : "CSM_DESTRUCTE(%s",cc);
        for (int l=0; l<alist_len(co->args); l++) {
          output_fmt(out,",%s",tbl[alist_get(co->args,l)].code);
        }
        output_fmt(out,") \\\n");
        conocc_td[k]=0;
      }
    }
    if (l==alist_len(rule->out[1])) break;
    csm_generate_out(chr,rule,tbl,out,so);
    l++;
  }
  free(conocc_td);
}

typedef struct {
  int constr;
  char *idxname;
  int rem;
  int pos;
} csm_idxclean_t;

/* generate codelist for a constraint occurence, using GIO */
void static csm_generate_code_gio(sem_cchr_t *cchr,int cons,int occ,output_t *out,csm_hashdefs_t *hd) {
  char buf[256];
  csm_conocc_getname(cchr,cons,occ,buf,256);
  char buf2[256];
  csm_constr_getname(cchr,cons,buf2,256);
  sem_constr_t *con=alist_ptr(cchr->cons,cons);
  sem_ruleocc_t *ro=alist_ptr(con->occ,occ);
  int rem=ro->type==SEM_RULE_LEVEL_REM;
  sem_rule_t *ru=alist_ptr(cchr->rules,ro->rule);
  char buf3[256];
  csm_rule_getname(cchr,ro->rule,buf3,256);
  sem_conocc_t *co=alist_ptr(ru->head[rem],ro->pos);

  gio_t gio;
  gio_generate(cchr,ru,&gio,ro->pos | (rem << 31));
  output_fmt(out,"\n");
  output_fmt(out,"#undef CODELIST_%s\n",buf);
  output_fmt(out,"#define CODELIST_%s ",buf);
  output_indent(out," \\","");
  if (!rem) {
    output_fmt(out,"CSM_MAKE(%s) \\\n",buf2);
  }
  csm_varuse_t *tbl=csm_generate_vartable_rule(cchr,ru,rem,ro->pos);
  csm_varuse_t *tbl_c=csm_generate_vartable_rule_cached(cchr,ru,rem,ro->pos);
  alist_declare(csm_idxclean_t,clean);
  alist_init(clean);
  for (int i=0; i<alist_len(co->args); i++) {
    int vid=alist_get(co->args,i);
    sem_var_t *var=alist_ptr(ru->vt.vars,vid);
    output_fmt(out,"CSM_IMMLOCAL(%s,%s,%s) \\\n",var->type,var->name,tbl[vid].code);
    tbl[vid].use=0;
    tbl_c[vid].use=0;
  }
  for (int i=0; i<alist_len(gio.order); i++) {
    gio_entry_t *entry=alist_ptr(gio.order,i);
    switch (entry->type) {
      case GIO_TYPE_ITER: {
	uint32_t cid=entry->data.iter.cot & (~(1<<31));
	int ci_rem=!!(entry->data.iter.cot & (1<<31));
	int cicon=alist_get(ru->head[ci_rem],cid).constr;
	char cicon_name[256];
	csm_constr_getname(cchr,cicon,cicon_name,256);
	output_fmt(out,"CSM_LOOP(%s,%s%i,",cicon_name,ci_rem ? "R" : "K",cid+1);
	output_indent(out," \\",") \\");
	break;
      }
      case GIO_TYPE_DIFF: {
	uint32_t cid[2];
	cid[0]=entry->data.diff.cot[0] & (~(1<<31));
	cid[1]=entry->data.diff.cot[1] & (~(1<<31));
	int crem[2];
	crem[0]=(entry->data.diff.cot[0] & (1<<31))!=0;
	crem[1]=(entry->data.diff.cot[1] & (1<<31))!=0;
	int si=-1;
	if (cid[0]==ro->pos && crem[0]==rem) si=0;
	if (cid[1]==ro->pos && crem[1]==rem) si=1;
	if (si>=0) {
	  output_fmt(out,"CSM_IF(CSM_DIFFSELF(%s%i),",crem[1-si] ? "R" : "K",cid[1-si]+1);
	} else {
	  output_fmt(out,"CSM_IF(CSM_DIFF(%s%i,%s%i),",crem[0] ? "R" : "K",cid[0]+1,crem[1] ? "R" : "K",cid[1]+1);
	}
	output_indent(out," \\",") \\");
	break;
      }
      case GIO_TYPE_VAR: {
        int vid=entry->data.var;
	sem_var_t *var=alist_ptr(ru->vt.vars,vid);
	output_fmt(out,"CSM_IMMLOCAL(%s,%s,%s) \\\n",var->type,var->name,tbl[vid].code);
	tbl[vid].use=0;
	tbl_c[vid].use=0;
        break;
      }
      case GIO_TYPE_OUT: {
        sem_out_t *so=alist_ptr(ru->out[0],entry->data.out);
	csm_generate_out(cchr,ru,tbl_c,out,so);
	break;
      }
      case GIO_TYPE_IDXITER: {
	uint32_t cid=entry->data.idxiter.cot & (~(1<<31));
	int ci_rem=!!(entry->data.idxiter.cot & (1<<31));
	int cicon=alist_get(ru->head[ci_rem],cid).constr;
	char cicon_name[256];
	csm_constr_getname(cchr,cicon,cicon_name,256);
	csm_hashdef_t def;
	csm_hashdef_init(&def);
	for (int i=0; i<alist_len(entry->data.idxiter.args); i++) {
	  sem_expr_t *exp=alist_get(entry->data.idxiter.args,i);
	  int ea=(exp!=NULL);
	  alist_add(def.list,ea);
	}
	char *idxname=csm_hashdef_strify(&def);
	output_fmt(out,"CSM_DEFIDXVAR(%s,%s,%s%i) \\\n",cicon_name,idxname,ci_rem ? "R" : "K",cid+1);
	for (int i=0; i<alist_len(entry->data.idxiter.args); i++) {
	  sem_expr_t *exp=alist_get(entry->data.idxiter.args,i);
	  if (exp) {
	    output_fmt(out,"CSM_SETIDXVAR(%s,%s,%s%i,arg%i,",cicon_name,idxname,ci_rem ? "R" : "K",cid+1,i+1);
	    csm_generate_expr(exp,tbl_c,out);
	    output_fmt(out,") \\\n");
	  }
	}
	output_fmt(out,"%s(%s,%s,%s%i,",(!rem) ? "CSM_IDXUNILOOP" : "CSM_IDXLOOP",cicon_name,idxname,ci_rem ? "R" : "K",cid+1);
	free(idxname);
	output_indent(out," \\",") \\");
	if (!rem) {
	  csm_idxclean_t cl;
	  cl.constr=cicon;
	  cl.idxname=csm_hashdef_strify(&def);
	  cl.rem=ci_rem;
	  cl.pos=cid;
	  alist_add(clean,cl);
	}
	csm_hashdefs_add(hd,&def);
	break;
      }
    }
  }
  char *end=NULL;
  int ncons=alist_len(ru->head[SEM_RULE_LEVEL_KEPT])+alist_len(ru->head[SEM_RULE_LEVEL_REM]);
  if (ru->hook>=0) {
    output_fmt(out,"CSM_HISTCHECK(%s",buf3);
    end=make_message("");
    for (int ci=0; ci<ncons; ci++) {
      if (ci==ro->pos) {
        char *nend=make_message("%s,self_",end); free(end); end=nend;
      } else {
        char *nend=make_message("%s,K%i",end,ci+1); free(end); end=nend;
      }
    }
    char *nend=make_message("%s) \\",end); free(end); end=nend;
    output_indent(out,", \\",end);
  }
  for (int k=0; k<alist_len(ru->head[SEM_RULE_LEVEL_REM]); k++) {
    sem_conocc_t *co=alist_ptr(ru->head[SEM_RULE_LEVEL_REM],k);
    char cc[256];
    csm_constr_getname(cchr,co->constr,cc,256);
    if (!rem || ro->pos!=k) {
      output_fmt(out,"CSM_KILL(R%i,%s) \\\n",k+1,cc);
    } else {
      output_fmt(out,"CSM_KILLSELF(%s) \\\n",cc);
    }
  }
  if (!rem) {
    output_fmt(out,"CSM_NEEDSELF(%s) \\\n",buf2);
  }
  if (ru->hook>=0) {
    output_fmt(out,"CSM_HISTADD(%s%s\n",buf3,end);
  }
  csm_generate_body(cchr,ru,tbl_c,out);
  if (rem) {
    output_fmt(out,"CSM_END \\\n");
  } else {
    output_indent(out,"CSM_IF(!CSM_ALIVESELF || CSM_REGENSELF, \\",") \\");
    output_fmt(out,"CSM_STROUT(\"abort\") \\\n");
    for (int k=0; k<alist_len(clean); k++) {
      csm_idxclean_t *cl=alist_ptr(clean,k);
      char chc[256];
      csm_constr_getname(cchr,cl->constr,chc,256);
      output_fmt(out,"CSM_IDXUNIEND(%s,%s,%s%i) \\\n",chc,cl->idxname,cl->rem ? "R" : "K",cl->pos+1);
      free(cl->idxname);
    }
    output_fmt(out,"CSM_END \\\n");
    output_unindent(out);
  }
  csm_destruct_vartable_rule(ru,tbl);
  csm_destruct_vartable_rule(ru,tbl_c);
  output_unindent_till(out,0);
  if (end) free(end);
  output_char(out,'\n');
  gio_destruct(&gio);
  alist_free(clean);
}

/* generate code for a CCHR block (based on the semantic tree) */
void csm_generate(sem_cchr_t *in,output_t *out) {
	char buf[256];
	output_fmt(out,"#undef CONSLIST\n");
	output_fmt(out,"#define CONSLIST(CB) ");
	for (int i=0; i<alist_len(in->cons); i++) {
		if (i) output_fmt(out," CB##_S ");
		csm_constr_getname(in,i,buf,256);
		output_fmt(out,"CB##_D(%s)",buf);
	}
	output_fmt(out,"\n\n");
	for (int i=0; i<alist_len(in->rules); i++) {
		sem_rule_t *r=alist_ptr(in->rules,i);
		if (alist_len(r->head[SEM_RULE_LEVEL_REM])==0) {
			char buf2[256];
			csm_rule_getname(in,i,buf2,256);
			output_fmt(out,"#undef PROPHIST_%s\n",buf2);
			output_fmt(out,"#define PROPHIST_%s(CB",buf2);
			for (int j=0; j<alist_len(r->head[SEM_RULE_LEVEL_KEPT]); j++) {
				output_fmt(out,",Pid%i",j+1);
			}
			output_fmt(out,",...) CB##_I(Pid%i,__VA_ARGS__,",r->hook+1);
			int jj=0;
			for (int j=0; j<alist_len(r->head[SEM_RULE_LEVEL_KEPT]); j++) {
				if (j!=r->hook) {
					if (j) output_string(out," CB##_S(__VA_ARGS__) ");
					output_fmt(out,"CB##_D(Pid%i,Pid%i,%i,__VA_ARGS__)",j+1,r->hook+1,jj++);
				}
			}
			output_string(out,")\n");
			csm_constr_getname(in,alist_get(r->head[SEM_RULE_LEVEL_KEPT],r->hook).constr,buf,256);
			output_fmt(out,"#undef PROPHIST_HOOK_%s\n",buf2);
			output_fmt(out,"#define PROPHIST_HOOK_%s %s\n",buf2,buf);
			output_fmt(out,"#undef RULE_KEPT_%s\n",buf2);
			output_fmt(out,"#define RULE_KEPT_%s (%i)\n",buf2,alist_len(r->head[SEM_RULE_LEVEL_KEPT]));
			output_fmt(out,"#undef RULE_REM_%s\n",buf2);
			output_fmt(out,"#define RULE_REM_%s (%i)\n",buf2,alist_len(r->head[SEM_RULE_LEVEL_REM]));
		}
	}
	for (int i=0; i<alist_len(in->cons); i++) {
		sem_constr_t *con=alist_ptr(in->cons,i);
		csm_hashdefs_t hd;
		csm_hashdefs_init(&hd);
		char conn[256];
		csm_constr_getname(in,i,conn,256);
		output_fmt(out,"#undef ARGLIST_%s\n",conn);
		output_fmt(out,"#define ARGLIST_%s(CB,...) ",conn);
		for (int j=0; j<alist_len(con->types); j++) {
			if (j) output_fmt(out," CB##_S ");
			output_fmt(out,"CB##_D(arg%i,%s,__VA_ARGS__)",j+1,alist_get(con->types,j));
		}
		output_fmt(out,"\n");
		output_fmt(out,"#undef RULELIST_%s\n",conn);
		output_fmt(out,"#define RULELIST_%s(CB) ",conn);
		int jj=0;
		for (int j=0; j<alist_len(con->occ); j++) {
			sem_ruleocc_t *cs=alist_ptr(con->occ,j);
			if (cs->type==SEM_RULE_LEVEL_KEPT || cs->type==SEM_RULE_LEVEL_REM) {
				if (jj) output_fmt(out," CB##_S ");
				jj++;
				csm_conocc_getname(in,i,j,buf,256);
				output_fmt(out,"CB##_D(%s)",buf);
			}
		}
		output_string(out,"\n");
		output_fmt(out,"#undef RELATEDLIST_%s\n",conn);
		output_fmt(out,"#define RELATEDLIST_%s(CB) ",conn);
		for (int j=0; j<alist_len(con->related); j++) {
			if (j) output_fmt(out," CB##_S ");
			csm_constr_getname(in,alist_get(con->related,j),buf,256);
			output_fmt(out,"CS##_D(%s)",buf);
		}
		output_char(out,'\n');
		csm_varuse_t *vt=csm_generate_vartable_constr(in,i);
		if (alist_len(con->fmt.parts)>0) {
			output_fmt(out,"#undef FORMAT_%s\n",conn);
			output_fmt(out,"#define FORMAT_%s ",conn);
			csm_generate_expr(&(con->fmt),vt,out);
			output_string(out,"\n");
		}
		output_char(out,'\n');
		output_fmt(out,"#undef DESTRUCT_%s\n",conn);
		output_fmt(out,"#define DESTRUCT_%s(",conn);
		for (int l=0; l<alist_len(con->types); l++) {
			if (l) output_fmt(out,",");
			output_fmt(out,"_arg_%i",l+1);
		}
		output_fmt(out,") ");
		if (alist_len(con->destr.parts)>0) {
			csm_generate_expr(&(con->destr),vt,out);
		}
		output_string(out,"\n");
		/*output_fmt(out,"#undef DESTRUCT_PID_%s\n",conn);
		output_fmt(out,"#define DESTRUCT_PID_%s(PID) DESTRUCT_%s(",conn,conn);
		for (int l=0; l<alist_len(con->types); l++) {
			if (l) output_fmt(out,",");
			output_fmt(out,"CSM_LARG(%s,PID,arg%i)",conn,l+1);
		}
		output_fmt(out,")\n");*/
		output_fmt(out,"#undef RULEHOOKS_%s\n",conn);
		output_fmt(out,"#define RULEHOOKS_%s(CB,...) ",conn);
		for (int g=0; g<alist_len(con->hooked); g++) {
			if (g) output_string(out,"CB##_S ");
			char bfk[256];
			csm_rule_getname(in,alist_get(con->hooked,g),bfk,256);
			output_fmt(out,"CB##_D(%s,%s,__VA_ARGS__)",conn,bfk);
		}
		output_string(out,"\n");
		for (int j=0; j<alist_len(con->occ); j++) {
			sem_ruleocc_t *cs=alist_ptr(con->occ,j);
			if (cs->type==SEM_RULE_LEVEL_KEPT || cs->type==SEM_RULE_LEVEL_REM) {
				/*csm_generate_code(in,i,j,out);*/
				csm_generate_code_gio(in,i,j,out,&hd);
			}
		}
		output_string(out,"\n");
		output_fmt(out,"#undef HASHLIST_%s\n",conn);
		output_fmt(out,"#define HASHLIST_%s(CB,...) ",conn);
		for (int i=0; i<alist_len(hd.defs); i++) {
		  if (i) output_fmt(out,"CB##_S ");
		  csm_hashdef_t *def=alist_ptr(hd.defs,i);
		  char *dn=csm_hashdef_strify(def);
		  output_fmt(out,"CB##_D(%s,__VA_ARGS__) ",dn);
		  free(dn);
		}
		output_fmt(out,"\n");
		for (int i=0; i<alist_len(hd.defs); i++) {
		  csm_hashdef_t *def=alist_ptr(hd.defs,i);
		  char *dn=csm_hashdef_strify(def);
		  output_fmt(out,"#undef HASHDEF_%s_%s\n",conn,dn);
		  output_fmt(out,"#define HASHDEF_%s_%s(CB,...) ",conn,dn);
		  int nn=0;
		  for (int j=0; j<alist_len(def->list); j++) {
		    if (alist_get(def->list,j)) {
		      if (nn) output_fmt(out,"CB##_S ");
		      nn=1;
		      output_fmt(out,"CB##_D(arg%i,%s,__VA_ARGS__) ",j+1,alist_get(con->types,j));
		    }
		  }
		  output_fmt(out,"\n");
		}
		output_fmt(out,"\n");
		csm_destruct_vartable_constr(con,vt);
		csm_hashdefs_destroy(&hd);
		output_fmt(out,"\n");
	}
	output_fmt(out,"#include \"cchr_csm.h\"\n");
}
