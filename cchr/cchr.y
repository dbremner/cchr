%{
/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| cchr.y - YACC parser for CHR-in-C code                                     |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef _cchr_y_
#define _cchr_y_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsestr.h"
#include "cchr.tab.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

typedef void *yyscan_t;

void dumpCHR(cchr_t *chr,int level);
int static yyerror(YYLTYPE *loc,yyscan_t scanner,cchr_t *output,int line,char *msg);
int yylex ( YYSTYPE * lvalp, YYLTYPE * llocp, yyscan_t scanner );

void cchr_init(cchr_t *cchr);
void cchr_merge(cchr_t *out,cchr_t *in);
void cchr_genrule(cchr_t *cchr,char *name,exprlist_t *kept,exprlist_t *removed,
                  exprlist_t *guard,exprlist_t *body);

#endif

#define YYLEX_PARAM scanner

%}

%locations
%pure-parser
%error-verbose

%parse-param { yyscan_t scanner }
%parse-param { cchr_t *output }
%parse-param { int base_line }

%union {
  char *lit;
  expr_t expr;
  token_t token;
  constr_t constr;
  cchr_t cchr;
  exprlist_t elist;
}

%token <lit> TOK_CONSTRAINT TOK_TRUE TOK_LCBRAC TOK_RCBRAC TOK_SEMI TOK_COMMA TOK_AT TOK_SIMP TOK_PROP TOK_SPIPE TOK_BSLASH TOK_LRBRAC	     TOK_RRBRAC TOK_FUNC TOK_SYMBAT TOK_CONST TOK_SYMB TOK_OP TOK_EXTERN TOK_BSTRING TOK_STRING TOK_ESTRING

%token TOK_ERROR

%type  <lit> literal type rname string stringparts


%destructor { free($$); } TOK_CONSTRAINT TOK_TRUE TOK_LCBRAC TOK_RCBRAC TOK_SEMI TOK_COMMA TOK_AT TOK_SIMP TOK_PROP TOK_SPIPE TOK_BSLASH TOK_LRBRAC TOK_RRBRAC TOK_FUNC TOK_SYMBAT TOK_CONST TOK_SYMB TOK_OP literal type rname TOK_EXTERN TOK_STRING TOK_BSTRING TOK_ESTRING

%type <constr> typelistc typelist constr carglist
%destructor { destruct_constr_t(&$$); } typelistc typelist constr carglist

%type <expr> tokenlist token etokenlist etoken stoken stokenlist functio
%destructor { destruct_expr_t(&$$); } tokenlist token etokenlist etoken functio

%type <token> arglist
%destructor { destruct_token_t(&$$); } arglist

%type <cchr> constrlist stmt input rule extlist
%destructor { destruct_cchr_t(&$$); } constrlist stmt input rule extlist

%type <elist> exprlist
%destructor { destruct_exprlist_t(&$$); } exprlist

%left TOK_COMMA
%left PRE_ENDALIST
%left PRE_ELIST

%left PRE_ETLIST
%left TOK_RRBRAC

%start main

%%

main : input { *output=$1; }
	 | input TOK_RCBRAC { *output=$1; 
	   free($2); /* dumpCHR(output, 1); */ 
	   YYACCEPT; }
     ;

input : { cchr_init(&$$); }
        | input stmt { $$=$1; cchr_merge(&$$,&$2); }
        ;

tokenlist : tokenlist token { $$.list=$1.list; alist_addall($$.list,$2.list); alist_free($2.list); }
          | %prec PRE_ETLIST { alist_init($$.list); }
          ;

etokenlist : etokenlist etoken { $$.list=$1.list; alist_addall($$.list,$2.list); alist_free($2.list); }
           | %prec PRE_ETLIST { alist_init($$.list); }
           ;

stokenlist : stokenlist stoken { $$.list=$1.list; alist_addall($$.list,$2.list); alist_free($2.list); }
           | %prec PRE_ETLIST { alist_init($$.list); }
           ;

