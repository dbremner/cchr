#ifndef _alist_h_
#define _alist_h_ 1

#define alist_declare(type,var) struct { int _n,_a; type *_d; } var;
#define alist_init(var) do {(var)._n=0; (var)._a=0; (var)._d=NULL; } while(0);

#define alist_get(var,pos) ((var)._d[(pos)])
#define alist_ptr(var,pos) ((var)._d+(pos))
#define alist_new(var,ptr) do { \
  (ptr)=(var)._d+(var)._n; \
  (var)._n++; \
  if ((var)._n>(var)._a) { \
    (var)._a=(((var)._n*5)/4)+3; \
    (var)._d=realloc((var)._d,sizeof(*((var)._d))*(var)._a); \
  } \
} while(0);

#endif
