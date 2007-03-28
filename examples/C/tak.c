#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ht_cuckoo.h"
#include "lookup3.h"

typedef struct {
  uint32_t key[3];
  int val;
} cache_t;

#define CACHE_DEFINED(VAL) ((VAL)->val >= 0)
#define CACHE_UNDEF(VAL) {(VAL)->val = -1;}
#define CACHE_HASH1(VAL) hashbytes(&((VAL)->key),sizeof((VAL)->key),0x16A09E66UL)
#define CACHE_HASH2(VAL) hashbytes(&((VAL)->key),sizeof((VAL)->key),0x1BB67AE8UL)
#define CACHE_EQ(V1,V2) (((V1)->key[0]==(V2)->key[0]) && ((V1)->key[1]==(V2)->key[1]) && ((V1)->key[2]==(V2)->key[2]))

ht_cuckoo_code(idx_t,cache_t,CACHE_HASH1,CACHE_HASH2,CACHE_EQ,CACHE_DEFINED,CACHE_UNDEF,CACHE_UNDEF)

int static inline calcTak_(int x,int y,int z,idx_t *tab) {
  if (x<=y) {
    return z;
  } else {
    cache_t kv={.key={x,y,z},.val=0};
    cache_t *find=idx_t_find(tab,&kv);
    if (find) return find->val;
    int r1=calcTak_(x-1,y,z,tab);
    int r2=calcTak_(y-1,z,x,tab);
    int r3=calcTak_(z-1,x,y,tab);
    int ret=calcTak_(r1,r2,r3,tab);
    kv.val=ret;
    idx_t_set(tab,&kv);
    return ret;
  }
}

int static calcTak(int x,int y,int z) {
  idx_t tab;
  idx_t_init(&tab);
  int ret=calcTak_(x,y,z,&tab);
  idx_t_free(&tab);
  return ret;
}


int main(void) {
  int ret;
  //for (int j=0; j<10; j++) {
    ret=calcTak(500,450,405);
  //}
  printf("%i\n",ret);
  return 0;
}
