/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| cchr.lex - FLEX file for CHR-in-C lexer                                    |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parsestr.h"
#include "cchr.tab.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

void static yyerror(char *message,yyscan_t scanner);

void strip_sl(char *c);

#define LIT_RETURN(TYPE) {yylloc->first_line=yyget_lineno(yyscanner); yylloc->last_line=yyget_lineno(yyscanner); yylval->lit=malloc(yyleng+1); memcpy(yylval->lit,yytext,yyleng); yylval->lit[yyleng]=0; return TYPE;}

#define YY_INPUT(buf,result,max_size) { \
	int c = getc(yyin); \
    result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
}

%}

%option noyywrap
%option yylineno
%option nounput
%option batch
%option always-interactive
%option bison-bridge
%option bison-locations
%option reentrant

%x BCOMMENT
%X LCOMMENT
%X STRING

white_space       [ \t\n]*
digit             [0-9]
alpha             [A-Za-z_$]
alpha_num         ({alpha}|{digit})
hex_digit         [0-9A-F]
identifier        {alpha}{alpha_num}*
unsigned_integer  {digit}+
hex_integer       -?(0x|OX){hex_digit}{hex_digit}*
exponent          e[+-]?{digit}+
integer           -?{unsigned_integer}U?(L|LL|S)?
i                 {unsigned_integer}
real              ({i}\.{i}?|{i}?\.{i}){exponent}?

%%

"/*"              BEGIN(BCOMMENT);
<BCOMMENT>"*/"    BEGIN(INITIAL);
<BCOMMENT><<EOF>> yyerror("EOF in comment",yyscanner);
<BCOMMENT>.       {}

"//"              BEGIN(LCOMMENT);
<LCOMMENT>.       {}
<LCOMMENT>"\n"	  BEGIN(INITIAL);

"\""			  BEGIN(STRING); LIT_RETURN(TOK_BSTRING);
<STRING>"\\"(x{hex_integer}{hex_integer})	LIT_RETURN(TOK_STRING)
<STRING>"\\".	  LIT_RETURN(TOK_STRING)
<STRING>"\""	  BEGIN(INITIAL); LIT_RETURN(TOK_ESTRING);
<STRING>.		  LIT_RETURN(TOK_STRING)

"constraint"      LIT_RETURN(TOK_CONSTRAINT);
"true"            LIT_RETURN(TOK_TRUE);
"extern"	  	  LIT_RETURN(TOK_EXTERN);
"{"               LIT_RETURN(TOK_LCBRAC);
"}"               LIT_RETURN(TOK_RCBRAC);
";"               LIT_RETURN(TOK_SEMI);
","               LIT_RETURN(TOK_COMMA);
"@"               LIT_RETURN(TOK_AT);
"<=>"             LIT_RETURN(TOK_SIMP);
"==>"             LIT_RETURN(TOK_PROP);
"|"               LIT_RETURN(TOK_SPIPE);
"\\"              LIT_RETURN(TOK_BSLASH);
"("               LIT_RETURN(TOK_LRBRAC);
")"               LIT_RETURN(TOK_RRBRAC);

"++"|"--"|"+"|"-"|"*"|"/"|"->"|"."|"<<"|">>"|"<"|">"|"="|"=="|"<="|">="|"%"|"%="               LIT_RETURN(TOK_OP)
"^"|"~"|"&"|"&&"|"||"|"+="|"*="|"/="|"-="|">>="|"<<="|"&="|"|="|"||="|"&&="   LIT_RETURN(TOK_OP)
{integer}         LIT_RETURN(TOK_CONST)
{real}            LIT_RETURN(TOK_CONST)
{hex_integer}     LIT_RETURN(TOK_CONST)
{identifier}{white_space}"("      {strip_sl(yytext); LIT_RETURN(TOK_FUNC);}
{identifier}      LIT_RETURN(TOK_SYMB)
{identifier}{white_space}"@"	  {strip_sl(yytext); LIT_RETURN(TOK_SYMBAT); }

{white_space}     /* do nothing */

.                 return TOK_ERROR;

%%

void static yyerror(char *message,yyscan_t scanner)
{
   fprintf(stderr,"Error: \"%s\" in line %d. Token = %s\n",
           message,yyget_lineno(scanner),yyget_text(scanner));
}

void strip_sl(char *c) {
  int len=strlen(c)-1;
  if (len<0) return;
  while (len>0 && isspace(c[len-1])) len--;
  c[len]=0;
}

