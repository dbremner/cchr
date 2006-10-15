#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parse.h"

int process_file(FILE* in,FILE* out, int *line, int level);
int static process_block(FILE *in, FILE *out, int *line, int level, char *code);
int static process_cchr(FILE *in, FILE *out, int *line, int level);
int static lread_wrapper(char *buf, FILE *in, int *line, int level);
void static print_spaces(int level,FILE *out);

static void print_spaces(int level,FILE *out) {
  while (level--) fputc(' ',out);
}

#define LREAD_ERROR -1
#define LREAD_EOL 0
#define LREAD_EOB 1
#define LREAD_BOB 2

int static lread_wrapper(char *buf, FILE *in, int *line, int level) {
  int ret=lread(buf,in,line);
  switch (ret) {
    case READ_BRAC:
      fprintf(stderr,"unbalanced bracket on line %i\n",*line);
      return LREAD_ERROR;
    case READ_CHAR:
      fprintf(stderr,"weird character on line %i\n",*line);
      return LREAD_ERROR;
    case READ_EOF:
      if (!level) return LREAD_EOB;
    case READ_EEOF:
      fprintf(stderr,"unexpected end of file on line %i\n",*line);
      return LREAD_ERROR;
    case READ_BUFF:
      fprintf(stderr,"buffer overflow on line %i\n",*line);
      return LREAD_ERROR;
    case READ_EOB:
      return LREAD_EOB;
    case READ_EOLS:
      return LREAD_BOB;
    default:
      return LREAD_EOL;
  }
}

int main(int argc,char **argv) {
  int line=0;
  process_file(stdin,stdout,&line,0);
  return 0;
}

int static process_cchr(FILE *in, FILE *out, int *line, int level) {
  char buf[MAXLINELEN];
  while(1) {
    int ret=lread_wrapper(buf,in,line,level);
    if (ret==LREAD_ERROR) return 1;
    if (ret==LREAD_EOB) return 0;
    if (ret==LREAD_BOB) {
      fprintf(stderr,"CCHR doesn't support subblocks on line %i",*line);
      return 1;
    }
  }
  return 0;
}

int static process_block(FILE *in, FILE *out, int *line, int level, char *code) {
  if (!strcmp(code,"extern \"CCHR\"")) {
    process_cchr(in,out,line,level);
  } else {
    print_spaces(level,out);
    fputs(code,out);
    fputc('\n',out);
    print_spaces(level,out);
    fputs("{\n",out);
    if (process_file(in,out,line,level+2)) return(1);
    print_spaces(level,out);
    fputs("}\n",out);
  }
  return 0;
}

int process_file(FILE* in,FILE* out,int *line, int level) {
  char buf[MAXLINELEN];
  if (level==0) *line=1;
  while(1) {
    int ret=lread_wrapper(buf,in,line,level);
    if (ret==LREAD_ERROR) return 1;
    if (ret==LREAD_EOB) return 0;
    if (ret==LREAD_BOB) {
      if (process_block(in,out,line,level,buf)) return 1;
      if (level==0) fputc('\n',out);
    } else {
      print_spaces(level,out);
      fputs(buf,out);
      fputs(";\n",out);
    }
  }
  return(0);
}
