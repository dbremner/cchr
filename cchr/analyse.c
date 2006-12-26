/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| abs2sem.c - syntax tree to semantic tree conversion                        |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "alist.h"
#include "parsestr.h"
#include "semtree.h"
#include "analyse.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

void static sem_expr_init(sem_expr_t *expr);
void static sem_expr_destruct(sem_expr_t *expr);


/* allocate and copy a string */
char static *copy_string(char *in) {
  if (in==NULL) return NULL;
  char *ret=malloc(strlen(in)+1);
  strcpy(ret,in);
  return ret;
}

/* initialize a sem_constr_t */
void static sem_constr_init(sem_constr_t* con,char *name) {
  alist_init(con->types);
  alist_init(con->occ);
  alist_init(con->hooked);
  alist_init(con->related);
  /*alist_init(con->fmtargs);*/
  sem_expr_init(&(con->fmt));
  sem_expr_init(&(con->destr));
  con->name=name;
}

/* destruct a sem_constr_t */
void static sem_constr_destruct(sem_constr_t *con) {
  free(con->name);
  alist_free(con->occ);
  alist_free(con->hooked);
  alist_free(con->related);
  for (int i=0; i<alist_len(con->types); i++) {
    free(alist_get(con->types,i));
  }
  alist_free(con->types);
  /*for (int i=0; i<alist_len(con->fmtargs); i++) {
    sem_expr_destruct(alist_ptr(con->fmtargs,i));
  }
  alist_free(con->fmtargs);*/
  sem_expr_destruct(&(con->fmt));
  
}

/* initialize a sem_exprpart_t as a variable reference */
void static sem_exprpart_init_var(sem_exprpart_t *exprp, int var) {
  exprp->type=SEM_EXPRPART_TYPE_VAR;
  exprp->data.var=var;
}

/* initialize a sem_expr_part_t as a literal string */
void static sem_exprpart_init_lit(sem_exprpart_t *exprp, char *str) {
  exprp->type=SEM_EXPRPART_TYPE_LIT;
  exprp->data.lit=str;
}

/* destruct a sem_exprpart_t */
void static sem_exprpart_destruct(sem_exprpart_t *exprp) {
  switch (exprp->type) {
    case SEM_EXPRPART_TYPE_LIT: {
      free(exprp->data.lit);
      break;
    }
    case SEM_EXPRPART_TYPE_VAR: {
      break;
    }
  }
}

/* initialize a sem_expr_t */
void static sem_expr_init(sem_expr_t *expr) {
  alist_init(expr->parts);
}

/* destruct a sem_expr_t */
void static sem_expr_destruct(sem_expr_t *expr) {
  for (int i=0; i<alist_len(expr->parts); i++) sem_exprpart_destruct(alist_ptr(expr->parts,i));
  alist_free(expr->parts);
}

/* initialize a sem_conocc_t */
void static sem_conocc_init(sem_conocc_t *occ,int constr) {
  alist_init(occ->args);
  occ->constr=constr;
}

/* destruct a sem_conocc_t */
void static sem_conocc_destruct(sem_conocc_t *con) {
  alist_free(con->args);
}

/* initialize a sem_conocc_t */
void static sem_conoccout_init(sem_conoccout_t *occ, int constr) {
  alist_init(occ->args);
  occ->constr=constr;
}

/* destruct a sem_conocc_t */
void static sem_conoccout_destruct(sem_conoccout_t *con) {
  for (int i=0; i<alist_len(con->args); i++) {
    sem_expr_destruct(&(alist_get(con->args,i)));
  }
  alist_free(con->args);
}

void static sem_out_init_con(sem_out_t *out, sem_conoccout_t *con) {
	out->type=SEM_OUT_TYPE_CON;
	out->data.con=*con;
}

void static sem_out_init_expr(sem_out_t *out, sem_expr_t *exp,int stmt) {
	out->type=(stmt ? SEM_OUT_TYPE_STM : SEM_OUT_TYPE_EXP);
	out->data.exp=*exp;
}

void static sem_out_init_var(sem_out_t *out, int var) {
	out->type=SEM_OUT_TYPE_VAR;
	out->data.var=var;
}

void static sem_out_destruct(sem_out_t *out) {
	switch (out->type) {
		case SEM_OUT_TYPE_CON:
			sem_conoccout_destruct(&(out->data.con));
			break;
		case SEM_OUT_TYPE_STM:
		case SEM_OUT_TYPE_EXP:
			sem_expr_destruct(&(out->data.exp));
			break;
		case SEM_OUT_TYPE_VAR:
			break;
	}
}

