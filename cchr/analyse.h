/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| abs2sem.h - header for syntax tree to semantic tree conversion             |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 


#ifndef ANALYSE_H_
#define ANALYSE_H_

#include "semtree.h"

int sem_generate_cchr(sem_cchr_t* out,cchr_t* in);
void sem_cchr_destruct(sem_cchr_t* cchr);
void sem_cchr_init(sem_cchr_t* cchr);
void destruct_cchr_t (cchr_t *cchr);


#endif /*ABS2SEM_H_*/
