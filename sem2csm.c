

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "semtree.h"
#include "alist.h"

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

void static csm_output_indented(int level,FILE *out) {
	const char spc[]="                                                                             ";
	fprintf(out,"%.*s",level*2,spc);
}

int static csm_constr_getname(sem_cchr_t *cchr,int cons,char *out,int size) {
	sem_constr_t *ptr=alist_ptr(cchr->cons,cons);
	return snprintf(out,size,"%s_%i",ptr->name,alist_len(ptr->types));
}

int static csm_rule_getname(sem_cchr_t *cchr,int rule,char *out,int size) {
	sem_rule_t *ptr=alist_ptr(cchr->rules,rule);
	if (ptr->name) {
		return snprintf(out,size,"%s",ptr->name);
	} else {
		return snprintf(out,size,"%iR",rule+1);
	}
}

int static csm_conocc_getname(sem_cchr_t *cchr,int cons,int occ,char *out,int size) {
	sem_constr_t *ptr=alist_ptr(cchr->cons,cons);
	int rem=1;
	if (occ>=alist_len(ptr->occ[1])) {
		rem=0;
		occ-=alist_len(ptr->occ[1]);
	}
	int tsize=0;
	sem_ruleocc_t *ro=alist_ptr(ptr->occ[rem],occ);
	tsize+=csm_constr_getname(cchr,cons,out+tsize,size-tsize);
	tsize+=snprintf(out+tsize,size-tsize,"_");
	tsize+=csm_rule_getname(cchr,ro->rule,out+tsize,size-tsize);
	tsize+=snprintf(out+tsize,size-tsize,"_%s%i",rem ? "R" : "K",ro->pos+1);
	return tsize;
}

char static **csm_generate_vartable(sem_cchr_t *chr,sem_rule_t *rule,int arem,int aid) {
	char **tbl=malloc(sizeof(char*)*alist_len(rule->vars));
	for (int i=0; i<alist_len(rule->vars); i++) {
		int found=0;
		sem_var_t *var=alist_ptr(rule->vars,i);
		sem_rule_level_t isrem=var->occ[SEM_RULE_LEVEL_REM] ? SEM_RULE_LEVEL_REM : SEM_RULE_LEVEL_KEPT;
		for (int j=0; j<alist_len(rule->con[isrem]); j++) {
			sem_conocc_t *co=alist_ptr(rule->con[isrem],j);
			for (int k=0; k<alist_len(co->args); k++) {
				if (alist_get(co->args,k).var==i) {
					char cona[256];
					csm_constr_getname(chr,co->constr,cona,256);
					if (arem==isrem && j==aid) {
						tbl[i]=make_message("CSM_ARG(%s,arg%i)",cona,k+1);
					} else {
						tbl[i]=make_message("CSM_LARG(%s,%s%i,arg%i)",cona,isrem ? "R" : "K",j+1,k+1);
					} 
					found=1;
					break; 
				}
			}
			if (found) break;
		}
	}
	return tbl;
}

void static csm_destruct_vartable(sem_rule_t *rule,char **tbl) {
	for (int u=0; u<alist_len(rule->vars); u++) free(tbl[u]);
	free(tbl);
}

void static csm_generate_expr(sem_expr_t *expr,char **tbl,FILE *out) {
	for (int t=0; t<alist_len(expr->parts); t++) {
		if (t) fprintf(out," ");
		sem_exprpart_t *ep=alist_ptr(expr->parts,t);
		switch (ep->type) {
			case SEM_EXPRPART_TYPE_LIT: {
				fprintf(out,"%s",ep->data.lit);
				break;
			}
			case SEM_EXPRPART_TYPE_VAR: {
				fprintf(out,"%s",tbl[ep->data.var]);
				break;
			}
		}
	}
}

