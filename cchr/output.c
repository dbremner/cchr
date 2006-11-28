/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| output.c - minimal indenting output routines                               |
| written by Pieter Wuille                                                   |
\****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "output.h"

#ifdef USE_EFENCE
#include <efence.h>
#endif

/* get line number in output stream */
int output_get_line(output_t *output) {
  return output->linenum;
}

/* set output line in output stream */
void output_set_line(output_t *output, int line) {
  output->linenum=line;
}

/* initialize output stream structure */
void output_init(output_t *output, FILE *out) {
  output->out=out;
  output->linenum=1;
  output->idf=malloc(3);
  strcpy(output->idf,"  ");
  alist_init(output->les);
}

/* destruct an output stream structure */
void output_destruct(output_t *output) {
  for (int j=0; j<alist_len(output->les); j++) {
    free(alist_get(output->les,j));
  }
  alist_free(output->les);
  free(output->idf);
}

/* output a number of chars (at most len) pointer to be str to out */
void output_chars(output_t *output, char *str, int len) {
  char *fs;
  while ((fs=strchr(str,'\n')) && fs<str+len) {
    fwrite(str,fs-str,1,output->out);
    len -= (fs+1-str);
    str=fs+1;
    int i=alist_len(output->les);
    putc('\n',output->out);
    output->linenum++;
    while (i--) {
      fputs(output->idf,output->out);
    }
  }
  fwrite(str,len,1,output->out);
}

/* output a single character to out */
void output_char(output_t *output, int ch) {
  char ccc=ch;
  output_chars(output,&ccc,1);
}

/* output a string to output */
void output_string(output_t *output, char *str) {
  output_chars(output,str,strlen(str));
}

/* output some formatted data to output (see fprintf) */
void output_fmt(output_t *output, char *fmt, ...) {
    int n, size = 100;
    char *p, *np;
    va_list ap;
    if ((p = malloc (size)) == NULL) return;
    while (1) {
        va_start(ap, fmt);
                n = vsnprintf (p, size, fmt, ap);
                va_end(ap);
                if (n > -1 && n < size) {
			output_string(output,p);
			free(p);
			return;
		}
                if (n > -1) {
                        size = n+1;
                } else {
                        size *= 2;
                }
        if ((np = realloc (p, size)) == NULL) {
            free(p);
            return;
        } else {
            p = np;
        }
    }
}

/* output "in" to output, followed by a newline after which an indented block follows.
 * this indented block can be ended with output_unindent, and will print a newline, a decreased indentation and "out" */
void output_indent(output_t *output, char *in, char *out) {
  output_string(output,in);
  char *ad=malloc(strlen(out)+2);
  strcpy(ad,"\n");
  strcat(ad,out);
  alist_add(output->les,ad);
  output_string(output,"\n");
}

/* end an indented block, see output_indent */
void output_unindent(output_t *output) {
  int l=alist_len(output->les);
  if (l) {
    char *ptr;
    alist_pop(output->les,ptr);
    output_string(output,ptr);
    free(ptr);
  }
}

/* end all indented blocks until level level */
void output_unindent_till(output_t *output,int level) {
  while (alist_len(output->les)>level) {
    output_unindent(output);
  }
}

