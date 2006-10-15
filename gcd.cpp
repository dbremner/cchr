
int inline sub(int a,int b) {
  return a-b;
}

int inline geq(int a,int b) {
  return a>=b;
}

int inline eq(int a,int b) {
  return a==b;
}

extern "CCHR" {
  constraint gcd(int);

  function subtract(int,int);
  function geq(int,int);
  function eq(int,int);

  gcd(N) <=> eq(N,0) | true;
  gcd(N) / gcd(M) <=> geq(M,N) | gcd(sub(M,N));

}
