#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "ht_cuckoo.h"

uint32_t hashword(const uint32_t *k,size_t length,uint32_t initval);


uint32_t hash1(uint32_t val) {
  return hashword(&val,1,0x2B7E15162UL);
}

uint32_t hash2(uint32_t val) {
  return hashword(&val,1,0x3243F6A88UL);
}

#define uint32_eq(v1,v2) ((v1)==(v2))

ht_cuckoo_code(hash_t,uint32_t,uint32_t,hash1,hash2,uint32_eq)

int main(void) {
  hash_t ht;
  hash_t_init(&ht);
  hash_t_double(&ht);
  hash_t_set(&ht,1,2);
  assert(*hash_t_get(&ht,1)==2);
  hash_t_set(&ht,2,3);
  hash_t_set(&ht,3,5);
  hash_t_set(&ht,4,7);
  hash_t_set(&ht,5,11);
  hash_t_set(&ht,6,13);
  hash_t_set(&ht,7,17);
  hash_t_set(&ht,8,19);
  hash_t_set(&ht,9,23);
  hash_t_set(&ht,10,29);
  hash_t_double(&ht);
  assert(*hash_t_get(&ht,1)==2);
  assert(*hash_t_get(&ht,2)==3);
  assert(*hash_t_get(&ht,3)==5);
  assert(*hash_t_get(&ht,4)==7);
  assert(*hash_t_get(&ht,5)==11);
  assert(*hash_t_get(&ht,6)==13);
  assert(*hash_t_get(&ht,7)==17);
  assert(*hash_t_get(&ht,8)==19);
  assert(*hash_t_get(&ht,9)==23);
  assert(*hash_t_get(&ht,10)==29);
  return 0;
}
