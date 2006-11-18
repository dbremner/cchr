#include <string.h>
#include <stdlib.h>

#include "alist.h"
#include "parsestr.h"
#include "semtree.h"

void sem_constr_init(sem_constr_t* con,char *name) {
  alist_init(con->types);
  alist_init(con->occ_kept);
  alist_init(con->occ_rem);
  alist_init(con->occ_body);
  con->name=name;
}

void sem_constr_destruct(sem_constr_t *con) {
  free(con->name);
  alist_free(con->occ_kept);
  alist_free(con->occ_rem);
  alist_free(con->occ_body);
}

void sem_exprpart_init_var(sem_exprpart_t *exprp, int var) {
  exprp->type=SEM_EXPRPART_TYPE_VAR;
  exprp->data.var=var;
}

void sem_exprpart_destruct(sem_exprpart_t *exprp) {
}

void sem_exprpart_init_lit(sem_exprpart_t *exprp, char *str) {
  exprp->type=SEM_EXPRPART_TYPE_LIT;
  exprp->data.lit=str;
}

void sem_expr_init(sem_expr_t *expr) {
  alist_init(expr->parts);
}

void sem_expr_destruct(sem_expr_t *expr) {
  for (int i=0; i<alist_len(expr->parts); i++) sem_exprpart_destruct(alist_ptr(expr->parts,i));
  alist_free(expr->parts);
}

void sem_conocc_init(sem_conocc_t *occ, int constr) {
  alist_init(occ->args);
  occ->constr=constr;
}

void sem_conocc_destruct(sem_conocc_t *con) {
  for (int i=0; i<alist_len(con->args); i++) sem_expr_destruct(alist_ptr(expr->parts,i));
  alist_free(con->parts);
}

void sem_var_init(sem_var_t *var, char *name, char *type) {
  var->name=name;
  var->type=type;
  var->occr=0;
  var->occk=0;
  var->occb=0;
  var->occg=0;
}

void sem_var_destruct(sem_var_t *var) {
  free(var->name);
}

void sem_rule_init(sem_rule_t *rule, char *name, sem_expr_t *guard) {
  rule->name=name;
  alist_init(rule->vars);
  alist_init(rule->kept);
  alist_init(rule->rem);
  alist_init(rule->body);
  rule->guard=(*guard);
}

void sem_rule_destruct(sem_rule_t *rule) {
  free(rule->name);
  for (int i=0; i<alist_len(rule->vars); i++) sem_var_destruct(alist_ptr(rule->vars,i));
  alist_free(rule->vars);
  for (int i=0; i<alist_len(rule->kept); i++) sem_conocc_destruct(alist_ptr(rule->kept,i));
  alist_free(rule->kept);
  for (int i=0; i<alist_len(rule->rem); i++) sem_conocc_destruct(alist_ptr(rule->rem,i));
  alist_free(rule->rem);
  for (int i=0; i<alist_len(rule->body); i++) sem_conocc_destruct(alist_ptr(rule->body,i));
  alist_free(rule->body);
  sem_expr_destruct(&(rule->guard));
}

void sem_cchr_init(sem_cchr_t *cchr) {
  alist_init(cchr->rules);
  alist_init(cchr->cons);
  alist_init(cchr->exts);
}

void sem_cchr_destruct(sem_cchr_t *cchr) {
  for (int i=0; i<alist_len(cchr->rules); i++) sem_rule_destruct(alist_ptr(cchr->rules,i));
  alist_free(cchr->rules);
  for (int i=0; i<alist_len(cchr->cons); i++) sem_rule_destruct(alist_ptr(cchr->cons,i));
  alist_free(cchr->cons);
  for (int i=0; i<alist_len(cchr->exts); i++) sem_rule_destruct(alist_ptr(cchr->exts,i));
  alist_free(cchr->exts);
}

static char *copy_string(char *in) {
  char *ret=malloc(strlen(in)+1);
  strcpy(ret,in);
  return ret;
}

void sem_generate_cchr(sem_cchr_t *out,cchr_t *in) {
  for (int i=0; i<alist_len(in->exts) {
    alist_add(out->exts,copy_string(alist_get(in->exts)));
  }
  
}
