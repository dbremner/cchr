%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsestr.h"

void dumpCHR(cchr_t *chr,int level);
int yylex(void);
void yyerror(char *msn);
void cchr_init(cchr_t *cchr);
void cchr_merge(cchr_t *out,cchr_t *in);
void cchr_genrule(cchr_t *cchr,char *name,exprlist_t *kept,exprlist_t *removed,expr_t *guard,exprlist_t *body);

%}

%union {
  char *lit;
  expr_t expr;
  token_t token;
  constr_t constr;
  cchr_t cchr;
  exprlist_t elist;
}

%token <lit> TOK_CONSTRAINT TOK_TRUE TOK_LCBRAC TOK_RCBRAC TOK_SEMI TOK_COMMA TOK_AT TOK_SIMP TOK_PROP TOK_SPIPE TOK_BSLASH TOK_LRBRAC TOK_RRBRAC TOK_FUNC TOK_SYMBAT
%token <lit> TOK_CONST TOK_SYMB TOK_OP

%type  <lit> literal type rname

%type <constr> typelistc typelist constr

%type <expr> tokenlist token etokenlist etoken

%type <token> arglist

%type <cchr> constrlist stmt main input rule

%type <elist> exprlist

%left TOK_COMMA
%left PRE_ENDALIST
%left PRE_ELIST

%left PRE_ETLIST
%left TOK_RRBRAC

%start main

%%

main : input { dumpCHR(&$1,0); }
     ;

input : { cchr_init(&($$)); }
        | input stmt { $$=$1; cchr_merge(&$$,&$2); }
        ;

tokenlist : tokenlist token { $$.list=$1.list; alist_addall($$.list,$2.list); alist_free($2.list); }
          | %prec PRE_ETLIST { alist_init($$.list); }
          ;

etokenlist : etokenlist etoken { $$.list=$1.list; alist_addall($$.list,$2.list); alist_free($2.list); }
           | %prec PRE_ETLIST { alist_init($$.list); }
           ;

token : literal                     { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; }
      | TOK_FUNC arglist TOK_RRBRAC { alist_init($$.list); $2.data=$1; alist_add($$.list,$2);  }
      | TOK_FUNC TOK_RRBRAC { alist_init($$.list); token_t *tok; alist_new($$.list,tok); alist_init(tok->args); tok->type=TOKEN_TYPE_FUNC; tok->data=$1; }
      | TOK_SYMB  { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_SYMB; }
      | TOK_LRBRAC etokenlist TOK_RRBRAC { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=malloc(sizeof($1)+1); strcpy(tok->data,$1); tok->type=TOKEN_TYPE_LIT; alist_addall($$.list,$2.list); alist_new($$.list,tok); tok->data=malloc(sizeof($3)+1); strcpy(tok->data,$3); tok->type=TOKEN_TYPE_LIT; alist_free($2.list); }
      ;

etoken : token
	   | TOK_SPIPE { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; }
	   | TOK_SYMBAT { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_SYMB; alist_new($$.list,tok); tok->data=malloc(2); strcpy(tok->data,"@"); tok->type=TOKEN_TYPE_LIT;}
	   ;

exprlist : TOK_TRUE { alist_init($$.list); }
		 | tokenlist %prec PRE_ELIST { alist_init($$.list); alist_add($$.list,$1); }
		 | exprlist TOK_COMMA tokenlist { $$=$1; alist_add($$.list,$3); }

arglist : etokenlist %prec PRE_ENDALIST { $$.type = TOKEN_TYPE_FUNC; alist_init($$.args); $$.data=NULL; alist_add($$.args,$1); }
		 | arglist TOK_COMMA etokenlist { $$=$1; alist_add($$.args,$3); }

literal : TOK_COMMA
        | TOK_CONST
        | TOK_OP
        | TOK_AT
        ;

rname : TOK_SYMBAT { $$=$1; }
      | { $$=NULL; }
      ;

rule : rname exprlist TOK_BSLASH exprlist TOK_SIMP tokenlist TOK_SPIPE exprlist TOK_SEMI { cchr_genrule(&$$,$1,&$2,&$4,&$6,&$8); }
	 | rname exprlist TOK_SIMP tokenlist TOK_SPIPE exprlist TOK_SEMI { cchr_genrule(&$$,$1,NULL,&$2,&$4,&$6); }
	 | rname exprlist TOK_PROP tokenlist TOK_SPIPE exprlist TOK_SEMI { cchr_genrule(&$$,$1,&$2,NULL,&$4,&$6); }
     | rname exprlist TOK_BSLASH exprlist TOK_SIMP exprlist TOK_SEMI { cchr_genrule(&$$,$1,&$2,&$4,NULL,&$6); }
	 | rname exprlist TOK_SIMP exprlist TOK_SEMI { cchr_genrule(&$$,$1,NULL,&$2,NULL,&$4); }
	 | rname exprlist TOK_PROP exprlist TOK_SEMI { cchr_genrule(&$$,$1,&$2,NULL,NULL,&$4); }
	 ;

stmt : TOK_CONSTRAINT constrlist TOK_SEMI { $$=$2; }
	 | rule
	 ;

constrlist : constr { cchr_init(&$$); alist_add($$.constrs,$1); }
		   | constrlist TOK_COMMA constr { $$=$1; alist_add($$.constrs,$3); }
		   ;

constr : TOK_FUNC typelist TOK_RRBRAC { $$=$2; $$.name=$1; }
     
