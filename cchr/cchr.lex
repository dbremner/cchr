/*
 * cchr.lex: FLEX lexer for CCHR code
 *
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parsestr.h"
#include "y.tab.h"

void yyerror(char *message);
void strip_sl(char *c);

#define LIT_RETURN(TYPE) {yylval.lit=malloc(yyleng+1); memcpy(yylval.lit,yytext,yyleng); yylval.lit[yyleng]=0; return TYPE;}

%}

%option noyywrap
%option yylineno
%option nounput

%x BCOMMENT
%X LCOMMENT

white_space       [ \t\n]*
digit             [0-9]
alpha             [A-Za-z_]
alpha_num         ({alpha}|{digit})
hex_digit         [0-9A-F]
identifier        {alpha}{alpha_num}*
unsigned_integer  {digit}+
hex_integer       -?(0x|OX){hex_digit}{hex_digit}*
exponent          e[+-]?{digit}+
integer           -?{unsigned_integer}
i                 {unsigned_integer}
real              ({i}\.{i}?|{i}?\.{i}){exponent}?

%%

"/*"              BEGIN(BCOMMENT);
<BCOMMENT>"*/"    BEGIN(INITIAL);
<BCOMMENT><<EOF>> yyerror("EOF in comment");
<BCOMMENT>.       {}

"//"              BEGIN(LCOMMENT);
<LCOMMENT>.       {}

constraint        LIT_RETURN(TOK_CONSTRAINT);
extern            LIT_RETURN(TOK_EXTERN);
true              LIT_RETURN(TOK_TRUE);
"{"               LIT_RETURN(TOK_LCBRAC);
"}"               LIT_RETURN(TOK_RCBRAC);
";"               LIT_RETURN(TOK_SEMI);
","               LIT_RETURN(TOK_COMMA);
"@"               LIT_RETURN(TOK_AT);
"<=>"             LIT_RETURN(TOK_SIMP);
"==>"              LIT_RETURN(TOK_PROP);
"|"               LIT_RETURN(TOK_SPIPE);
"\\"              LIT_RETURN(TOK_BSLASH);
"("               LIT_RETURN(TOK_LRBRAC);
")"               LIT_RETURN(TOK_RRBRAC);

"+"|"-"|"*"|"/"|"->"|"<<"|">>"|"<"|">"|"="|"=="|"<="|">="                     LIT_RETURN(TOK_OP)
"^"|"~"|"&"|"&&"|"||"|"+="|"*="|"/="|"-="|">>="|"<<="|"&="|"|="|"||="|"&&="   LIT_RETURN(TOK_OP)
{integer}         LIT_RETURN(TOK_CONST)
{real}            LIT_RETURN(TOK_CONST)
{hex_integer}     LIT_RETURN(TOK_CONST)
{identifier}{white_space}"("      {strip_sl(yytext); LIT_RETURN(TOK_FUNC);}
{identifier}      LIT_RETURN(TOK_SYMB)
{identifier}{white_space}"@"	  {strip_sl(yytext); LIT_RETURN(TOK_SYMBAT); }

{white_space}     /* do nothing */

.                 yyerror("Illegal input");

%%

void yyerror(char *message)
{
   fprintf(stderr,"Error: \"%s\" in line %d. Token = %s\n",
           message,yylineno,yytext);
   exit(1);
}

void strip_sl(char *c) {
  int len=strlen(c)-1;
  if (len<0) return;
  while (len>0 && isspace(c[len-1])) len--;
  c[len]=0;
}

