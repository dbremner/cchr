#include <stdint.h>
#include <stdio.h>

cchr {
  constraint gcd(uint64_t);

  triv @ gcd(0ULL) <=> true;
  dec @ gcd(N) \ gcd(M) <=> M>=N | gcd(M-N);
}

int main(void) {
  cchr_runtime_init();
  cchr_add_gcd_1(10ULL);
  cchr_add_gcd_1(17856535355ULL);
  printf("size=%u\n",(unsigned int)(sizeof(cchr_entry_t)));
  dcls_iter(_global_runtime.store,j,CCHR_CONS_TYPE_gcd_1,{
    cchr_entry_t *ent=dcls_ptr(_global_runtime.store,j);
    printf("gcd(%llu)\n",(unsigned long long)(ent->data.gcd_1.arg1));
  })
  return 0;
}
