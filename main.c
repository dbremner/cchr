/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| main.c - main compiler routines                                            |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

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

/* a few definitions, not exported by flex/bison */
typedef void* yyscan_t;
int yylex_init (yyscan_t* scanner);
int yylex_destroy (yyscan_t yyscanner );
int yyparse(yyscan_t scanner,cchr_t *output,int base_line);
void yyset_in  ( FILE * in_str , yyscan_t scanner );
typedef struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} YYLTYPE;

YYLTYPE *yyget_lloc ( yyscan_t scanner );


/* process a single file */
void process_file(FILE *in, FILE *out) {
	char wb[256];
	int ws=0; /* size of word buffer */
	char sb[256];
	int ss=0; /* size of space buffer */
	int as=1; /* accepting state (only after ; or } ) */
	int c; /* character read */
	int line=1; /* line number */
	int ls=1; /* only spaces have occured after last newline */
	while ((c=getc(in)) != EOF) { /* loop over all bytes in the source */
		if (c == '\n') {line++;ls=1;} /* line-number counter */
		if (isalpha(c)) { /* for alphabetical characters */
			ls=0;
			if (ss>0) { /* if word+space buffer are filled */
				fwrite(wb,ws,1,out); /* write them out */
				if (ws) as=0;
				ws=0;
				fwrite(sb,ss,1,out);
				ss=0;
			}
			wb[ws++]=c; /* add this character to word buffer */		
			continue;
		}
		if (c == '#' && ls) { /* for preprocessor statements */
			fwrite(wb,ws,1,out);
			ws=0;
			fwrite(sb,ss,1,out);
			ss=0;
			fputc(c,out);
			int bs=0;
			while ((c=getc(in)) != EOF) {
				fputc(c,out);
				if (c=='\n') line++;
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
				if (!yyparse(scanner,&cchr,line-1)) {
					line=yyget_lloc(scanner)->last_line+line-1;
					yylex_destroy(scanner);
					sem_cchr_t sem_cchr;
					sem_generate_cchr(&sem_cchr,&cchr);
					destruct_cchr_t(&cchr);
					csm_generate(&sem_cchr,out);
					sem_cchr_destruct(&sem_cchr);
				} else {
					yylex_destroy(scanner);
					return;
				}
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
