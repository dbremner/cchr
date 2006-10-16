#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "parse.h"
#include "util.h"

int starts_with(char **haystack, const char *needle) {
  int len=strlen(needle);
  if (!strncmp(*haystack,needle,len)) {
    if ((isalnum((*haystack)[len-1]) || (*haystack)[len-1] == '_') !=
    (isalnum((*haystack)[len]) || (*haystack)[len] == '_')) {
      *haystack+=len;
      while (isspace(**haystack)) (*haystack)++;
      return 1;
    }
  }
  return 0;
}

void print_spaces(int level,FILE *out) {
  while (level--) fputc(' ',out);
}

int lread_wrapper(char *buf, FILE *in, int *line, int level) {
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
