#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "alist.h"
#include "model.h"

enum cchr_cons_type { CCHR_CONS_TYPE_GCD };

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
} cchr_entry_t;

typedef struct {
  model_t model;
  alist_declare(cchr_entry_t*,store);
  int nextid;
} cchr_runtime_t;

cchr_runtime_t static _global_runtime;

void cchr_fire_gcd(int pid,int arg1);

void cchr_runtime_init() {
  alist_init(_global_runtime.store);
  model_init(&(_global_runtime.model));
  _global_runtime.nextid=1;
}

/* either store in constraint store, or destroy */
cchr_entry_t *cchr_make_entry(enum cchr_cons_type type) {
  cchr_entry_t *ret=malloc(sizeof(cchr_entry_t));
  ret->id=_global_runtime.nextid++;
  ret->state=CCHR_STATE_NOTYET;
  ret->gen_num=0;
  ret->type=type;
  return ret;
}

void cchr_destroy_entry(cchr_entry_t *entry) {
  free(entry);
}

int cchr_store(cchr_entry_t *entry) {
  int j=0;
  while (j<alist_len(_global_runtime.store)) {
    if (!alist_get(_global_runtime.store,j)) break;
    j++;
  }
  if (j<alist_len(_global_runtime.store)) {
    alist_get(_global_runtime.store,j)=entry;
  } else {
    alist_add(_global_runtime.store,entry);
  }
  return j;
}

void cchr_kill(int pid) {
  free(alist_get(_global_runtime.store,pid));
  alist_get(_global_runtime.store,pid)=NULL;
}

void cchr_add_gcd(int arg1) {
  printf("adding gcd(%i)\n",arg1);
  cchr_fire_gcd(-1,arg1);
}

void cchr_fire_gcd(int pid,int arg1) {
  cchr_entry_t *ent=NULL; /* before being stored, after being created */
  /* <1> gcd(0) <=> true */
  {
    if (arg1==0) {
      printf("rule 1 on (%i)\n",arg1);
      if (pid>=0) cchr_kill(pid);
      return;
    }
  }
  /* <2> gcd(I) \ _gcd(J)_ <=> J >= I | gcd(J-I) */
  {
    int pid2=0;
    while (pid2<alist_len(_global_runtime.store)) {
      if (alist_get(_global_runtime.store,pid2) &&
      (alist_get(_global_runtime.store,pid2)->type == CCHR_CONS_TYPE_GCD) &&
        (pid2 != pid) &&
        (arg1 >= alist_get(_global_runtime.store,pid2)->data.gcd.arg1)) {
	int pid2_arg1=alist_get(_global_runtime.store,pid2)->data.gcd.arg1;
	printf("rule 2 on (%i,%i)\n",arg1,pid2_arg1);
        if (pid>=0) cchr_kill(pid);
	cchr_add_gcd(arg1 % pid2_arg1);
	return;
      }
      pid2++;
    }
  }
  /* make sure entry is created */
  if (pid<0) ent=cchr_make_entry(CCHR_CONS_TYPE_GCD);
  ent->data.gcd.arg1=arg1;
  /* <3> _gcd(I)_ \ gcd(J) <=> J>=I | gcd(J-I) */
  {
    int pid2=0;
    while (pid2<alist_len(_global_runtime.store)) {
      if (alist_get(_global_runtime.store,pid2) &&
        (alist_get(_global_runtime.store,pid2)->type == CCHR_CONS_TYPE_GCD) &&
        (pid2 != pid) &&
	(alist_get(_global_runtime.store,pid2)->data.gcd.arg1>=arg1)) {
	int pid2_arg1=alist_get(_global_runtime.store,pid2)->data.gcd.arg1;
	printf("rule 3 on (%i,%i)\n",pid2_arg1,arg1);
	cchr_kill(pid2);
	if (pid<0) pid=cchr_store(ent);
	int oldgen=alist_get(_global_runtime.store,pid)->gen_num;
	int oldid=alist_get(_global_runtime.store,pid)->id;
	cchr_add_gcd(pid2_arg1 % arg1);
	if (alist_get(_global_runtime.store,pid)==NULL ||
	  (alist_get(_global_runtime.store,pid)->id != oldid) ||
	  (alist_get(_global_runtime.store,pid)->gen_num != oldgen)) {
	  return;
	}
      }
      pid2++;
    }
  }
  cchr_store(ent);
}

int main(void) {
  cchr_runtime_init();
  cchr_add_gcd(65535);
  cchr_add_gcd(978563);
  int j=0;
  while (j<alist_len(_global_runtime.store)) {
    cchr_entry_t *ent=alist_get(_global_runtime.store,j);
    if (ent && ent->type == CCHR_CONS_TYPE_GCD) {
      printf("gcd(%i)\n",ent->data.gcd.arg1);
    }
    j++;
  }
  return 0;
}
