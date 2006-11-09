#ifndef _alist_h_
#define _alist_h_ 1

#define alist_declare(type,var) struct { int _n,_a; type *_d; } var;
#define alist_init(var) do {(var)._n=0; (var)._a=0; (var)._d=NULL; } while(0);

#define alist_get(var,pos) ((var)._d[(pos)])
#define alist_ptr(var,pos) ((var)._d+(pos))
#define alist_ensure(var,size) do { \
  if ((var)._a < (size)) { \
    (var)._a=(((size)*5)/4)+3; \
    (var)._d=realloc((var)._d,sizeof(*((var)._d))*(var)._a); \
  } \
} while(0);

#define alist_new(var,ptr) do { \
  (var)._n++; \
  alist_ensure(var,(var)._n); \
  (ptr)=(var)._d+(var)._n-1; \
} while(0);

#define alist_add(var,val) do { \
  alist_ensure(var,((var)._n+1)); \
  (var)._d[(var)._n]=val; \
  (var)._n++; \
} while(0);
#define alist_len(var) ((var)._n)
#define alist_free(var) do { free((var)._d); (var)._d=NULL; (var)._n=0; (var)._a=0; } while(0);

#define alist_addall(var1,var2) do { \
  alist_ensure((var1),((var1)._n+(var2)._n)); \
  int _j=0; \
  while (_j<(var2)._n) { \
    (var1)._d[(var1)._n++]=(var2)._d[_j++]; \
  } \
} while(0);

#endif
