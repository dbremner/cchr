#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "alist.h"
#include "parsestr.h"
#include "semtree.h"

void sem_constr_init(sem_constr_t* con,char *name) {
  alist_init(con->types);
  alist_init(con->occ[SEM_RULE_LEVEL_KEPT]);
  alist_init(con->occ[SEM_RULE_LEVEL_REM]);
  alist_init(con->occ[SEM_RULE_LEVEL_BODY]);
  con->name=name;
}

void sem_constr_destruct(sem_constr_t *con) {
  free(con->name);
  alist_free(con->occ[SEM_RULE_LEVEL_KEPT]);
  alist_free(con->occ[SEM_RULE_LEVEL_REM]);
  alist_free(con->occ[SEM_RULE_LEVEL_BODY]);
}

void sem_exprpart_init_var(sem_exprpart_t *exprp, int var) {
  exprp->type=SEM_EXPRPART_TYPE_VAR;
  exprp->data.var=var;
}

void sem_exprpart_destruct(sem_exprpart_t *exprp) {
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

void sem_exprpart_init_lit(sem_exprpart_t *exprp, char *str) {
  exprp->type=SEM_EXPRPART_TYPE_LIT;
  exprp->data.lit=str;
}

void sem_expr_init(sem_expr_t *expr) {
  alist_init(expr->parts);
}

void sem_expr_destruct(sem_expr_t *expr) {
  for (int i=0; i<alist_len(expr->parts); i++) sem_exprpart_destruct(alist_ptr(expr->parts,i));
  alist_free(expr->parts);
}

void sem_conocc_init(sem_conocc_t *occ, int constr) {
  alist_init(occ->args);
  occ->constr=constr;
}

void sem_conocc_destruct(sem_conocc_t *con) {
  alist_free(con->args);
}

void sem_var_init(sem_var_t *var, char *name, char *type) {
  var->name=name;
  var->type=type;
  var->occ[SEM_RULE_LEVEL_KEPT]=0;
  var->occ[SEM_RULE_LEVEL_REM]=0;
  var->occ[SEM_RULE_LEVEL_BODY]=0;
  var->occ[SEM_RULE_LEVEL_GUARD]=0;
}

void sem_var_destruct(sem_var_t *var) {
  free(var->name);
}

void sem_rule_init(sem_rule_t *rule, char *name) {
  rule->name=name;
  alist_init(rule->vars);
  alist_init(rule->con[SEM_RULE_LEVEL_KEPT]);
  alist_init(rule->con[SEM_RULE_LEVEL_REM]);
  alist_init(rule->con[SEM_RULE_LEVEL_BODY]);
  alist_init(rule->con[SEM_RULE_LEVEL_GUARD]);
}

void sem_rule_destruct(sem_rule_t *rule) {
  free(rule->name);
  for (int i=0; i<alist_len(rule->vars); i++) sem_var_destruct(alist_ptr(rule->vars,i));
  alist_free(rule->vars);
  for (int i=0; i<alist_len(rule->con[SEM_RULE_LEVEL_KEPT]); i++) sem_conocc_destruct(alist_ptr(rule->con[SEM_RULE_LEVEL_KEPT],i));
  alist_free(rule->con[SEM_RULE_LEVEL_KEPT]);
  for (int i=0; i<alist_len(rule->con[SEM_RULE_LEVEL_REM]); i++) sem_conocc_destruct(alist_ptr(rule->con[SEM_RULE_LEVEL_REM],i));
  alist_free(rule->con[SEM_RULE_LEVEL_REM]);
  for (int i=0; i<alist_len(rule->con[SEM_RULE_LEVEL_BODY]); i++) sem_conocc_destruct(alist_ptr(rule->con[SEM_RULE_LEVEL_BODY],i));
  alist_free(rule->con[SEM_RULE_LEVEL_BODY]);
  for (int i=0; i<alist_len(rule->guard); i++) sem_expr_destruct(alist_ptr(rule->guard,i));
  alist_free(rule->guard);
}

void sem_cchr_init(sem_cchr_t *cchr) {
  alist_init(cchr->rules);
  alist_init(cchr->cons);
  alist_init(cchr->exts);
}

void sem_cchr_destruct(sem_cchr_t *cchr) {
  for (int i=0; i<alist_len(cchr->rules); i++) sem_rule_destruct(alist_ptr(cchr->rules,i));
  alist_free(cchr->rules);
  for (int i=0; i<alist_len(cchr->cons); i++) sem_constr_destruct(alist_ptr(cchr->cons,i));
  alist_free(cchr->cons);
  for (int i=0; i<alist_len(cchr->exts); i++) free(alist_get(cchr->exts,i));
  alist_free(cchr->exts);
}

char static *copy_string(char *in) {
  if (in==NULL) return NULL;
  char *ret=malloc(strlen(in)+1);
  strcpy(ret,in);
  return ret;
}

int sem_generate_random_var(sem_rule_t *rule) {
	int j=0;
	char test[32];
	do {
		snprintf(test,32,"_tmp%i_",j);
		int found=0;
		for (j=0; j<alist_len(rule->vars); j++) {
			if (!strcmp(alist_get(rule->vars,j).name,test)) {
				found=1;
				break;
			}
		}
		if (!found) break;
		j++;
	} while(1);
	sem_var_t var;
	sem_var_init(&var,copy_string(test),NULL);
	int ret=alist_len(rule->vars);
	alist_add(rule->vars,var);
	printf("generated var '%s' as %i\n",var.name,ret);
	return ret;
}

void sem_generate_expr(sem_expr_t *expr,sem_rule_t *rule,sem_cchr_t *cchr,expr_t *in) {
	for (int j=0; j<alist_len(in->list); j++) {
		token_t *tok=alist_ptr(in->list,j);
		int pa=0;
		switch (tok->type) {
			case TOKEN_TYPE_LIT: {
				sem_exprpart_t se;
				sem_exprpart_init_lit(&se,copy_string(tok->data));
				alist_add(expr->parts,se);
				break;
			}
			case TOKEN_TYPE_FUNC: /* a function-call is actually a type of symol */
			  pa=1;
			case TOKEN_TYPE_SYMB: {
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
				if (!isupper(tok->data[0])) {
					// TODO: error, variable names must start with an uppercase letter
					break;
				}
				for (int i=0; i<alist_len(rule->vars); i++) { /* look for existing var */
					if (!strcmp(tok->data,alist_get(rule->vars,i).name)) {
						sem_exprpart_init_var(&se,i);
						alist_add(expr->parts,se);
						ie=1;
						break;
					}
				}
				if (ie) break;
				int nvp=alist_len(rule->vars);
				sem_var_t nv;
				sem_var_init(&nv,copy_string(tok->data),NULL);
				alist_add(rule->vars,nv);
				sem_exprpart_init_var(&se,nvp);
				alist_add(expr->parts,se);
				break;
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
				sem_generate_expr(expr,rule,cchr,alist_ptr(tok->args,l));
			}
		}
	}
}

int sem_generate_conocc_arg(sem_rule_t *rule,sem_cchr_t *cchr,sem_expr_t *expr) {
	if (alist_len(expr->parts)==1 && alist_get(expr->parts,0).type==SEM_EXPRPART_TYPE_VAR) {
		int v=alist_get(expr->parts,0).data.var;
		sem_expr_destruct(expr);
		return v;
	}
	/*for (int j=0; j<alist_len(expr.list); j++) {
		if (alist_get(expr.list,j).type==SEM_EXPRPART_TYPE_VAR) {
			TODO: error: variable expression as CCHR argument
			sem_expr_destruct(&expr);
			return -1;
		}
	}*/
	int var=sem_generate_random_var(rule);
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
	alist_add(rule->guard,nex);
	return var;
}

/* return 0 if no constraint occurence can be derived from the expression 'in' */
int sem_generate_conocc(sem_rule_t *rule,sem_cchr_t *cchr,expr_t *in,int type) {
	if (alist_len(in->list) != 1) return 0;
	token_t *tok=alist_ptr(in->list,0);
	if (tok->type != TOKEN_TYPE_FUNC) return 0;
	for (int j=0; j<alist_len(cchr->cons); j++) {
		sem_constr_t *cons=alist_ptr(cchr->cons,j);
		if ((alist_len(tok->args) == alist_len(cons->types)) && !strcmp(tok->data,cons->name)) {
			sem_conocc_t n;
			sem_conocc_init(&n,j);
			sem_ruleocc_t r;
			r.pos=alist_len(rule->con[type]);
			r.rule=alist_len(cchr->rules);
			alist_add(cons->occ[type],r);
			for (int s=0; s<alist_len(tok->args); s++) {
				expr_t *expr=alist_ptr(tok->args,s);
				sem_conoccarg_t coa;
				sem_expr_t se;
				sem_expr_init(&se);
				sem_generate_expr(&se,rule,cchr,expr);
				if (type==SEM_RULE_LEVEL_KEPT || type==SEM_RULE_LEVEL_REM) {
				  int var=sem_generate_conocc_arg(rule,cchr,&se);
				  coa.var=var;
				  alist_add(n.args,coa);
				  alist_get(rule->vars,var).occ[type]++;
				} else {
					coa.expr=se;
					alist_add(n.args,coa);
				}
			}
			alist_add(rule->con[type],n);
			return 1;
		}
	}
	return 0;
}

void sem_rule_hnf(sem_rule_t *rule) {
	for (int j=0; j<alist_len(rule->vars); j++) {
		sem_var_t *var=alist_ptr(rule->vars,j);
		int bnd=var->occ[0]+var->occ[1];
		if (bnd==0) {
			fprintf(stderr,"error: in rule '%s': variable '%s' is unbound\n",rule->name,var->name);
			// TODO error handling
		}
		if (bnd>1) { // split variable
			int oc=0;
			for (int p=SEM_RULE_LEVEL_KEPT; p<=SEM_RULE_LEVEL_REM; p++) { // KEPT & REM
				for (int k=0; k<alist_len(rule->con[SEM_RULE_LEVEL_KEPT]); k++) { // all conocc's
					sem_conocc_t *cot=alist_ptr(rule->con[SEM_RULE_LEVEL_KEPT],k);
					for (int l=0; l<alist_len(cot->args); l++) { // all args of conocc
						int kv=alist_get(cot->args,l).var;
						if (kv==j) {
							if (oc) {
								int nv=sem_generate_random_var(rule);
								alist_get(cot->args,l).var=nv;
								sem_expr_t ne;
								sem_expr_init(&ne);
								sem_exprpart_t nep;
								sem_exprpart_init_var(&nep,j);
								alist_add(ne.parts,nep);
								sem_exprpart_init_lit(&nep,copy_string("=="));
								alist_add(ne.parts,nep);
								sem_exprpart_init_var(&nep,nv);
								alist_add(ne.parts,nep);
								alist_add(rule->guard,ne);
								var->occ[p]--;
								alist_get(rule->vars,nv).occ[p]++;
							}
							oc=1;
						}
					}
				}
			}
		}
	}
}

void sem_generate_rule(sem_cchr_t *out,rule_t *in) {
	sem_rule_t n;
	sem_rule_init(&n,copy_string(in->name));
	if (alist_len(in->guard.list)!=0) {
		sem_expr_t expr;
		sem_expr_init(&expr);
		sem_generate_expr(&expr,&n,out,&(in->guard));
		alist_add(n.guard,expr);
	}
	for (int i=0; i<alist_len(in->kept.list); i++) {
		sem_generate_conocc(&n,out,alist_ptr(in->kept.list,i),SEM_RULE_LEVEL_KEPT); /* TODO check return==1 */
	}
	for (int i=0; i<alist_len(in->removed.list); i++) {
		sem_generate_conocc(&n,out,alist_ptr(in->removed.list,i),SEM_RULE_LEVEL_REM); /* TODO check return==1 */
	}
	for (int i=0; i<alist_len(in->body.list); i++) {
		sem_generate_conocc(&n,out,alist_ptr(in->body.list,i),SEM_RULE_LEVEL_BODY); /* TODO check return==1 */
	}
	sem_rule_hnf(&n);
	alist_add(out->rules,n);
}

void sem_generate_cons(sem_cchr_t *out,constr_t *in) {
  sem_constr_t n;
  sem_constr_init(&n,copy_string(in->name));
  for (int i=0; i<alist_len(in->list); i++) {
  	alist_add(n.types,copy_string(alist_get(in->list,i)));
  }
  alist_add(out->cons,n);
}

void sem_generate_cchr(sem_cchr_t *out,cchr_t *in) {
  sem_cchr_init(out);
  for (int i=0; i<alist_len(in->exts); i++) {
    alist_add(out->exts,copy_string(alist_get(in->exts,i)));
  }
  for (int i=0; i<alist_len(in->constrs); i++) {
  	sem_generate_cons(out,alist_ptr(in->constrs,i));
  }
  for (int i=0; i<alist_len(in->rules); i++) {
  	sem_generate_rule(out,alist_ptr(in->rules,i));
  }
}

void process_abstree(cchr_t *in) {
	sem_cchr_t cchr;
	sem_generate_cchr(&cchr,in);
	printf("Semantic tree generated\n");
	sem_cchr_destruct(&cchr);
}
