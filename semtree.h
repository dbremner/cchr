#ifndef _semtree_h_
#define _semtree_h_ 1

#include "alist.h"

typedef struct {
  char *name;
  alist_declare(char*,types);
  alist_declare(int,occ_kept);
  alist_declare(int,occ_rem);
  alist_declare(int,occ_body);
} sem_constr_t;

#define SEM_EXPRPART_TYPE_VAR 0
#define SEM_EXPRPART_TYPE_LIT 0

typedef struct {
  int type;
  union {
    int var;
    char *lit;
  } data;
} sem_exprpart_t;

typedef struct {
  alist_declare(sem_exprpart_t,parts);
} sem_expr_t;

typedef struct {
  int constr;
  alist_declare(sem_expr_t,args);
} sem_conocc_t

typedef struct {
  char *name;
  char *type;
  int def; /* 0=in kept, 1=in removed, 2=in body */
  int defnum; /* index of declaration of type def */
  int occ; /* will be 0 in HNF, 1 for each extra occ in kept or removed */
} sem_var_t;

typedef struct {
  char *name;
  alist_declare(sem_var_t,vars);
  alist_declare(sem_conocc_t,kept);
  alist_declare(sem_conocc_t,rem);
  alist_declare(sem_conocc_t,body);
  sem_expr_t guard;
} sem_rule_t;

#endif
