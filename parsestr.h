/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| parsestr.h - definition of syntax tree data structure                      |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef _parsestr_h_
#define _parsestr_h_ 1

#include <stdlib.h>
#include <string.h>

#include "alist.h"

typedef enum enum_token_type_t {
  TOKEN_TYPE_LIT=1,
  TOKEN_TYPE_SYMB=2,
  TOKEN_TYPE_FUNC=3
} token_type_t;

#define TOKEN_TYPE_LIT 1
#define TOKEN_TYPE_SYMB 2
#define TOKEN_TYPE_FUNC 3

typedef struct _expr_t_struct expr_t;

typedef struct {
  token_type_t type;
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
  alist_declare(char*,exts);
} cchr_t;

void destruct_cchr_t (cchr_t *cchr);
void destruct_rule_t (rule_t *rule);
void destruct_exprlist_t (exprlist_t *exprl);
void destruct_constr_t (constr_t *constr);
void destruct_expr_t (expr_t *expr);
void destruct_token_t (token_t *tok);

#endif
