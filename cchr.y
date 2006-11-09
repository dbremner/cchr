/*
 * expr.y : A simple yacc expression parser
 *          Based on the Bison manual example. 
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsestr.h"

%}

%union {
  char *lit;
  expr_t expr;
}

%token <lit> TOK_CONSTRAINT TOK_EXTERN TOK_TRUE TOK_LCBRAC TOK_RCBRAC TOK_SEMI TOK_COMMA TOK_AT TOK_SIMP TOK_PROP TOK_SPIPE TOK_BSLASH TOK_LRBRAC TOK_RRBRAC
%token <lit> TOK_CONST TOK_SYMB TOK_OP

%type  <lit> literal

%type <expr> tokenlist token

%%

/* input :   
      | input stmt
      ; */

tokenlist : tokenlist token { $$.list=$1.list; alist_addall($$.list,$2.list); alist_free($2.list); }
          |                 { alist_init($$.list); }
          ;

token : literal                     { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_LIT; }
      | TOK_SYMB                    { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=$1; tok->type=TOKEN_TYPE_SYMB; }
      | TOK_LRBRAC tokenlist TOK_RRBRAC { alist_init($$.list); token_t *tok; alist_new($$.list,tok); tok->data=malloc(sizeof($1)+1); strcpy(tok->data,$1); tok->type=TOKEN_TYPE_LIT; alist_addall($$.list,$2.list); alist_new($$.list,tok); tok->data=malloc(sizeof($3)+1); strcpy(tok->data,$3); tok->type=TOKEN_TYPE_LIT; alist_free($2.list); }
      ;



literal : TOK_COMMA                     { $$ = $1; }
        | TOK_SPIPE                     { $$ = $1; }
        | TOK_CONST                     { $$ = $1; }
        | TOK_OP                        { $$ = $1; }
        | literal literal               { $$=malloc(strlen($1)+strlen($2)+2); strcpy($$,$1); strcat($$," "); strcat($$,$2); free($1); free($2); }
        ;

/*stmt :
     ; */

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