/* initialize a sem_var_t */
void static sem_var_init(sem_var_t *var, char *name, char *type, int anon) {
  var->name=name;
  var->type=type;
  var->local=0;
  var->anon=anon;
  var->occ[SEM_RULE_LEVEL_KEPT]=0;
  var->occ[SEM_RULE_LEVEL_REM]=0;
  var->occ[SEM_RULE_LEVEL_GUARD]=0;
  var->occ[SEM_RULE_LEVEL_BODY]=0;
  sem_expr_init(&(var->def));
}

/* initialize a variable as local */
void static sem_var_init_local(sem_var_t *var, char *name, char *type, sem_expr_t *def, int body) {
	sem_var_init(var,name,type,0);
	var->local=body+1;
	var->def = *def;
}

/* destruct a sem_var_t */
void static sem_var_destruct(sem_var_t *var) {
  free(var->name);
  free(var->type);
  if (var->local) sem_expr_destruct(&(var->def));
}

/* initialize a variable table */
void static sem_vartable_init(sem_vartable_t *vt) {
  alist_init(vt->vars);
}

/* initialize a vartable to have only $%i vars */
void static sem_vartable_init_args(sem_vartable_t *vt, int nargs) {
	sem_vartable_init(vt);
	for (int i=0; i<nargs; i++) {
		char c[16];
		snprintf(c,16,"$%i",i+1);
		sem_var_t var;
		sem_var_init(&var,copy_string(c),NULL,0);
		alist_add(vt->vars,var);
	}
}

/* destruct a sem_vartable_t */
void static sem_vartable_destruct(sem_vartable_t *vr) {
  for (int i=0; i<alist_len(vr->vars); i++) sem_var_destruct(alist_ptr(vr->vars,i));
  alist_free(vr->vars);
}

/* initialize a sem_rule_t */
void static sem_rule_init(sem_rule_t *rule, char *name) {
  rule->name=name;
  sem_vartable_init(&(rule->vt));
  alist_init(rule->head[SEM_RULE_LEVEL_KEPT]);
  alist_init(rule->head[SEM_RULE_LEVEL_REM]);
  alist_init(rule->out[0]);
  alist_init(rule->out[1]);
  rule->hook=-1;
}

/* destruct a sem_rule_t */
void static sem_rule_destruct(sem_rule_t *rule) {
  free(rule->name);
  sem_vartable_destruct(&(rule->vt));
  for (int i=0; i<alist_len(rule->head[SEM_RULE_LEVEL_KEPT]); i++) sem_conocc_destruct(alist_ptr(rule->head[SEM_RULE_LEVEL_KEPT],i));
  alist_free(rule->head[SEM_RULE_LEVEL_KEPT]);
  for (int i=0; i<alist_len(rule->head[SEM_RULE_LEVEL_REM]); i++) sem_conocc_destruct(alist_ptr(rule->head[SEM_RULE_LEVEL_REM],i));
  alist_free(rule->head[SEM_RULE_LEVEL_REM]);
  for (int i=0; i<alist_len(rule->out[0]); i++) sem_out_destruct(alist_ptr(rule->out[0],i));
  alist_free(rule->out[0]);
  for (int i=0; i<alist_len(rule->out[1]); i++) sem_out_destruct(alist_ptr(rule->out[1],i));
  alist_free(rule->out[1]);
}

/* initialize a sem_cchr_t */
void sem_cchr_init(sem_cchr_t *cchr) {
  alist_init(cchr->rules);
  alist_init(cchr->cons);
  alist_init(cchr->exts);
}

/* destruct a sem_cchr_t */
void sem_cchr_destruct(sem_cchr_t *cchr) {
  for (int i=0; i<alist_len(cchr->rules); i++) sem_rule_destruct(alist_ptr(cchr->rules,i));
  alist_free(cchr->rules);
  for (int i=0; i<alist_len(cchr->cons); i++) sem_constr_destruct(alist_ptr(cchr->cons,i));
  alist_free(cchr->cons);
  for (int i=0; i<alist_len(cchr->exts); i++) free(alist_get(cchr->exts,i));
  alist_free(cchr->exts);
}