int static csm_generate_guard(sem_cchr_t *chr,sem_rule_t *rule,char **tbl,FILE *out,int level) {
	if (alist_len(rule->guard)>0) {
		csm_output_indented(level,out);
		fprintf(out,"CSM_IF(");
		for (int s=0; s<alist_len(rule->guard); s++) {
			if (s) fprintf(out," && ");
			fprintf(out,"(");
			sem_expr_t *expr=alist_ptr(rule->guard,s);
			csm_generate_expr(expr,tbl,out);
			fprintf(out,")");
		}
		fprintf(out,", \\\n");
		level++;
	}
	return level;
}

int static csm_generate_body(sem_cchr_t *cchr,sem_rule_t *rule,int arem,int aid,char **tbl,FILE *out,int level) {
	for (int i=0; i<alist_len(rule->con[SEM_RULE_LEVEL_BODY]); i++) {
		sem_conocc_t *co=alist_ptr(rule->con[SEM_RULE_LEVEL_BODY],i);
		for (int j=0; j<alist_len(co->args); j++) {
			csm_output_indented(level,out);
			fprintf(out,"CSM_SETLOCAL(%s,B%i_arg%i,",alist_get(alist_get(cchr->cons,co->constr).types,j),i+1,j+1);
			csm_generate_expr(&(alist_get(co->args,j).expr),tbl,out);
			fprintf(out,") \\\n");
		}
		
	}
	for (int k=0; k<alist_len(rule->con[SEM_RULE_LEVEL_REM]); k++) {
		if (!arem || aid!=k) {
			csm_output_indented(level,out);
			fprintf(out,"CSM_KILL(R%i) \\\n",k+1);
		}
	}
	if (arem) {
		csm_output_indented(level,out);
		fprintf(out,"CSM_KILLSELF \\\n");
	} else {
		csm_output_indented(level,out);
		fprintf(out,"CSM_NEEDSELF \\\n");
	}
	for (int k=0; k<alist_len(rule->con[SEM_RULE_LEVEL_BODY]); k++) {
		sem_conocc_t *co=alist_ptr(rule->con[SEM_RULE_LEVEL_BODY],k);
		char con[256];
		csm_constr_getname(cchr,co->constr,con,256);
		if (alist_len(co->args)==0) {
			csm_output_indented(level,out);
			fprintf(out,"CSM_ADDE(%s) \\\n",con);
		} else {
			csm_output_indented(level,out);
			fprintf(out,"CSM_ADD(%s",con);
			for (int l=0; l<alist_len(co->args); l++) {
				fprintf(out,",CSM_GETLOCAL(B%i_arg%i)",k+1,l+1);
			}
			fprintf(out,") \\\n");
		}
	}
	if (arem) {
		csm_output_indented(level,out);
		fprintf(out,"CSM_END \\\n");
	} else {
		csm_output_indented(level,out);
		fprintf(out,"CSM_IF(!CSM_ALIVESELF || CSM_REGENSELF,CSM_END) \\\n");
	}
	return level;
}

