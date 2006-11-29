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
#include "output.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

/* a few definitions for interfacing with lexer/scanner */
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

/* process an input stream, considering it CCHR code */
int process_file_cchr(FILE *in, output_t *out, int *line) {
	yyscan_t scanner;
	yylex_init(&scanner);
	yyset_in(in,scanner);
	cchr_t cchr;
	int ok=1;
	if (!yyparse(scanner,&cchr,*line-1)) {
		*line+=yyget_lloc(scanner)->last_line-1;
		yylex_destroy(scanner);
		sem_cchr_t sem_cchr;
		int oko=sem_generate_cchr(&sem_cchr,&cchr);
		destruct_cchr_t(&cchr);
		if (oko) {
			csm_generate(&sem_cchr,out);
		} else {
			ok=0;
		}
		sem_cchr_destruct(&sem_cchr);
	} else {
		yylex_destroy(scanner);
		ok=0;
	}
	return ok;
}

/* process a single file. This function will read the passed file, byte per
 * byte, and call process_file_cchr when necessary */
int process_file(FILE *in, output_t *out, int *line, char *inname, char *outname) {
	char wb[256];
	int ws=0; /* size of word buffer */
	char sb[256];
	int ss=0; /* size of space buffer */
	int as=1; /* accepting state (only after ; or } ) */
	int c; /* character read */
	int ls=1; /* only spaces have occured after last newline */
	int ok=1; /* return value */
	output_fmt(out,"#line %i \"%s\"\n",*line,inname);
	while ((c=getc(in)) != EOF) { /* loop over all bytes in the source */
		if (c == '\n') {(*line)++;ls=1;} /* line-number counter */
		if (isalpha(c)) { /* for alphabetical characters */
			ls=0;
			if (ss>0) { /* if word+space buffer are filled */
				output_chars(out,wb,ws); /* write them out */
				if (ws) as=0;
				ws=0;
				output_chars(out,sb,ss);
				ss=0;
			}
			wb[ws++]=c; /* add this character to word buffer */		
			continue;
		}
		if (c == '#' && ls) { /* for preprocessor statements */
			output_chars(out,wb,ws);
			ws=0;
			output_chars(out,sb,ss);
			ss=0;
			output_char(out,c);
			int bs=0;
			while ((c=getc(in)) != EOF) {
				output_char(out,c);
				if (c=='\n') (*line)++;
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
		if (isspace(c)) { /* whitespace */
			if (ws) {
			  sb[ss++]=c;
			  continue;
			}
		} else {
			ls=0;
		}
		if (c == '{') { /* begin of a block */
			if (as && ws==4 && !strncmp(wb,"cchr",4)) {
				output_fmt(out,"#line %i \"%s\"\n",output_get_line(out)+1,outname);
				if (!process_file_cchr(in,out,line)) ok=0;
			    output_fmt(out,"#line %i \"%s\"\n",*line,inname);
				ws=0;
				ss=0;
				as=1;
				continue;
			}
		}
		output_chars(out,wb,ws);
		ws=0;
		output_chars(out,sb,ss);
		ss=0;
		if (!isspace(c)) as=(c == '}' || c == ';'); /* after these a "cchr {" may follow */
		output_char(out,c);
		
	}
	output_chars(out,wb,ws);
	output_chars(out,sb,ss);
	return ok;
}


int main(int argc, char *argv[])
{
	int ok=1;
	for (int i=1; i<argc; i++) {
	    char *arg=argv[i];
	    int line=1;
	    char *oa=malloc(strlen(arg)+3);
	    strcpy(oa,arg);
	    if (strlen(arg)>4 && !strcmp(arg+strlen(arg)-4,".chr")) oa[strlen(arg)-4]=0;
	    if (strlen(arg)>5 && !strcmp(arg+strlen(arg)-5,".cchr")) oa[strlen(arg)-5]=0;
	    strcat(oa,".c");
	    FILE *in=fopen(arg,"r");
	    FILE *out=fopen(oa,"w");
	    output_t oo;
	    output_init(&oo,out);
	    if (!process_file(in,&oo,&line,arg,oa)) ok=0;
	    free(oa);
	    output_destruct(&oo);
	    fclose(out);
	    fclose(in);
	}
	return (!ok);
}