functio : TOK_FUNC arglist TOK_RRBRAC { 
    		alist_init($$.list);
		    $2.data=$1;
		    alist_add($$.list,$2);
		    free($3);
		}
		| TOK_FUNC TOK_RRBRAC { 
   		    alist_init($$.list);
		    token_t *tok;
		    alist_new($$.list,tok);
		    alist_init(tok->args);
		    tok->type=TOKEN_TYPE_FUNC;
		    tok->data=$1;
		    free($2);
		}

token : literal { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); }
	  | functio
	  | string  { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; alist_init(tok->args); }
	  | TOK_LCBRAC stokenlist TOK_RCBRAC { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; alist_addall($$.list,$2.list); alist_new($$.list,tok); tok->data=$3; tok->type=TOKEN_TYPE_LIT; alist_free($2.list); }
      | TOK_SYMB  { 
   		    alist_init($$.list);
		    token_t *tok;
		    alist_new($$.list,tok);
		    tok->data=$1;
		    tok->type=TOKEN_TYPE_SYMB;
		    alist_init(tok->args);

		  }
	  | TOK_LRBRAC TOK_RRBRAC {
   		    alist_init($$.list);
		    token_t *tok;
		    alist_new($$.list,tok);
		    alist_init(tok->args);
		    tok->type=TOKEN_TYPE_FUNC;
		    tok->data=NULL;
		    free($2);
		    free($1);
	  }
      | TOK_LRBRAC arglist TOK_RRBRAC { 
    		alist_init($$.list);
		    $2.data=NULL;
		    alist_add($$.list,$2);
		    free($3);
		    free($1);
		}
      ;

etoken : token
	   | TOK_SPIPE { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; }
	   | TOK_SYMBAT { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_SYMB; alist_new($$.list,tok); tok->data=malloc(2); strcpy(tok->data,"@"); tok->type=TOKEN_TYPE_LIT;}
	   ;

stoken : etoken
       | TOK_SEMI { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; }
	   ;

exprlist : TOK_TRUE { free($1); alist_init($$.list); }
		 | tokenlist %prec PRE_ELIST { alist_init($$.list); alist_add($$.list,$1); }
		 | exprlist TOK_COMMA tokenlist { $$=$1; alist_add($$.list,$3); free($2); }
		 ;

string : TOK_BSTRING stringparts TOK_ESTRING { $$=malloc(strlen($1)+strlen($2)+strlen($3)+1); strcpy($$,$1); strcat($$,$2); strcat($$,$3); free($1); free($2); free($3); }
	   ;

stringparts : { $$=malloc(1); $$[0]=0; }
			| stringparts TOK_STRING { 
				$$=malloc(strlen($1)+strlen($2)+1);
				strcpy($$,$1);
				strcat($$,$2);
				free($1);
				free($2);
			  }
			;

arglist : etokenlist %prec PRE_ENDALIST { $$.type = TOKEN_TYPE_FUNC; alist_init($$.args); $$.data=NULL; alist_add($$.args,$1); }
		 | arglist TOK_COMMA etokenlist { $$=$1; alist_add($$.args,$3); free($2); }

extlist : TOK_SYMB { cchr_init(&$$); alist_add($$.exts,$1); }
         | extlist TOK_COMMA TOK_SYMB { $$=$1; alist_add($$.exts,$3); free($2); }
	 
literal : TOK_COMMA
        | TOK_CONST
        | TOK_OP
        | TOK_AT
        ;

rname : TOK_SYMBAT { $$=$1; }
      | { $$=NULL; }
      ;

