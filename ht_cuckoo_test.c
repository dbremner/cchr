#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "ht_cuckoo.h"

uint32_t hashword(const uint32_t *k,size_t length,uint32_t initval);


uint32_t hash1(uint32_t val) {
  return (uint32_t)hashword(&val,1,0x2B7E15162UL);
}

uint32_t hash2(uint32_t val) {
  return (uint32_t)hashword(&val,1,0x3243F6A88UL);
}

#define uint32_eq(v1,v2) ((v1)==(v2))

ht_cuckoo_code(hash_t,uint32_t,uint32_t,hash1,hash2,uint32_eq)

#define SIZE (1<<17)

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
    hash_t_set(&ht,key[j],val[j]);
    int dl=rand()%SIZE;
    if (dl<=j) {
    	hash_t_unset(&ht,key[dl]);
    	del[dl]=1;
    }
    int ow=rand()%SIZE;
    if (ow<=j) {
    	val[ow]=rand();
    	del[ow]=0;
    	hash_t_set(&ht,key[ow],val[ow]);
    }
    /*for (int k=0; k<SIZE; k++) {
      int mh=(k<=j) && !del[k];
      assert(hash_t_have(&ht,key[k])==mh);
      if (mh) assert(*hash_t_get(&ht,key[k])==val[k]);
    }*/
  }
  printf("size=%i used=%i inserts=%i iters=%f\n",ht.size,ht.used,ht.ninsert,(double)ht.niter/ht.ninsert);
  hash_t_free(&ht);
  free(key);
  free(val);
  free(del);
  return 0;
}