/* generate a new (unused) variable in a rule, and return its id */
int static sem_generate_random_var(sem_vartable_t *vt) {
	int j=0;
	char test[32];
	do {
		snprintf(test,32,"_tmp%i_",j);
		int found=0;
		for (j=0; j<alist_len(vt->vars); j++) {
			if (!strcmp(alist_get(vt->vars,j).name,test)) {
				found=1;
				break;
			}
		}
		if (!found) break;
		j++;
	} while(1);
	sem_var_t var;
	sem_var_init(&var,copy_string(test),NULL,1);
	int ret=alist_len(vt->vars);
	alist_add(vt->vars,var);
	return ret;
}

struct {
	char *name;
	int ar;
} sem_stmsym;

/* store<0: not, >=0: in that place in var->occ[] */
/* generate a sem_expr_t from a expr_t */
int static sem_generate_expr(sem_expr_t *expr,sem_vartable_t *vt,sem_cchr_t *cchr,expr_t *in,char *desc,int pos, int stmt) {
	int ok=1;
	for (int j=pos; j<alist_len(in->list); j++) {
		token_t *tok=alist_ptr(in->list,j);
		int pa=0;
		switch (tok->type) {
			case TOKEN_TYPE_LIT: {
				sem_exprpart_t se;
				sem_exprpart_init_lit(&se,copy_string(tok->data));
				alist_add(expr->parts,se);
				break;
			}
			case TOKEN_TYPE_FUNC: /* a function-call is actually a type of symbol */
			  pa=1;
			case TOKEN_TYPE_SYMB: if (tok->data) {
				sem_exprpart_t se;
				int ie=0;
				for (int i=0; i<alist_len(cchr->exts); i++) {
					if (!strcmp(tok->data,alist_get(cchr->exts,i))) {
						sem_exprpart_init_lit(&se,copy_string(tok->data));
						alist_add(expr->parts,se);
						ie=1;
						break;
					}
				}
				if (ie) break;
				if (!stmt && vt && tok->data[0]=='_') { /* anonymous variable */
					int anvar=sem_generate_random_var(vt);
					sem_exprpart_init_var(&se,anvar);
					alist_add(expr->parts,se);
					ie=1;
					break;
				}
				if (vt) { for (int i=0; i<alist_len(vt->vars); i++) { /* look for existing var */
					if (!strcmp(tok->data,alist_get(vt->vars,i).name)) {
						sem_exprpart_init_var(&se,i);
						alist_add(expr->parts,se);
						ie=1;
						break;
					}
				} }
				if (ie) break;
				if (stmt) {
					sem_exprpart_init_lit(&se,copy_string(tok->data));
					alist_add(expr->parts,se);
					ie=1;
					break;
				} else {
					if (!isupper(tok->data[0])) {
						fprintf(stderr,"error: in %s: variable names must start with uppercase letter in '%s'\n",desc ? desc : "<anonymus>",tok->data);
						ok=0;
					} else {
						if (vt) {
							int nvp=alist_len(vt->vars);
							sem_var_t nv;
							sem_var_init(&nv,copy_string(tok->data),NULL,0);
							alist_add(vt->vars,nv);
							sem_exprpart_init_var(&se,nvp);
							alist_add(expr->parts,se);
							ie=1;
						}
					}
					break;
				}
			}
		}
		if (pa) {
			sem_exprpart_t se;
			sem_exprpart_init_lit(&se,copy_string("("));
			alist_add(expr->parts,se);
			for (int l=0; l<alist_len(tok->args); l++) {
				if (l) {
					sem_exprpart_init_lit(&se,copy_string(","));
					alist_add(expr->parts,se);
				}
				if (!sem_generate_expr(expr,vt,cchr,alist_ptr(tok->args,l),desc,0,stmt)) ok=0;
			}
			sem_exprpart_init_lit(&se,copy_string(")"));
			alist_add(expr->parts,se);
		}
	}
	if (!ok) sem_expr_destruct(expr);
	return ok;
}

int static sem_generate_localstm(sem_cchr_t *cchr,sem_rule_t *rule,expr_t *expr,int body) {
	if (alist_len(expr->list)<3) return 0;
	if (alist_get(expr->list,0).type != TOKEN_TYPE_LIT || strcmp(alist_get(expr->list,0).data,"{")) return 0;
	token_t b;
	alist_pop(expr->list,b);
	if (b.type != TOKEN_TYPE_LIT || strcmp(b.data,"}")) {alist_add(expr->list,b); return 0;}
	destruct_token_t(&b);
	sem_expr_t se;
	sem_expr_init(&se);
	if (!sem_generate_expr(&se,&(rule->vt),cchr,expr,rule->name,1,1)) return 0;
	sem_out_t out;
	sem_out_init_expr(&out,&se,1);
	alist_add(rule->out[body],out);
	return 1;
}

