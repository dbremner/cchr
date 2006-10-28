#ifndef _dcls_h_
#define _dcls_h_ 1

#include <stdint.h>

typedef uint32_t dcls_pid_t;
#define DCLS_EMPTY_PID (0xFFFFFFFF)

/**
 * _d : points to dynamic array
 * _s : size of the dynamic array
 * _fe: points to the first (youngest) empty cell (or DCLS_EMPTY_PID if there are no empty cells)
 * empty cells point to the next empty cell, and have DCLS_EMPTY_PID als _prev
 * the last empty cell points to DCLS_EMPTY_PID
 * cell pid=0 is the filled marker, and points to the first/last real filled (or itself if there are none)
 * things will break if you remove pid 0 from the filled set
 */
 
/* declare var to be a DCLS of type type */
#define dcls_declare(type,var) struct { dcls_pid_t _s,_fe; struct { type _data; dcls_pid_t _prev,_next;  } *_d;} var;

/* initialize a DCLS var */
#define dcls_init(var) do {\
  (var)._s=1; \
  (var)._d=malloc(sizeof((var)._d[0])); \
  (var)._d[0]._next=0; \
  (var)._d[0]._prev=0; \
  (var)._fe=DCLS_EMPTY_PID; \
} while(0);

/* ensure a DCLS var has size positions (including the filled marked) */
#define dcls_ensure(var,size) do {\
  dcls_pid_t _ns=(size);\
  if ((var)._s<_ns) {\
    (var)._d=realloc((var)._d,sizeof((var)._d[0])*_ns);\
    while ((var)._s<_ns) { \
      (var)._d[(var)._s]._prev=DCLS_EMPTY_PID; \
      (var)._d[(var)._s]._next=(var)._fe; \
      (var)._fe=(var)._s; \
      (var)._s++;\
    } \
  } \
} while(0);

/* allocate a position in DCLS var, and put it in pid */
/* the result will neither be in the filled set, nor in the empty set */
#define dcls_alloc(var,pid) do { \
  if ((var)._fe==DCLS_EMPTY_PID) dcls_ensure(var,(((var)._s+1)*5)/4+3); \
  (pid)=(var)._fe; \
  (var)._fe=(var)._d[(pid)]._next; \
  (var)._d[(pid)]._prev=DCLS_EMPTY_PID; \
} while(0);

/* bring a position into the empty set */
/* @pre: position was allocated (in filled set or not) */
#define dcls_free(var,pid) do { \
  if ((var)._d[(pid)]._prev!=DCLS_EMPTY_PID) {\
    dcls_pid_t _prev=(var)._d[(pid)]._prev; \
    dcls_pid_t _next=(var)._d[(pid)]._next; \
    (var)._d[_prev]._next=_next;\
    (var)._d[_next]._prev=_prev;\
    (var)._d[(pid)]._prev=DCLS_EMPTY_PID;\
  }\
  (var)._d[(pid)]._next=(var)._fe;\
  (var)._fe=(pid);\
} while(0);

/* bring a position into the filled set */
/* @pre: position was allocated (not in filled or empty set) */
#define dcls_used(var,pid) do { \
  (var)._d[(pid)]._next=(var)._d[0].next; \
  (var)._d[(pid)]._prev=0; \
  (var)._d[(var)._d[0].next]._prev=(pid); \
  (var)._d[0]._next=(pid); \
} while(0);

#define dcls_free(var) do { \
  free((var)._d); \
  (var)._d=NULL; \
  (var)._s=0; \
} while(0);

#endif
