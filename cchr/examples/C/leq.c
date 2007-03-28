#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "logical.h"

#define MAX(a,b) ((a)>(b) ? (a) : (b))

logical_code(int,log_int_t,logical_nodestr)

void addleq(int size,int a,int b,log_int_t *vars,int *cmp) {
  cmp[size*a+b]++;
  a=log_int_t_getval(vars[a]);
  b=log_int_t_getval(vars[b]);
  if (a==b) {
    return;
  }
  int ov=cmp[size*b+a];
  if (ov) {
    log_int_t_seteq(vars[a],vars[b]);
    int low=log_int_t_getval(vars[a]);
    for (int j=0; j<size; j++) {
      cmp[j*size+low] = cmp[j*size+a]+cmp[j*size+b];
      cmp[low*size+j] = cmp[a*size+j]+cmp[b*size+a];
    }
    for (int j=0; j<size; j++) {
      if (cmp[j*size+low]) addleq(size,j,low,vars,cmp);
      if (cmp[low*size+j]) addleq(size,low,j,vars,cmp);
    }
    return;
  }
  for (int j=0; j<size; j++) {
    if (cmp[size*b+j]) {
      addleq(size,a,j,vars,cmp);
      if (cmp[size*b+a]>ov) return;
    }
  }
}

void test(int size) {
  int *cmp=malloc(sizeof(int)*size*size);
  log_int_t *vars=malloc(sizeof(log_int_t)*size);
  for (int i=0; i<size; i++) {
    vars[i]=log_int_t_create();
    log_int_t_setval(vars[i],i);
  }
  memset(cmp,0,sizeof(int)*size*size);
  for (int i=0; i<size; i++) {
    addleq(size,i,(i+1)%size,vars,cmp);
  }
  for (int i=0; i<size; i++) {
    if (!log_int_t_testeq(vars[i],vars[(i+1)%size])) printf("outch %i != %i\n",i,(i+1)%size);
  }
  for (int i=0; i<size; i++) {
    log_int_t_destruct(vars[i]);
  }
  free(vars);
  free(cmp);
}

int main(void) {
  for (int j=0; j<50; j++) {
    test(100);
  }
  return 0;
}
