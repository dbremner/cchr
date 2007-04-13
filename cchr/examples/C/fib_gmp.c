#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>

typedef struct {
  mpz_t v;
} bigint_t;

void fib_gmp(int upto) {
  bigint_t *nums=malloc(sizeof(bigint_t)*(upto+1));
  mpz_init_set_si(nums[0].v,1);
  mpz_init_set_si(nums[1].v,1);
  for (int j=2; j<=upto; j++) {
    mpz_init(nums[j].v);
    mpz_add(nums[j].v,nums[j-2].v,nums[j-1].v);
  }
//  gmp_printf("fib(%i,%Zd)\n",upto,nums[upto].v);
  for (int j=0; j<=upto; j++) {
    mpz_clear(nums[j].v);
  }
  free(nums);
}

int main(int argc,char **argv) {
  int a=(argc>1 ? (int)strtol(argv[1],NULL,0) : 92);
  fib_gmp(a);
  return 0;
}
