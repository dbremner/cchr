%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsestr.h"

%}

%union {
  char *lit;
  expr_t expr;
  token_t token;
  constr_t constr;
  cchr_t cchr;
}

%token <lit> TOK_CONSTRAINT TOK_EXTERN TOK_TRUE TOK_LCBRAC TOK_RCBRAC TOK_SEMI TOK_COMMA TOK_AT TOK_SIMP TOK_PROP TOK_SPIPE TOK_BSLASH TOK_LRBRAC TOK_RRBRAC
%token <lit> TOK_CONST TOK_SYMB TOK_OP

%type  <lit> literal type

%type <constr> typelistc typelist constr

%type <expr> tokenlist token

%type <token> arglist arglistc

%type <cchr> constrlist stmt

%%

/* input :   
      | input stmt
      ; */

tokenlist : tokenlist token { $$.list=$1.list; alist_addall($$.list,$2.list); alist_free($2.list); }
          |                 { alist_init($$.list); }
          ;

token : literal                     { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; }
      | TOK_SYMB TOK_LRBRAC arglist TOK_RRBRAC { $$=$3; $$.name=$1.data; }
      | TOK_SYMB                    { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_SYMB; }
      | TOK_LRBRAC tokenlist TOK_RRBRAC { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=malloc(sizeof($1)+1); strcpy(tok->data,$1); tok->type=TOKEN_TYPE_LIT; alist_addall($$.list,$2.list); alist_new($$.list,tok); tok->data=malloc(sizeof($3)+1); strcpy(tok->data,$3); tok->type=TOKEN_TYPE_LIT; alist_free($2.list); }
      ;

arglist : { $$.type = TOKEN_TYPE_FUNC; alist_init($$.args); $$.data=NULL; }
		| arglistc { $$ = $1; }

arglistc : tokenlist { $$.type = TOKEN_TYPE_FUNC; alist_init($$.args); $$.data=NULL; alist_add($$.args,$1); }
		 | arglistc TOK_COMMA tokenlist { $$=$1; alist_add($$.args,$3); }

literal : TOK_COMMA                     { $$ = $1; }
        | TOK_SPIPE                     { $$ = $1; }
        | TOK_CONST                     { $$ = $1; }
        | TOK_OP                        { $$ = $1; }
        ;

stmt : TOK_CONSTRAINT constrlist { $$=$2; }
	 ;

constrlist : constr { alist_init($$.constrlist); alist_add($$.constrlist,$1; }
		   | constrlist TOK_COMMA constr { $$=$1; alist_add($$.constrlist,$3); }
		   ;

constr : TOK_SYMB TOK_LRBRAC typelist TOK_RBRAC { $$=$3; $$.name=$1.data; }
     
typelist :				{ $$.name=NULL; alist_init($$.list); }
		 | typelistc    { $$ = $1; }
		 ;

typelistc : type		{ $$.name=NULL; alist_init($$.list); alist_add($$.list,$1.data); }
		  | typelistc TOK_COMMA type { $$=$1; alist_add($$.list,$3.data; }
		  ;

type : TOK_SYMB { $$ = $1; }
	 | type TOK_SYMB { $$ = realloc($$,strlen($$)+strlen($1)+2); strcat($$," "); strcat($$,$1); }
	 ;

%%

void yyerror(char *message)
{
  printf("%s\n",message);
  return 0;
}

int main(int argc, char *argv[])
{
  yyparse();
  return(0);
}








