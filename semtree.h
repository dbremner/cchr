#ifndef _semtree_h_
#define _semtree_h_ 1

#include "alist.h"

typedef enum enum_sem_rule_level {
  SEM_RULE_LEVEL_KEPT=0,
  SEM_RULE_LEVEL_REM=1,
  SEM_RULE_LEVEL_BODY=2,
  SEM_RULE_LEVEL_GUARD=3
} sem_rule_level_t;

#define SEM_RULE_LEVEL_KEPT 0
#define SEM_RULE_LEVEL_REM 1
#define SEM_RULE_LEVEL_BODY 2
#define SEM_RULE_LEVEL_GUARD 3

typedef struct {
	int rule; /* what rule? */
	/* type of conlist in rule is determined by index of ruleocc list in sem_constr_t */
	int pos; /* position in that rule */
} sem_ruleocc_t;

typedef struct {
  char *name;
  alist_declare(char*,types);
  alist_declare(sem_ruleocc_t,occ[3]);
} sem_constr_t;

typedef enum enum_sem_exprpart_type {
  SEM_EXPRPART_TYPE_VAR=1,
  SEM_EXPRPART_TYPE_LIT=2
} sem_exprpart_type;

#define SEM_EXPRPART_TYPE_VAR 1
#define SEM_EXPRPART_TYPE_LIT 2

typedef struct {
  sem_exprpart_type type;
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
  alist_declare(int,args); /* var ID's */
} sem_conocc_t;

typedef struct {
  char *name;
  char *type; /* copy of constr->types[], do not free */
  int occ[3]; /* occurences in removed,kept,body */
} sem_var_t;

typedef struct {
  char *name;
  alist_declare(sem_var_t,vars);
  alist_declare(sem_conocc_t,con[3]);
  alist_declare(sem_expr_t,guard);
} sem_rule_t;

typedef struct {
  alist_declare(sem_rule_t,rules);
  alist_declare(char*,exts);
  alist_declare(sem_constr_t,cons);
} sem_cchr_t;

#endif
