/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| abs2sem.h - header for syntax tree to semantic tree conversion             |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 


#ifndef ANALYSE_H_
#define ANALYSE_H_

#include "semtree.h"
#include "parsestr.h"

void sem_expr_destruct(sem_expr_t *expr);
void sem_expr_init(sem_expr_t *expr);
void sem_expr_copy(sem_expr_t *src,sem_expr_t *dst,int start,int stop);

void sem_cchr_destruct(sem_cchr_t* cchr);
void sem_cchr_init(sem_cchr_t* cchr);

int sem_generate_cchr(sem_cchr_t* out,cchr_t* in);


#endif /*ANALYSE_H_*/
