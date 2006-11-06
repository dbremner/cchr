/*
 * cchr.lex: FLEX lexer for CCHR code
 *
 */

%{
#include <stdio.h>
#include "y.tab.h"

int line_number = 0;

void yyerror(char *message);

#define LIT_RETURN(VAL) {yylval.
%}

%option noyywrap
%option yylineno

%x BCOMMENT
%X LCOMMENT

white_space       [ \t]*
digit             [0-9]
alpha             [A-Za-z_]
alpha_num         ({alpha}|{digit})
hex_digit         [0-9A-F]
identifier        {alpha}{alpha_num}*
unsigned_integer  {digit}+
hex_integer       ${hex_digit}{hex_digit}*
exponent          e[+-]?{digit}+
integer           [+-]?{unsigned_integer}
real              ({i}\.{i}?|{i}?\.{i}){exponent}?

%%

"/*"              BEGIN(BCOMMENT);
<BCOMMENT>"*/"    BEGIN(INITIAL);
<BCOMMENT>\n      line_number++;
<BCOMMENT><<EOF>> yyerror("EOF in comment");
<BCOMMENT>.       {}

"//"              BEGIN(LCOMMENT);
<LCOMMENT>\n      {line_number++; BEGIN(INITIAL);}
<LCOMMENT>.       {}

constraint        return(TOK_CONSTRAINT);
extern            return(TOK_EXTERN);
true              return(TOK_TRUE);
"{"               return(TOK_LCBRAC);
"}"               return(TOK_RCBRAC);
";"               return(TOK_SEMI);
","               return(TOK_COMMA);
"@"               return(TOK_AT);
"<=>"             return(TOK_SIMP);
"=>"              return(TOK_PROP);
"|"               return(TOK_SPIPE);
"||"              return(TOK_DPIPE);
"&"               return(TOK_SAND);
"&&"              return(TOK_DAND);
"-"               return(TOK_MINUS);
"+"               return(TOK_PLUS);
"*"               return(TOK_MULT);
"/"               return(TOK_DIV);
"\\"              return(TOK_BSLASH);
"^"               return(TOK_CARET);
"."               return(TOK_DOT);
"->"              return(TOK_ARROW);
"("               return(TOK_LRBRAC);
")"               return(TOK_RRBRAC);
"="               return(TOK_ASSIGN);
"=="              return(TOK_EQUALS);
">="              return(TOK_GREQ);
">"               return(TOK_GR);
"<="              return(TOK_SMEQ);
"<"               return(TOK_SM);
"!="              return(TOK_NEQ);
"!"               return(TOK_NOT);
">>"              return(TOK_RSHIFT);
"<<"              return(TOK_LSHIFT);

{integer}         {yylval.ival=strreturn(UNSIGNED_INTEGER);
{real}               return(REAL);
{hex_integer}        return(HEX_INTEGER);
{string}             return{STRING};
{bad_string}         yyerror("Unterminated string");

{identifier}         return(IDENTIFIER);

[*/+\-,^.;:()\[\]]   return(yytext[0]);

{white_space}        /* do nothing */
\n                   line_number += 1;
.                    yyerror("Illegal input");

%%

void yyerror(char *message)
{
   fprintf(stderr,"Error: \"%s\" in line %d. Token = %s\n",
           message,line_number,yytext);
   exit(1);
}


