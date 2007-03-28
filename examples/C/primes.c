#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int genPrimes(int upto) {
  int *primes=malloc((int)(sizeof(int)*upto*3.0/(2.0*log(upto))));
  primes[0]=2;
  int n=1;
  for (int j=3; j<=upto; j++) {
    int k=0;
    while (k<n) {
      int t=primes[k];
      if ((j%t)==0) break;
      k++;
    }
    if (k==n) {
      primes[n++]=j;
    }
  } 
  int ret=primes[n-1];
  free(primes);
  return ret;
}

int main(void) {
  int r;
  for (int k=0; k<1000; k++) {
    r=genPrimes(7500);
  }
  printf("%i\n",r);
  return 0;
}