/* assign an expression to a vartable (update occurrence counts in variables) */
void static sem_expr_assign(sem_expr_t *expr,sem_vartable_t *vt, int type, int mult) {
	for (int j=0; j<alist_len(expr->parts); j++) {
		sem_exprpart_t *ep=alist_ptr(expr->parts,j);
		if (ep->type==SEM_EXPRPART_TYPE_VAR) {
			alist_get(vt->vars,ep->data.var).occ[type]+=mult;
		}
	}
}

/* assign a rule to its vartable (update occurrence counts in variables) */
void static sem_rule_assign(sem_rule_t *rule,int mult) {
	for (int type=0; type<2; type++) {
		for (int j=0; j<alist_len(rule->head[type]); j++) {
			sem_conocc_t *co=alist_ptr(rule->head[type],j);
			for (int k=0; k<alist_len(co->args); k++) {
				alist_get(rule->vt.vars,alist_get(co->args,k)).occ[type]+=mult;
			}
		}
	}
	for (int body=0; body<2; body++) {
		for (int j=0; j<alist_len(rule->out[body]); j++) {
			sem_out_t *co=alist_ptr(rule->out[body],j);
			switch (co->type) {
				case SEM_OUT_TYPE_CON: {
					for (int k=0; k<alist_len(co->data.con.args); k++) {
						sem_expr_assign(alist_ptr(co->data.con.args,k),&(rule->vt),body ? SEM_RULE_LEVEL_BODY : SEM_RULE_LEVEL_GUARD,mult);
					}
					break;
				}
				case SEM_OUT_TYPE_EXP:{
					sem_expr_assign(&(co->data.exp),&(rule->vt),body ? SEM_RULE_LEVEL_BODY : SEM_RULE_LEVEL_GUARD,mult);
					break;
				}
				case SEM_OUT_TYPE_STM: {
					sem_expr_assign(&(co->data.exp),&(rule->vt),body ? SEM_RULE_LEVEL_BODY : SEM_RULE_LEVEL_GUARD,mult);
					break;
				}
				case SEM_OUT_TYPE_VAR: {
					sem_var_t *var=alist_ptr(rule->vt.vars,co->data.var);
					var->occ[body ? SEM_RULE_LEVEL_BODY : SEM_RULE_LEVEL_GUARD]+=mult;
					sem_expr_assign(&(var->def),&(rule->vt),body ? SEM_RULE_LEVEL_BODY : SEM_RULE_LEVEL_GUARD,mult);
					break;
				}
			}
		}
	}
}

int static sem_generate_localvar(sem_cchr_t *cchr,sem_rule_t *rule,expr_t *expr, int body) {
	if (alist_len(expr->list)<3) return 0;
	int j=0;
	int pl=0;
	while (j<alist_len(expr->list)) {
		token_t *ep=alist_ptr(expr->list,j);
		if (ep->type==TOKEN_TYPE_LIT && !strcmp(ep->data,"=")) {
			if (j<2) return 0;
			token_t *pep=alist_ptr(expr->list,j-1);
			if (pep->type==TOKEN_TYPE_SYMB && isupper(pep->data[0])) {
				char *type=malloc(pl+1);
				type[0]=0;
				for (int t=0; t<j-1; t++) {
					if (t) strcat(type," ");
					strcat(type,alist_get(expr->list,t).data);
				}
				sem_expr_t se;
				sem_expr_init(&se);
				if (j<alist_len(expr->list)-1) {
					if (!sem_generate_expr(&se,&(rule->vt),cchr,expr,rule->name,j+1,0)) return 0;
				}
				sem_var_t var;
				sem_var_init_local(&var,copy_string(pep->data),type,&se,body);
				alist_add(rule->vt.vars,var);
				sem_out_t out;
				sem_out_init_var(&out,alist_len(rule->vt.vars)-1);
				alist_add(rule->out[body],out);
				return 1;
			}
			return 0;
		}
		if (ep->type==TOKEN_TYPE_FUNC) return 0;
		pl+=strlen(ep->data)+1;
		j++;
	}
	return 0;
}

