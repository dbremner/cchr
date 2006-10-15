#ifndef _util_h_
#define _util_h_ 1

#include "parse.h"

#define LREAD_ERROR -1
#define LREAD_EOL 0
#define LREAD_EOB 1
#define LREAD_BOB 2

int lread_wrapper(char *buf, FILE *in, int *line, int level);
void print_spaces(int level,FILE *out);

#endif
