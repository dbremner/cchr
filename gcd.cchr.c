#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alist.h"

enum cchr_cons_type { CCHR_CONS_TYPE_UNK, CCHR_CONS_TYPE_GCD };

typedef struct {
  int arg1;
} cchr_cons_gcd_t;

typedef struct {
  enum cchr_cons_type type;
  int id;
  enum { CCHR_STATE_NOTYET, CCHR_STATE_STORED, CCHR_STATE_REMOVED } state;
  int gen_num;
  union {
    cchr_cons_gcd_t gcd;
  } data;
} cchr_cs_entry_t;

typedef struct {
  model_t model;
  alist_declare(cchr_cs_entry_t*,stack);
  int nextid;
} cchr_runtime_t;

void cchr_runtime_init(cchr_runtime *run) {
  alist_init(run->stack);
  model_init(&(run->model));
  run->nextid=1;
}

void cchr_runtime_make_id(cchr_runtime *run,cchr_entry_t *entry,enum cchr_cons_type type) {
  entry->id=run->nextid++;
  entry->state=CCHR_STATE_NOTYET;
  entry->gen_num=0;
  entry->type=type;
}

cchr_entry_t *cchr_runtime_store(cchr_runtime *run,cchr_entry_t *entry) {
  cchr_entry_t *ret=model_malloc(&(run->model),sizeof(cchr_entry_t);
  *ret=*entry;
  ret->state=CCHR_STATE_STORED;
  return ret;
}

cchr_entry_t *cchr_runtime_kill(cchr_runtime *run,cchr_entry_t *entry) {
  int j=0;
}

void cchr_add_gcd(cchr_runtime *run,int arg1) {
  /* simplification rules */
  cchr_cs_entry_t id;
  cchr_cs_entry_t *idp=NULL; /* null=not created, &id=not added, otherwise=stored/removed */
  /* <1> gcd(0) <=> true */
  if (arg1==0) {
    if (idp && idp!=&id) cchr_runtime_kill(run,idp);
  }
}