void static csm_generate_code(sem_cchr_t *cchr,int cons,int occ,FILE *out) {
	char buf[256];
	csm_conocc_getname(cchr,cons,occ,buf,256);
	char buf2[256];
	csm_constr_getname(cchr,cons,buf2,256);
	sem_constr_t *con=alist_ptr(cchr->cons,cons);
	int rem=1;
	if (occ>=alist_len(con->occ[1])) {
		rem=0;
		occ-=alist_len(con->occ[1]);
	}
	sem_ruleocc_t *ro=alist_ptr(con->occ[rem],occ);
	sem_rule_t *ru=alist_ptr(cchr->rules,ro->rule);
	
	fprintf(out,"\n");
	fprintf(out,"#undef CODELIST_%s\n",buf);
	fprintf(out,"#define CODELIST_%s \\\n",buf);
	int level=1;
	if (!rem) {
		csm_output_indented(level,out);
		fprintf(out,"CSM_MAKE(%s) \\\n",buf2);
	}
	int ncons=alist_len(ru->con[SEM_RULE_LEVEL_KEPT])+alist_len(ru->con[SEM_RULE_LEVEL_REM]);
	for (int ci=0; ci<ncons; ci++) {
		int ci_rem=1,cid=ci;
		if (ci>=alist_len(ru->con[SEM_RULE_LEVEL_REM])) { 
			cid-= alist_len(ru->con[SEM_RULE_LEVEL_REM]); 
			ci_rem=0;
		}
		if (cid!=ro->pos || ci_rem!=rem) {
			int cicon=alist_get(ru->con[ci_rem],cid).constr;
			char cicon_name[256];
			csm_constr_getname(cchr,cicon,cicon_name,256);
			csm_output_indented(level,out);
			fprintf(out,"CSM_LOOP(%s,%s%i, \\\n",cicon_name,ci_rem ? "R" : "K",cid+1);
			level++;
			int conlo=0;
			for (int ci2=0; ci2<ncons; ci2++) {
				int ci2_rem=1,ci2d=ci2;
				if (ci2>=alist_len(ru->con[SEM_RULE_LEVEL_REM])) { 
					ci2d-= alist_len(ru->con[SEM_RULE_LEVEL_REM]); 
					ci2_rem=0;
				}
				int cicon2=alist_get(ru->con[ci2_rem],ci2d).constr;
				if ((ci2<ci || (ci2_rem==rem && ci2d==ro->pos)) && (cicon2==cicon)) { 
					if (conlo==0) {
						csm_output_indented(level++,out);
						fprintf(out,"CSM_IF(");
					} else {
						fprintf(out," && ");
					}
					conlo++;
					if (ci2d==ro->pos && ci2_rem==rem) {
						fprintf(out,"CSM_DIFFSELF(%s%i),",ci_rem ? "R" : "K",cid+1);
					} else {
						fprintf(out,"CSM_DIFF(%s%i,%s%i),",ci_rem ? "R" : "K",cid+1,ci2_rem ? "R" : "K",ci2d+1);
					}
				}
				
			}
			if (conlo) fprintf(out," \\\n");
		}
	}
	char **tbl=csm_generate_vartable(cchr,ru,rem,ro->pos);
	level=csm_generate_guard(cchr,ru,tbl,out,level);
	level=csm_generate_body(cchr,ru,rem,ro->pos,tbl,out,level);
	csm_destruct_vartable(ru,tbl);
	while (level>2) {
		level--;
		csm_output_indented(level,out);
		fprintf(out,") \\\n");
	}
	level--;
	csm_output_indented(level,out);
	fprintf(out,")\n\n");
}

void csm_generate(sem_cchr_t *in,FILE *out) {
	char buf[256];
	fprintf(out,"#undef CONSLIST\n");
	fprintf(out,"#define CONSLIST(DEF,SEP) ");
	for (int i=0; i<alist_len(in->cons); i++) {
		if (i) fprintf(out," SEP ");
		csm_constr_getname(in,i,buf,256);
		fprintf(out,"DEF(%s)",buf);
	}
	fprintf(out,"\n\n");
	for (int i=0; i<alist_len(in->cons); i++) {
		sem_constr_t *con=alist_ptr(in->cons,i);
		char conn[256];
		csm_constr_getname(in,i,conn,256);
		fprintf(out,"#undef ARGLIST_%s\n",conn);
		fprintf(out,"#define ARGLIST_%s(DEF,SEP) ",conn);
		for (int j=0; j<alist_len(con->types); j++) {
			if (j) fprintf(out," SEP ");
			fprintf(out,"DEF(%s,arg%i,%s)",conn,j+1,alist_get(con->types,j));
		}
		fprintf(out,"\n");
		fprintf(out,"#undef RULELIST_%s\n",conn);
		fprintf(out,"#define RULELIST_%s(DEF,SEP) ",conn);
		for (int j=0; j<alist_len(con->occ[0])+alist_len(con->occ[1]); j++) {
			if (j) fprintf(out," SEP ");
			csm_conocc_getname(in,i,j,buf,256);
			fprintf(out,"DEF(%s)",buf);
		}
		fprintf(out,"\n");
		for (int j=0; j<alist_len(con->occ[0])+alist_len(con->occ[1]); j++) {
			csm_generate_code(in,i,j,out);
		}
		fprintf(out,"\n");
	}
	fprintf(out,"#include \"cchr_csm.h\"\n");
}
