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

void sem_exprpart_init_var(sem_exprpart_t *exprp, int var) {
  exprp->type=SEM_EXPRPART_TYPE_VAR;
  exprp->data.var=var;
}

void sem_exprpart_init_lit(sem_exprpart_t *exprp, char *str) {
  exprp->type=SEM_EXPRPART_TYPE_LIT;
  exprp->data.lit=str;
}

void sem_expr_init(sem_expr_t *expr) {
  alist_init(expr->parts);
}

void sem_expr_add_part(sem_expr_t *expr, sem_exprpart_t *exprp) {
  alist_add(expr->parts,(*exprp));
}

void sem_conocc_init(sem_conocc_t *occ, int constr
void abs2sem(cchr_t *in,