/* generate a conocc arg (for in kept or removed constraints) given its sem_expr_t as argument */
int static sem_generate_conocc_arg(sem_rule_t *rule,sem_cchr_t *cchr,sem_expr_t *expr) {
	if (alist_len(expr->parts)==1 && alist_get(expr->parts,0).type==SEM_EXPRPART_TYPE_VAR) {
		int v=alist_get(expr->parts,0).data.var;
		sem_expr_destruct(expr);
		return v;
	}
	int var=sem_generate_random_var(&(rule->vt));
	sem_expr_t nex;
	sem_expr_init(&nex);
	sem_exprpart_t nexp;
	sem_exprpart_init_var(&nexp,var);
	alist_add(nex.parts,nexp);
	sem_exprpart_init_lit(&nexp,copy_string("=="));
	alist_add(nex.parts,nexp);
	sem_exprpart_init_lit(&nexp,copy_string("("));
	alist_add(nex.parts,nexp);
	alist_addall(nex.parts,expr->parts);
	alist_free(expr->parts);
	sem_exprpart_init_lit(&nexp,copy_string(")"));
	alist_add(nex.parts,nexp);
	sem_out_t out;
	sem_out_init_expr(&out,&nex,0);
	alist_add(rule->out[0],out);
	return var;
}

/* return 0 if no constraint occurrence can be derived from the expression 'in' */
/* generate a conocc (given its functional form in a expr_t) */
/* type cannot be SEM_RULE_LEVEL_GUARD (no conocc's there) */
int static sem_generate_conocc(sem_rule_t *rule,sem_cchr_t *cchr,expr_t *in,int type) {
	int ok=1;
	if (alist_len(in->list) != 1) return 0;
	token_t *tok=alist_ptr(in->list,0);
	if (tok->type != TOKEN_TYPE_FUNC) return 0;
	for (int j=0; j<alist_len(cchr->cons); j++) {
		sem_constr_t *cons=alist_ptr(cchr->cons,j);
		if ((alist_len(tok->args) == alist_len(cons->types)) && !strcmp(tok->data,cons->name)) {
			sem_conocc_t n1;
			sem_conoccout_t n2;
			sem_ruleocc_t r;
			r.rule=alist_len(cchr->rules);
			r.type=type;
			if (type==SEM_RULE_LEVEL_BODY) {
				sem_conoccout_init(&n2,j);
				r.pos=alist_len(rule->out[1]);
			} else {
				sem_conocc_init(&n1,j);
				r.pos=alist_len(rule->head[type]);
			}
			alist_add(cons->occ,r);
			for (int s=0; s<alist_len(tok->args); s++) {
				expr_t *expr=alist_ptr(tok->args,s);
				sem_expr_t se;
				sem_expr_init(&se);
				if (!sem_generate_expr(&se,&(rule->vt),cchr,expr,rule->name,0,0)) ok=0;
				if (type==SEM_RULE_LEVEL_BODY) {
					alist_add(n2.args,se);
				} else {
				  	int var=sem_generate_conocc_arg(rule,cchr,&se);
				  	alist_add(n1.args,var);
				}
			}
			if (type==SEM_RULE_LEVEL_BODY) {
				sem_out_t out;
				sem_out_init_con(&out,&n2);
				alist_add(rule->out[1],out);
			} else {
				alist_add(rule->head[type],n1);
			}
			return ok;
		}
	}
	return 0;
}

