#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "ht_cuckoo.h"

typedef struct {
  uint32_t key;
  uint32_t val;
  int set;
} het_t;

#define het_eq(het1,het2) ((het1)->key == (het2)->key)
#define het_defined(het1) ((het1)->set)
#define het_unset(het) {(het)->set=0;}

uint32_t hashword(const uint32_t *k,size_t length,uint32_t initval);


uint32_t hash1(het_t *val) {
  return (uint32_t)hashword(&(val->key),1,0x2B7E1516UL);
}

uint32_t hash2(het_t *val) {
  return (uint32_t)hashword(&(val->key),1,0x3243F6A9UL);
}

ht_cuckoo_code(hash_t,het_t,hash1,hash2,het_eq,het_defined,het_unset,het_unset)

#define SIZE (1<<12)

int main(void) {
  hash_t ht;
  hash_t_init(&ht);
  uint32_t *key=malloc(sizeof(uint32_t)*SIZE);
  uint32_t *val=malloc(sizeof(uint32_t)*SIZE);
  int *del=malloc(sizeof(int)*SIZE);
  for (int l=0; l<SIZE; l++) {
  	val[l]=(uint32_t)rand();
  	key[l]=l+(uint32_t)rand()*SIZE;
  	del[l]=0;
  }
  for (int j=0; j<SIZE; j++) {
    het_t het={.key=key[j],.val=val[j],.set=1};
    hash_t_set(&ht,&het);
    int dl=rand()%SIZE;
    if (dl<=j) {
        het.key=key[dl];
    	hash_t_unset(&ht,&het);
    	del[dl]=1;
    }
    int ow=rand()%SIZE;
    if (ow<=j) {
    	val[ow]=rand();
    	del[ow]=0;
	het.key=key[ow];
	het.val=val[ow];
	het.set=1;
    	hash_t_set(&ht,&het);
    }
/*    for (int k=0; k<SIZE; k++) {
      int mh=(k<=j) && !del[k];
      het.key=key[k];
      assert(hash_t_have(&ht,&het)==mh);
      if (mh) assert(hash_t_find(&ht,&het)->val==val[k]);
    }*/
  }
  hash_t_free(&ht);
  free(key);
  free(val);
  free(del);
  return 0;
}
