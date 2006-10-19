#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cchr.h"
#include "util.h"

int static process_stream(FILE* in,FILE* out, int *line, int level);
int static process_block(FILE *in, FILE *out, int *line, int level, char *code);

/* main function: translates CCHR on stdin to C on stdout */
int main(int argc,char **argv) {
  int line=0;
  process_stream(stdin,stdout,&line,0);
  return 0;
}

/* translate a block of input (enclosed by { }) */
/* detects 'extern "CCHR"' blocks, and calls process_cchr to handle these */
int static process_block(FILE *in, FILE *out, int *line, int level, char *code) {
  if (!strcmp(code,"extern \"CCHR\"")) {
    process_cchr(in,out,line,level);
  } else {
    print_spaces(level,out);
    fputs(code,out);
    fputc('\n',out);
    print_spaces(level,out);
    fputs("{\n",out);
    if (process_stream(in,out,line,level+2)) return(1);
    print_spaces(level,out);
    fputs("}\n",out);
  }
  return 0;
}

/* translate input to output, calls process_block to translate {}-enclosed blocks */
int static process_stream(FILE* in,FILE* out,int *line, int level) {
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
