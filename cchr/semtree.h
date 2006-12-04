/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| semtree.h - Definition of semantic tree data structure                     |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef _semtree_h_
#define _semtree_h_ 1

#include "alist.h"

/* 4 types of rule expressions */
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

/* a rule occurence, listing in what rule and where a specific constraint occurs */
typedef struct {
	int rule; /* what rule? */
	sem_rule_level_t type; /* in which clause of that rule */
	int pos; /* position in that rule */
} sem_ruleocc_t;

typedef struct _sem_expr_t_struct sem_expr_t;

/* the types of expression parts */
typedef enum enum_sem_exprpart_type {
  SEM_EXPRPART_TYPE_VAR=1, /* a variable reference */
  SEM_EXPRPART_TYPE_LIT=2 /* a literal piece of code */
} sem_exprpart_type;

#define SEM_EXPRPART_TYPE_VAR 1
#define SEM_EXPRPART_TYPE_LIT 2

/* a part of an expression, being either a var ref or a lit piece of code */
typedef struct {
  sem_exprpart_type type;
  union {
    int var; /* when type==SEM_EXPRPART_TYPE_VAR */
    char *lit; /* when type==SEM_EXPRPART_TYPE_LIT */
  } data;
} sem_exprpart_t;

/* an expression being a list of expression parts */
struct _sem_expr_t_struct {
  alist_declare(sem_exprpart_t,parts);
};


/* a constraint, having a name, a list of types, and a list of rule occurences */
typedef struct {
  char *name;
  alist_declare(char*,types);
  alist_declare(sem_ruleocc_t,occ);
  sem_expr_t fmt;
  sem_expr_t destr;
  /*alist_declare(sem_expr_t,fmtargs);*/
} sem_constr_t;

/* an argument of a constraint occurence (being a var in head constraints, or an expr in body constraints) */ 
typedef union {
	sem_expr_t expr; /* for BODY */
	int var; /* for KEPT & REM */
} sem_conoccarg_t;

/* a constraint occurence, with a number referring to a constraint, and a list of arguments */
typedef struct {
  int constr;
  alist_declare(sem_conoccarg_t,args); /* in KEPT & REM: just one var ID */
} sem_conocc_t;

/* a variable, with a name, a type (unused ftm), and occurence counts in both head constraints of rules */
typedef struct {
  char *name;
  char *type; /* copy of constr->types[], do not free */
  int occ[2]; /* occurences in removed,kept */
  int local; /* whether is variable is local in the body; 1=guard, 2=body */
  sem_expr_t def; /* only when local==1, this variable's definition */ 
} sem_var_t;

/* variable table */
typedef struct {
  alist_declare(sem_var_t,vars);
} sem_vartable_t;

/* a rule, having a (optional) name, a list of variables, a list of constraint occurences (in head & body), and a guard */
typedef struct {
  char *name;
  sem_vartable_t vt;
  alist_declare(sem_conocc_t,con[3]);
  alist_declare(sem_expr_t,guard);
  alist_declare(sem_expr_t,lstmt[2]);
} sem_rule_t;

/* a semantic tree, which is hardly a tree anymore */
typedef struct {
  alist_declare(sem_rule_t,rules);
  alist_declare(char*,exts);
  alist_declare(sem_constr_t,cons);
} sem_cchr_t;

#endif