/* complete the HNF form (splitting duplicate variables) */
/* requires assign to have completed */
int static sem_rule_hnf(sem_rule_t *rule) {
	for (int j=0; j<alist_len(rule->vt.vars); j++) {
		sem_var_t *var=alist_ptr(rule->vt.vars,j);
		int bnd=var->occ[SEM_RULE_LEVEL_KEPT]+var->occ[SEM_RULE_LEVEL_REM];
		int occ=bnd+var->occ[SEM_RULE_LEVEL_GUARD]+var->occ[SEM_RULE_LEVEL_BODY];
		if (bnd==0 && !var->local) {
			fprintf(stderr,"error: in rule '%s': variable '%s' is unbound\n",rule->name ? rule->name : "(unk)",var->name);
			return 0;
		}
		if (occ==1 && !var->anon) {
			fprintf(stderr,"warning: in rule '%s': variable '%s' is singleton\n",rule->name ? rule->name : "(unk)",var->name);
		} 
		if (bnd>1) { // split variable
			int oc=0;
			for (int p=SEM_RULE_LEVEL_KEPT; p<=SEM_RULE_LEVEL_REM; p++) { // KEPT & REM
				for (int k=0; k<alist_len(rule->head[p]); k++) { // all conocc's
					sem_conocc_t *cot=alist_ptr(rule->head[p],k);
					for (int l=0; l<alist_len(cot->args); l++) { // all args of conocc
						int kv=alist_get(cot->args,l);
						if (kv==j) {
							if (oc) {
								int nv=sem_generate_random_var(&(rule->vt));
								alist_get(cot->args,l)=nv;
								sem_expr_t ne;
								sem_expr_init(&ne);
								sem_exprpart_t nep;
								sem_exprpart_init_var(&nep,j);
								alist_add(ne.parts,nep);
								sem_exprpart_init_lit(&nep,copy_string("=="));
								alist_add(ne.parts,nep);
								sem_exprpart_init_var(&nep,nv);
								alist_add(ne.parts,nep);
								sem_out_t out;
								sem_out_init_expr(&out,&ne,0);
								alist_add(rule->out[0],out);
								var->occ[p]--;
								alist_get(rule->vt.vars,nv).occ[p]++;
								alist_get(rule->vt.vars,nv).occ[SEM_RULE_LEVEL_GUARD]++;
								alist_get(rule->vt.vars,kv).occ[p]--;
							}
							oc=1;
						}
					}
				}
			}
		}
	}
	return 1;
}

void static sem_hook_rule(sem_cchr_t *out,int rulenum) {
	sem_rule_t *rule=alist_ptr(out->rules,rulenum);
	if (rule->hook<0 && alist_len(rule->head[SEM_RULE_LEVEL_REM])==0) {
		int bestpos=-1; /* what conocc in KEPT is best (-1: none yet) */
		int bestcon=0; /* what constraint is best */
		int bestnum=0; /* how many hooks that contraint already has */
		for (int j=0; j<alist_len(rule->head[SEM_RULE_LEVEL_KEPT]); j++) {
			sem_conocc_t *co=alist_ptr(rule->head[SEM_RULE_LEVEL_KEPT],j);
			int num=alist_len(alist_get(out->cons,co->constr).hooked);
			if (bestpos==-1 || num<bestnum) {
				bestpos=j;
				bestcon=co->constr;
				bestnum=num;
			}
		}
		alist_add(alist_get(out->cons,bestcon).hooked,rulenum);
		rule->hook=bestpos;
	}
}

void static sem_rule_related(sem_cchr_t *out,sem_rule_t *rule) {
	for (int i=0; i<alist_len(rule->head[SEM_RULE_LEVEL_REM])+alist_len(rule->head[SEM_RULE_LEVEL_KEPT]); i++) {
		int ik=(i>=alist_len(rule->head[SEM_RULE_LEVEL_REM]));
		int in=i-ik*alist_len(rule->head[SEM_RULE_LEVEL_REM]);
		sem_constr_t *cons=alist_ptr(out->cons,alist_get(rule->head[ik ? SEM_RULE_LEVEL_KEPT : SEM_RULE_LEVEL_REM],in).constr);
		for (int j=0; j<alist_len(rule->head[SEM_RULE_LEVEL_REM])+alist_len(rule->head[SEM_RULE_LEVEL_KEPT]); j++) {
			if (i!=j) {
				int jk=(j>=alist_len(rule->head[SEM_RULE_LEVEL_REM]));
				int jn=j-jk*alist_len(rule->head[SEM_RULE_LEVEL_REM]);
				int conid=alist_get(rule->head[jk ? SEM_RULE_LEVEL_KEPT : SEM_RULE_LEVEL_REM],jn).constr;
				int k=0;
				while (k<alist_len(cons->related)) {
					if (alist_get(cons->related,k) == conid) break;
					k++;
				}
				if (k==alist_len(cons->related)) {
					alist_add(cons->related,conid);
				}
			}
		}
	}
}

