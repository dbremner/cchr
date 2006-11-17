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

void sem_exprpart_init_var(

void abs2sem(cchr_t *in,