typelist :				{ $$.name=NULL; alist_init($$.list); }
		 | typelistc    { $$ = $1; }
		 ;

typelistc : type		{ $$.name=NULL; alist_init($$.list); alist_add($$.list,$1); }
		  | typelistc TOK_COMMA type { $$=$1; alist_add($$.list,$3); }
		  ;

type : TOK_SYMB { $$ = $1; }
	 | type TOK_SYMB { $$ = realloc($$,strlen($$)+strlen($1)+2); strcat($$," "); strcat($$,$1); }
	 ;

%%

int main(int argc, char *argv[])
{
  yyparse();
  return(0);
}

void printIndent(int level) {
  fprintf(stderr,"%.*s",level*2,"                                                                                                  ");
}

void dumpConstr(constr_t *constr,int level) {
  printIndent(level); fprintf(stderr,"constr '%s' {\n",constr->name);
  level++;
  printIndent(level); fprintf(stderr,"nArgs=%i;\n",alist_len(constr->list));
  int j=0;
  while (j<alist_len(constr->list)) {
    printIndent(level); fprintf(stderr,"arg[%i]='%s'\n",j,alist_get(constr->list,j));
    j++;
  }
  level--;
  printIndent(level); fprintf(stderr,"}\n");
}

void dumpExpr(expr_t *expr);
void dumpExpr(expr_t *expr) {
  int j=0;
  while (j<alist_len(expr->list)) {
    if (j>0) fprintf(stderr," ");
    token_t *tok=alist_ptr(expr->list,j);
    if (tok->type == TOKEN_TYPE_LIT) fprintf(stderr,"%s",tok->data);
    if (tok->type == TOKEN_TYPE_SYMB) fprintf(stderr,"sym_%s",tok->data);
    if (tok->type == TOKEN_TYPE_FUNC) {
      fprintf(stderr,"func_%s[",tok->data);
      int l=0;
      while (l<alist_len(tok->args)) {
        if (l>0) fprintf(stderr,"|");
        dumpExpr(alist_ptr(tok->args,l));
        l++;
      }
      fprintf(stderr,"]");
    }
    j++;
  }
}

void dumpRule(rule_t *rule,int level) {
  printIndent(level); fprintf(stderr,"rule '%s' {\n",rule->name ? rule->name : "<anon>");
  level++;
  printIndent(level); fprintf(stderr,"nKept=%i;\n",alist_len(rule->kept.list));
  int j1=0;
  while (j1<alist_len(rule->kept.list)) {
    printIndent(level); fprintf(stderr,"kept[%i]='",j1); dumpExpr(alist_ptr(rule->kept.list,j1)); fprintf(stderr,"';\n");
    j1++;
  }
  printIndent(level); fprintf(stderr,"nRemoved=%i;\n",alist_len(rule->removed.list));
  int j2=0;
  while (j2<alist_len(rule->removed.list)) {
    printIndent(level); fprintf(stderr,"removed[%i]='",j2); dumpExpr(alist_ptr(rule->removed.list,j2)); fprintf(stderr,"';\n");
    j2++;
  }
  printIndent(level); fprintf(stderr,"nBody=%i;\n",alist_len(rule->body.list));
  int j3=0;
  while (j3<alist_len(rule->body.list)) {
    printIndent(level); fprintf(stderr,"body[%i]='",j3); dumpExpr(alist_ptr(rule->body.list,j3)); fprintf(stderr,"';\n");
    j3++;
  }
  printIndent(level); fprintf(stderr,"Guard='"); dumpExpr(&(rule->guard)); fprintf(stderr,"';\n");
  level--;
  printIndent(level); fprintf(stderr,"}\n");
}

void dumpCHR(cchr_t *cchr,int level) {
  printIndent(level); fprintf(stderr,"cchr {\n");
  level++;
  printIndent(level); fprintf(stderr,"nConstraints=%i;\n",alist_len(cchr->constrs));
  int j=0;
  while (j<alist_len(cchr->constrs)) {
    dumpConstr(alist_ptr(cchr->constrs,j),level);
    j++;
  }
  printIndent(level); fprintf(stderr,"nRules=%i;\n",alist_len(cchr->rules));
  int k=0;
  while (k<alist_len(cchr->rules)) {
    dumpRule(alist_ptr(cchr->rules,k),level);
    k++;
  }
  level--;
  printIndent(level); fprintf(stderr,"}\n");
}

void cchr_init(cchr_t *cchr) {
  alist_init(cchr->constrs);
  alist_init(cchr->rules);
}

void cchr_merge(cchr_t *out,cchr_t *in) {
  alist_addall(out->constrs,in->constrs);
  alist_addall(out->rules,in->rules);
  alist_free(in->constrs);
}

void cchr_genrule(cchr_t *cchr,char *name,exprlist_t *kept,exprlist_t *removed,expr_t *guard,exprlist_t *body) {
  cchr_init(cchr);
  rule_t *rule; alist_new(cchr->rules,rule);
  rule->name=name;
  if (kept) {
    rule->kept = *kept;
  } else {
    alist_init(rule->kept.list);
  }
  if (removed) {
    rule->removed = *removed;
  } else {
    alist_init(rule->removed.list);
  }
  if (body) {
    rule->body = *body;
  } else {
    alist_init(rule->body.list);
  }
  if (guard) {
    rule->guard= *guard;
  } else {
    alist_init(rule->guard.list);
  }
}




