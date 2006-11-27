#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "output.h"

int output_get_line(output_t *output) {
  return output->linenum;
}

void output_set_line(output_t *output, int line) {
  output->linenum=line;
}

void output_init(output_t *output, FILE *out) {
  output->out=out;
  output->linenum=1;
  output->idf=malloc(3);
  strcpy(output->idf,"  ");
  alist_init(output->les);
}

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

void output_char(output_t *output, int ch) {
  char ccc=ch;
  output_chars(output,&ccc,1);
}

void output_string(output_t *output, char *str) {
  output_chars(output,str,strlen(str));
}

void output_indent(output_t *output, char *in, char *out) {
  output_string(output,in);
  char *ad=malloc(strlen(out)+2);
  strcpy(ad,"\n");
  strcat(ad,out);
  alist_add(output->les,ad);
  output_string(output,"\n");
}

void output_unindent(output_t *output) {
  int l=alist_len(output->les);
  if (l) {
    char *ptr;
    alist_pop(output->les,ptr);
    output_string(output,ptr);
    free(ptr);
  }
}

void output_unindent_till(output_t *output,int level) {
  while (alist_len(output->les)>level) {
    output_unindent(output);
  }
}

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