rule : rname exprlist TOK_BSLASH exprlist TOK_SIMP exprlist TOK_SPIPE exprlist TOK_SEMI { cchr_genrule(&$$,$1,&$2,&$4,&$6,&$8); free($3); free($5); free($7); free($9); }
     | rname exprlist TOK_SIMP exprlist TOK_SPIPE exprlist TOK_SEMI { cchr_genrule(&$$,$1,NULL,&$2,&$4,&$6); free($3); free($5); free($7); }
     | rname exprlist TOK_PROP exprlist TOK_SPIPE exprlist TOK_SEMI { cchr_genrule(&$$,$1,&$2,NULL,&$4,&$6); free($3); free($5); free($7); }
     | rname exprlist TOK_BSLASH exprlist TOK_SIMP exprlist TOK_SEMI { cchr_genrule(&$$,$1,&$2,&$4,NULL,&$6); free($3); free($5); free($7); }
     | rname exprlist TOK_SIMP exprlist TOK_SEMI { cchr_genrule(&$$,$1,NULL,&$2,NULL,&$4); free($3); free($5); }
     | rname exprlist TOK_PROP exprlist TOK_SEMI { cchr_genrule(&$$,$1,&$2,NULL,NULL,&$4); free($3); free($5); }
     ;


stmt : TOK_CONSTRAINT constrlist TOK_SEMI { $$=$2; free($1); free($3); }
     | TOK_EXTERN extlist TOK_SEMI { $$=$2; free($1); free($3); }
     | rule
     ;


constrlist : constr { cchr_init(&$$); alist_add($$.constrs,$1); }
		   | constrlist TOK_COMMA constr { $$=$1; alist_add($$.constrs,$3); free($2); }
		   ;

carglist : { alist_init($$.args); alist_init($$.list); $$.name=NULL; }
		 | carglist functio { alist_add($1.args,$2); $$=$1; }
		 ;

constr : TOK_FUNC typelist TOK_RRBRAC carglist { $$=$2; $$.name=$1; free($3); $$.args=$4.args; }


typelist :	{ $$.name=NULL; alist_init($$.list); }
		 | typelistc    { $$ = $1; }
		 ;

typelistc : type		{ $$.name=NULL; alist_init($$.list); alist_add($$.list,$1); }
		  | typelistc TOK_COMMA type { $$=$1; alist_add($$.list,$3); free($2); }
		  ;

type : TOK_SYMB { $$ = $1; }
	 | type TOK_SYMB { $$ = realloc($1,strlen($1)+strlen($2)+2); strcat($$," "); strcat($$,$2); free($2); }
	 ;

%%

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
  printIndent(level); fprintf(stderr,"nGuard=%i;\n",alist_len(rule->guard.list));
  int j4=0;
  while (j4<alist_len(rule->guard.list)) {
    printIndent(level); fprintf(stderr,"guard[%i]='",j4); dumpExpr(alist_ptr(rule->guard.list,j4)); fprintf(stderr,"';\n");
    j4++;
  }
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
  printIndent(level); fprintf(stderr,"nExts=%i;\n",alist_len(cchr->exts));
  int l=0;
  while (l<alist_len(cchr->exts)) {
    printIndent(level); fprintf(stderr,"ext[%i]='%s'\n",l,alist_get(cchr->exts,l));
    l++;
  }
  level--;
  printIndent(level); fprintf(stderr,"}\n");
}

void cchr_init(cchr_t *cchr) {
  alist_init(cchr->constrs);
  alist_init(cchr->rules);
  alist_init(cchr->exts);
}

void cchr_merge(cchr_t *out,cchr_t *in) {
  alist_addall(out->constrs,in->constrs);
  alist_addall(out->rules,in->rules);
  alist_addall(out->exts,in->exts);
  alist_free(in->constrs);
  alist_free(in->rules);
  alist_free(in->exts);
}

void cchr_genrule(cchr_t *cchr,char *name,exprlist_t *kept,exprlist_t *removed,exprlist_t *guard,exprlist_t *body) {
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

int static yyerror(YYLTYPE *loc,yyscan_t scanner,cchr_t *output,int base_line,char *msg) {
  fprintf(stderr,"Parse error on line %i: %s\n",loc->last_line+base_line,msg);
  return 1;
}


