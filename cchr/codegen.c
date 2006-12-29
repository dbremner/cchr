/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| sem2csm.c - Conversion of semantic tree to C output (using CSM)            |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "semtree.h"
#include "alist.h"
#include "output.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

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

char static **csm_generate_vartable_constr(sem_cchr_t *chr,int coni) {
	sem_constr_t *co=alist_ptr(chr->cons,coni);
	char c[256];
	csm_constr_getname(chr,coni,c,256);
	char **tbl=malloc(sizeof(char*)*alist_len(co->types));
	for (int i=0; i<alist_len(co->types); i++) {
		tbl[i]=make_message("_arg_%i",i+1);
	}
	return tbl;
}

/* generate variable-access table (array of char*'s, each pointing to the code to be used for accessing variable corresponding to array index) */ 
char static **csm_generate_vartable_rule(sem_cchr_t *chr,sem_rule_t *rule,int arem,int aid) {
	char **tbl=malloc(sizeof(char*)*alist_len(rule->vt.vars));
	for (int i=0; i<alist_len(rule->vt.vars); i++) {
		sem_var_t *var=alist_ptr(rule->vt.vars,i);
		if (var->local) { /* local variables are accessed as LOCAL's in CSM */
			tbl[i]=make_message("CSM_LOCAL(%s)",var->name);
		} else { /* variable defined by head of rule */
			sem_rule_level_t isrem=var->occ[SEM_RULE_LEVEL_REM] ? SEM_RULE_LEVEL_REM : SEM_RULE_LEVEL_KEPT;
			int j=var->pos; /* what constraint occurrence in the rule defines it */
			sem_conocc_t *co=alist_ptr(rule->head[isrem],j);
			int k=var->poss; /* search which argument of that constraint defines it */
			char cona[256];
			csm_constr_getname(chr,co->constr,cona,256);
			if (arem==isrem && j==aid) { /* if this is the active rule, use ARG instead of LARG */
				tbl[i]=make_message("CSM_ARG(%s,arg%i)",cona,k+1);
			} else {
				tbl[i]=make_message("CSM_LARG(%s,%s%i,arg%i)",cona,isrem ? "R" : "K",j+1,k+1);
			} 
		}
	}
	return tbl;
}

char static **csm_generate_vartable_rule_cached(sem_cchr_t *chr,sem_rule_t *rule,int arem,int aid) {
	char **tbl=malloc(sizeof(char*)*alist_len(rule->vt.vars));
	for (int i=0; i<alist_len(rule->vt.vars); i++) {
		sem_var_t *var=alist_ptr(rule->vt.vars,i);
		tbl[i]=make_message("CSM_LOCAL(%s)",var->name);
	}
	return tbl;
}

/* nice destructor for the variable table */
void static csm_destruct_vartable_rule(sem_rule_t *rule,char **tbl) {
	for (int u=0; u<alist_len(rule->vt.vars); u++) free(tbl[u]);
	free(tbl);
}

/* nice destructor for the variable table */
void static csm_destruct_vartable_constr(sem_constr_t *con,char **tbl) {
	for (int u=0; u<alist_len(con->types); u++) free(tbl[u]);
	free(tbl);
}

/* generate code for an expression (as a C expression) */
void static csm_generate_expr(sem_expr_t *expr,char **tbl,output_t *out) {
	int dos=0;
	for (int t=0; t<alist_len(expr->parts); t++) {
		if (dos) output_fmt(out," ");
		dos=1;
		sem_exprpart_t *ep=alist_ptr(expr->parts,t);
		switch (ep->type) {
			case SEM_EXPRPART_TYPE_LIT: {
				if (!strcmp(ep->data.lit,"}")) {output_unindent(out);dos=0;}
				output_fmt(out,"%s",ep->data.lit);
				if (!strcmp(ep->data.lit,"}")) {output_string(out," \\\n");}
				if (!strcmp(ep->data.lit,";")) {output_string(out," \\\n");dos=0;}
				if (!strcmp(ep->data.lit,"{")) {output_indent(out," \\","");dos=0;}
				break;
			}
			case SEM_EXPRPART_TYPE_VAR: {
				output_fmt(out,"%s",tbl[ep->data.var]);
				break;
			}
		}
	}
}

void static csm_generate_varcache(sem_cchr_t *chr,sem_rule_t *rule, output_t *out,char **table, int body) {
	for (int l=0; l<alist_len(rule->vt.vars); l++) {
		sem_var_t *var=alist_ptr(rule->vt.vars,l);
		if (!var->local && (var->occ[SEM_RULE_LEVEL_GUARD] || var->occ[SEM_RULE_LEVEL_BODY] || (body && var->occ[SEM_RULE_LEVEL_REM])) && (var->occ[SEM_RULE_LEVEL_GUARD]==0)==body) {
			output_fmt(out,"CSM_IMMLOCAL(%s,%s,%s) \\\n",var->type,var->name,table[l]);
		}
	}
}

void static csm_generate_out(sem_cchr_t *chr,sem_rule_t *rule,char **tbl,output_t *out,int body) {
	int ncon=0;
	int l=0;
	while (l<alist_len(rule->out[body])) {
		sem_out_t *so=alist_ptr(rule->out[body],l);
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
				ncon++;
				break;
			}
			case SEM_OUT_TYPE_EXP: {
				int len=1;
				output_fmt(out,"CSM_IF(");
				while (l+len<alist_len(rule->out[body]) && alist_get(rule->out[body],l).type==SEM_OUT_TYPE_EXP) len++;
				int p=l;
				while (p<len+l) {
					if (p>l) output_fmt(out," && ");
					if (len>1) output_fmt(out,"(");
					csm_generate_expr(&(alist_get(rule->out[body],p).data.exp),tbl,out);
					if (len>1) output_fmt(out,")");
					p++;
				}
				l=p-1; /* skip mulitiple guards */
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
		l++;
	}
}

