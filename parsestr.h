#ifndef _parsestr_h_
#define _parsestr_h_ 1

#include "alist.h"

#define TOKEN_TYPE_LIT 0
#define TOKEN_TYPE_SYMB 1

typedef struct {
  char *data;
  int type;
} token_t;

typedef struct {
  alist_declare(token_t,list);
} expr_t;

#endif
