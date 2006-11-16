#ifndef _parsestr_h_
#define _parsestr_h_ 1

#ifdef USE_EFENCE
#include <efence.h>
#endif

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
  alist_declare(char*,exts);
} cchr_t;

void static destruct_cchr_t (cchr_t *cchr);
void static destruct_rule_t (rule_t *rule);
void static destruct_exprlist_t (exprlist_t *exprl);
void static destruct_constr_t (constr_t *constr);
void static destruct_expr_t (expr_t *expr);
void static destruct_token_t (token_t *tok);

void static destruct_token_t (token_t *tok) {
  free(tok->data);
  if (tok->type == TOKEN_TYPE_FUNC) {
    for (int i=0; i<alist_len(tok->args); i++) destruct_expr_t(alist_ptr(tok->args,i));
    alist_free(tok->args);
  }
}

void static destruct_expr_t (expr_t *expr) {
  for (int i=0; i<alist_len(expr->list); i++) destruct_token_t(alist_ptr(expr->list,i));
  alist_free(expr->list);
}

void static destruct_constr_t (constr_t *constr) {
  free(constr->name);
  for (int i=0; i<alist_len(constr->list); i++) free(alist_get(constr->list,i));
  alist_free(constr->list);
}

void static destruct_exprlist_t (exprlist_t *exprl) {
  for (int i=0; i<alist_len(exprl->list); i++) destruct_expr_t(alist_ptr(exprl->list,i));
  alist_free(exprl->list);
}

void static destruct_rule_t (rule_t *rule) {
  free(rule->name);
  destruct_exprlist_t(&(rule->kept));
  destruct_exprlist_t(&(rule->removed));
  destruct_exprlist_t(&(rule->body));
  destruct_expr_t(&(rule->guard));
}

void static destruct_cchr_t (cchr_t *cchr) {
  for (int i=0; i<alist_len(cchr->constrs); i++) destruct_constr_t(alist_ptr(cchr->constrs,i));
  alist_free(cchr->constrs);
  for (int i=0; i<alist_len(cchr->rules); i++) destruct_rule_t(alist_ptr(cchr->rules,i));
  alist_free(cchr->rules);
  for (int i=0; i<alist_len(cchr->exts); i++) free(alist_get(cchr->exts,i));
  alist_free(cchr->exts);
}

#endif
