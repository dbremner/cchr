#ifndef _parsestr_h_
#define _parsestr_h_ 1

#include "alist.h"

#define TOKEN_TYPE_LIT 0
#define TOKEN_TYPE_SYMB 1
#define TOKEN_TYPE_FUNC 2

typedef struct _expr_t_struct expr_t;

typedef struct {
  int type;
  char *data;
  alist_declare(expr_t,args);
} token_t;

struct _expr_t_struct {
  alist_declare(token_t,list);
};

typedef struct {
  char *name;
  alist_declare(char*,list);
} constr_t;

typedef struct {
  alist_declare(expr_t,list);
} exprlist_t;

typedef struct {
  char *name;
  exprlist_t kept;
  exprlist_t removed;
  exprlist_t body;
  expr_t guard;
} rule_t;

typedef struct {
  alist_declare(constr_t,constrs);
  alist_declare(rule_t,rules);
} cchr_t;

#endif
