#include <stdio.h>

cchr {
  constraint fib(int,uint64_t),init(int);
  
  begin @ init(_) ==> fib(0,1ULL), fib(1,1ULL);
  calc @  init(Max), fib(N-1,M1), fib(N,M2) ==> N<Max | uint64_t NP=N+1, fib(NP, M1+M2);
//  fini @ init(Max) <=> true; /* this removes init_1 before any fib_2 is generated */
  fini @ fib(Max,_) \ init(Max) <=> true;
}

int main(void) {
  cchr_runtime_init();
  cchr_add_init_1(92);
  dcls_iter(_global_runtime.store,j,CCHR_CONS_TYPE_fib_2,{
    cchr_entry_t *ent=dcls_ptr(_global_runtime.store,j);
    printf("fib(%i,%llu)\n",(int)(ent->data.fib_2.arg1),(unsigned long long)(ent->data.fib_2.arg2));
  })
  return 0;
}
