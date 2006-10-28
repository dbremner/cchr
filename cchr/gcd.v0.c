#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t gcd(uint64_t a,uint64_t b) {
  begin:
  if (b==0) return a;
  if (a>=b) {
    a-=b;
    goto begin;
  }
  uint64_t c=b-a;
  b=a;
  a=c;
  goto begin;
}

int main(void) {
  uint64_t a=10ULL;
  uint64_t b=17856535355ULL;
  uint64_t r=gcd(a,b);
  printf("gcd(%llu)\n",(unsigned long long)r);
  return 0;
}
