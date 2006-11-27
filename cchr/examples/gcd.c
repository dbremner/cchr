#include <stdint.h>
#include <stdio.h>
#include <string.h>

cchr {
  constraint gcd(uint64_t);

  triv @ gcd(0ULL) <=> true;
  dec @ gcd(N) \ gcd(M) <=> M>=N | gcd(M-N);
}

int main(int argc, char **argv) {
  uint64_t a1 = (uint64_t)(argc>1 ? strtoull(argv[1],NULL,0) : 993);
  uint64_t a2 = (uint64_t)(argc>2 ? strtoull(argv[2],NULL,0) : 37);
  cchr_runtime_init();
  cchr_add_gcd_1(a1);
  cchr_add_gcd_1(a2);
  printf("size=%u\n",(unsigned int)(sizeof(cchr_entry_t)));
  dcls_iter(_global_runtime.store,j,CCHR_CONS_TYPE_gcd_1,{
    cchr_entry_t *ent=dcls_ptr(_global_runtime.store,j);
    printf("gcd(%llu,%llu)=%llu\n",(unsigned long long)a1,(unsigned long long)a2,(unsigned long long)(ent->data.gcd_1.arg1));
  })
  return 0;
}