/* generate codelist for a constraint occurence */
void static csm_generate_code(sem_cchr_t *cchr,int cons,int occ,output_t *out) {
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
	
	output_fmt(out,"\n");
	output_fmt(out,"#undef CODELIST_%s\n",buf);
	output_fmt(out,"#define CODELIST_%s ",buf);
	output_indent(out," \\","");
	if (!rem) {
		output_fmt(out,"CSM_MAKE(%s) \\\n",buf2);
	}
	int ncons=alist_len(ru->head[SEM_RULE_LEVEL_KEPT])+alist_len(ru->head[SEM_RULE_LEVEL_REM]);
	for (int ci=0; ci<ncons; ci++) {
		int ci_rem=1,cid=ci;
		if (ci>=alist_len(ru->head[SEM_RULE_LEVEL_REM])) { 
			cid-= alist_len(ru->head[SEM_RULE_LEVEL_REM]); 
			ci_rem=0;
		}
		if (cid!=ro->pos || ci_rem!=rem) {
			int cicon=alist_get(ru->head[ci_rem],cid).constr;
			char cicon_name[256];
			csm_constr_getname(cchr,cicon,cicon_name,256);
			output_fmt(out,"CSM_LOOP(%s,%s%i,",cicon_name,ci_rem ? "R" : "K",cid+1);
			output_indent(out," \\",") \\");
			int conlo=0;
			for (int ci2=0; ci2<ncons; ci2++) {
				int ci2_rem=1,ci2d=ci2;
				if (ci2>=alist_len(ru->head[SEM_RULE_LEVEL_REM])) { 
					ci2d-= alist_len(ru->head[SEM_RULE_LEVEL_REM]); 
					ci2_rem=0;
				}
				int cicon2=alist_get(ru->head[ci2_rem],ci2d).constr;
				if ((ci2<ci || (ci2_rem==rem && ci2d==ro->pos)) && (cicon2==cicon)) { 
					if (conlo==0) {
						output_fmt(out,"CSM_IF(");
					} else {
						output_fmt(out," && ");
					}
					conlo++;
					if (ci2d==ro->pos && ci2_rem==rem) {
						output_fmt(out,"CSM_DIFFSELF(%s%i),",ci_rem ? "R" : "K",cid+1);
					} else {
						output_fmt(out,"CSM_DIFF(%s%i,%s%i),",ci_rem ? "R" : "K",cid+1,ci2_rem ? "R" : "K",ci2d+1);
					}
				}
				
			}
			if (conlo) output_indent(out," \\",") \\");
		}
	}
	char **tbl=csm_generate_vartable_rule(cchr,ru,rem,ro->pos);
	char **tbl_c=csm_generate_vartable_rule_cached(cchr,ru,rem,ro->pos);
	char *end=NULL;
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
	csm_generate_varcache(cchr,ru,out,tbl,0);
	csm_generate_out(cchr,ru,tbl_c,out,0);
	csm_generate_varcache(cchr,ru,out,tbl,1);
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
            output_fmt(out,"CSM_NEEDSELF \\\n");
        }
        if (ru->hook>=0) {
            output_fmt(out,"CSM_HISTADD(%s%s\n",buf3,end);
        }
	csm_generate_out(cchr,ru,tbl_c,out,1);
	for (int k=0; k<alist_len(ru->head[SEM_RULE_LEVEL_REM]); k++) {
		sem_conocc_t *co=alist_ptr(ru->head[SEM_RULE_LEVEL_REM],k);
		char cc[256];
		csm_constr_getname(cchr,co->constr,cc,256);
		output_fmt(out,alist_len(co->args) ? "CSM_DESTRUCT(%s" : "CSM_DESTRUCTE(%s",cc);
		for (int l=0; l<alist_len(co->args); l++) {
		    output_fmt(out,",%s",tbl_c[alist_get(co->args,l)]);
		}
		output_fmt(out,") \\\n");
	}
	if (rem) {
		output_fmt(out,"CSM_END \\\n");
	} else {
		char cc[256];
		csm_constr_getname(cchr,alist_get(ru->head[rem ? SEM_RULE_LEVEL_REM : SEM_RULE_LEVEL_KEPT],ro->pos).constr,cc,256);
		output_fmt(out,"CSM_IF(!CSM_ALIVESELF || CSM_REGENSELF, CSM_STROUT(\"abort\") CSM_END) \\\n");
	}
	csm_destruct_vartable_rule(ru,tbl);
	csm_destruct_vartable_rule(ru,tbl_c);
	output_unindent_till(out,0);
	free(end);
	output_char(out,'\n');
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
		char **vt=csm_generate_vartable_constr(in,i);
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
			if (g) output_string(out," CB##_S ");
			char bfk[256];
			csm_rule_getname(in,alist_get(con->hooked,g),bfk,256);
			output_fmt(out,"CB##_D(%s,%s,__VA_ARGS__)",conn,bfk);
		}
		output_string(out,"\n");
		for (int j=0; j<alist_len(con->occ); j++) {
			sem_ruleocc_t *cs=alist_ptr(con->occ,j);
			if (cs->type==SEM_RULE_LEVEL_KEPT || cs->type==SEM_RULE_LEVEL_REM) {
				csm_generate_code(in,i,j,out);
			}
		}
		csm_destruct_vartable_constr(con,vt);
		output_fmt(out,"\n");
	}
	output_fmt(out,"#include \"cchr_csm.h\"\n");
}
