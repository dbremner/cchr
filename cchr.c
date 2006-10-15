#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parse.h"

static void print_spaces(int level,FILE *out) {
  while (level--) fputc(' ',out);
}

int main(int argc,char **argv) {
  process(stdin,stdout,0);
  return 0;
}

int process(FILE* in,FILE* out,int level) {
  char buf[MAXLINELEN];
  int line=1;
  while(1) {
    int ret=lread(buf,in,&line);
    if (ret==READ_BRAC) {
      fprintf(stderr,"unbalanced bracket on line %i\n",line);
      return(1);
    }
    if (ret==READ_CHAR) {
      fprintf(stderr,"weird character on line %i\n",line);
      return(1);
    }
    if ((ret==READ_EEOF)||(level&&(ret==READ_EOF))) {
      fprintf(stderr,"unexpected end of file on line %i\n",line);
      return(1);
    }
    if (ret==READ_BUFF) {
      fprintf(stderr,"buffer overflow on line %i\n",line);
      return(1);
    }
    if (ret==READ_EOF) {
      fputc('\n',out);
      return(0);
    }
    if (ret==READ_EOB) return(0);
    print_spaces(level,out);
    fputs(buf,out);
    if (ret==READ_EOLS) {
      fputc('\n',out);
      print_spaces(level,out);
      fputs("{\n",out);
      if (process(in,out,level+2)) return(1);
      print_spaces(level,out);
      fputs("}\n",out);
      if (level==0) fputc('\n',out);
    } else {
     fputs(";\n",out);
    }
  }
  return(0);
}
