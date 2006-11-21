#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "semtree.h"
#include "alist.h"

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
	tsize+=snprintf(out+tsize,size-tsize,"_%s%i",rem ? "simp" : "prop",ro->pos+1);
	return tsize;
}

void static csm_generate_code(sem_cchr_t *cchr,int cons,int occ,FILE *out) {
	sem_constr_t *ptr=alist_ptr(cchr->cons,cons);
	int rem=1;
	if (occ>=alist_len(ptr->occ[1])) {
		rem=0;
		occ-=alist_len(ptr->occ[1]);
	}
	sem_ruleocc_t *ro=alist_ptr(ptr->occ[rem],occ);
	char buf[256];
	csm_conocc_getname(cchr,cons,occ,buf,256);
	
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
			fprintf(out,"DEF(%s,%i,%s)",conn,j+1,alist_get(con->types,j));
		}
		fprintf(out,"\n");
		
		fprintf(out,"#undef RULELIST_%s\n",conn);
		fprintf(out,"#define RULELIST_%s(DEF,SEP) ",conn);
		for (int j=0; j<alist_len(con->occ[0])+alist_len(con->occ[1]); j++) {
			if (j) fprintf(out," SEP ");
			csm_conocc_getname(in,i,j,buf,256);
			fprintf(out,"DEF(%s)",buf);
		}
		fprintf(out,"\n\n");
		
	}
	
}
