#ifndef _GIO_H_
#define _GIO_H_ 

#include "semtree.h"

typedef enum {
  GIO_TYPE_ITER,
  GIO_TYPE_IDXITER,
  GIO_TYPE_LSTMT,
  GIO_TYPE_LVAR,
  GIO_TYPE_IF
} gio_type_t;

#define GIO_TYPE_ITER 0
#define GIO_TYPE_IDXITER 1
#define GIO_TYPE_OUT 2

typedef struct {
  gio_type_t type;
  union {
    struct {
      uint32_t cot;
    } iter;
    struct {
      uint32_t cot;
      alist_declare(int,argp);
      alist_declare(sem_expr_t,args);
    } idxiter;
    int out;
  } data;
} gio_entry_t;

typedef struct {
  alist_declare(gio_entry_t,order);
} gio_t;

#endif
