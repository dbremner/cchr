#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "parsestr.h"
#include "semtree.h"
#include "abs2sem.h"
#include "sem2csm.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

typedef void* yyscan_t;
int yylex_init (yyscan_t* scanner);
int yylex_destroy (yyscan_t yyscanner );
int yyparse(yyscan_t scanner,cchr_t *output);
void yyset_in  ( FILE * in_str , yyscan_t scanner );

void static process_file(FILE *in, FILE *out) {
	char wb[256];
	int ws=0; /* size of word buffer */
	char sb[256];
	int ss=0; /* size of space buffer */
	int as=1; /* accepting state (only after ; or } ) */
	int c; /* character read */
	int line=1; /* line number */
	int ls=1; /* only spaces have occured after last newline */
	while ((c=getc(in)) != EOF) {
		if (c == '\n') {line++;ls=1;}
		if (isalpha(c)) {
			ls=0;
			if (ss>0) {
				fwrite(wb,ws,1,out);
				if (ws) as=0;
				ws=0;
				fwrite(sb,ss,1,out);
				ss=0;
			}
			wb[ws++]=c;		
			continue;
		}
		if (c == '#' && ls) {
			fwrite(wb,ws,1,out);
			ws=0;
			fwrite(sb,ss,1,out);
			ss=0;
			fputc(c,out);
			int bs=0;
			while ((c=getc(in)) != EOF) {
				fputc(c,out);
				if (c=='\n' && !bs) break;
				if (c=='\\') {
					bs=(!bs);
				} else {
					bs=0;
				}
			}
			ls=1;
			continue;
		}
		if (isspace(c)) {
			if (ws) {
			  sb[ss++]=c;
			  continue;
			}
		} else {
			ls=0;
		}
		if (c == '{') {
			if (as && ws==4 && !strncmp(wb,"cchr",4)) {
				yyscan_t scanner;
				yylex_init(&scanner);
				yyset_in(in,scanner);
				cchr_t cchr;
				yyparse(scanner,&cchr);
				yylex_destroy(scanner);
				sem_cchr_t sem_cchr;
				sem_generate_cchr(&sem_cchr,&cchr);
				destruct_cchr_t(&cchr);
				csm_generate(&sem_cchr,out);
				sem_cchr_destruct(&sem_cchr);
				ws=0;
				ss=0;
				as=1;
				continue;
			}
		}
		fwrite(wb,ws,1,out);
		ws=0;
		fwrite(sb,ss,1,out);
		ss=0;
		if (!isspace(c)) as=(c == '}' || c == ';');
		fputc(c,out);
		
	}
	fwrite(wb,ws,1,out);
	fwrite(sb,ss,1,out);
}


int main(int argc, char *argv[])
{
	process_file(stdin,stdout);
}