/* generate a new rule in an output sem_cchr_t */
int static sem_generate_rule(sem_cchr_t *out,rule_t *in) {
	sem_rule_t n;
	sem_rule_init(&n,copy_string(in->name));
	int doret=1;
	for (int i=0; i<alist_len(in->guard.list); i++) {
		int ok=0;
		if (!ok) ok=sem_generate_localvar(out,&n,alist_ptr(in->guard.list,i),0);
		if (!ok) ok=sem_generate_localstm(out,&n,alist_ptr(in->guard.list,i),0);
		if (!ok) {
			sem_expr_t expr;
			sem_expr_init(&expr);
			if (!sem_generate_expr(&expr,&(n.vt),out,alist_ptr(in->guard.list,i),n.name,0,0)) doret=0;
			sem_out_t ot;
			sem_out_init_expr(&ot,&expr,0);
			alist_add(n.out[0],ot);
		}
	}
	for (int i=0; i<alist_len(in->removed.list); i++) {
		if (!sem_generate_conocc(&n,out,alist_ptr(in->removed.list,i),SEM_RULE_LEVEL_REM)) doret=0;
	}
	for (int i=0; i<alist_len(in->kept.list); i++) {
		if (!sem_generate_conocc(&n,out,alist_ptr(in->kept.list,i),SEM_RULE_LEVEL_KEPT)) doret=0;
	}
	for (int i=0; i<alist_len(in->body.list); i++) {
		int ok=0;
		if (!ok) ok=sem_generate_conocc(&n,out,alist_ptr(in->body.list,i),SEM_RULE_LEVEL_BODY);
		if (!ok) ok=sem_generate_localvar(out,&n,alist_ptr(in->body.list,i),1);
		if (!ok) ok=sem_generate_localstm(out,&n,alist_ptr(in->body.list,i),1);
		if (!ok) {fprintf(stderr,"In rule %s: unable to parse body part %i\n",n.name ? n.name : "<anonymous>",i+1);doret=0;}
	}
	sem_rule_assign(&n,1);
	if (doret && sem_rule_hnf(&n)) {
		sem_rule_related(out,&n);
		alist_add(out->rules,n);
		sem_hook_rule(out,alist_len(out->rules)-1);
		return 1;
	} else {
		sem_rule_destruct(&n);
		return 0;
	}
}

/* generate a new constraint in an output sem_cchr_t */
void static sem_generate_cons(sem_cchr_t *out,constr_t *in) {
  sem_constr_t n;
  sem_constr_init(&n,copy_string(in->name));
  for (int i=0; i<alist_len(in->list); i++) {
  	alist_add(n.types,copy_string(alist_get(in->list,i)));
  }
  sem_vartable_t svt;
  sem_vartable_init_args(&svt,alist_len(n.types));
  for (int i=0; i<alist_len(in->args); i++) {
  	expr_t *e=alist_ptr(in->args,i);
  	token_t *t=alist_ptr(e->list,0);
  	int ok=0;
  	if (t->type==TOKEN_TYPE_FUNC) {
  		if (!ok && !strcmp(t->data,"fmt")) {
  			sem_expr_init(&(n.fmt));
  			sem_generate_expr(&(n.fmt),NULL,out,alist_ptr(t->args,0),n.name,0,1);
  			/*for (int j=1; j<alist_len(t->args); j++) {
  				sem_expr_t ar;
  				sem_expr_init(&ar);
  				sem_generate_expr(&ar,&svt,out,alist_ptr(t->args,j),n.name,0,1,-1);
  				alist_add(n.fmtargs,ar);
  			}*/
  			ok=1;
  		}
  		if (!ok && !strcmp(t->data,"destr")) {
  			sem_expr_init(&(n.destr));
  			sem_generate_expr(&(n.destr),&svt,out,alist_ptr(t->args,0),n.name,0,1);
  			ok=1;  			
  		}
  		if (!ok) {
  			fprintf(stderr,"warning: unknown constraint attribute '%s' ignored\n",t->data);
  		}
  	}
  }
  sem_vartable_destruct(&svt);
  alist_add(out->cons,n);
}

/* generate a semantic form (sem_cchr_t) of the syntax tree (cchr_t) */
int sem_generate_cchr(sem_cchr_t *out,cchr_t *in) {
  sem_cchr_init(out);
  int ok=1;
  for (int i=0; i<alist_len(in->exts); i++) {
    alist_add(out->exts,copy_string(alist_get(in->exts,i)));
  }
  for (int i=0; i<alist_len(in->constrs); i++) {
  	sem_generate_cons(out,alist_ptr(in->constrs,i));
  }
  for (int i=0; i<alist_len(in->rules); i++) {
  	if (!sem_generate_rule(out,alist_ptr(in->rules,i))) ok=0;
  }
  return ok;
}
