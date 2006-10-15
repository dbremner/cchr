#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "cchr.h"

int process_cchr(FILE *in, FILE *out, int *line, int level) {
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

