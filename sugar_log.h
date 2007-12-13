#ifndef _sugar_log_h_
#define _sugar_log_h_ 1

#include "semtree.h"
#include "output.h"

int sugar_log_analyse(sem_cchr_t *cchr);
int sugar_log_codegen(sem_cchr_t *cchr, output_t *code, output_t *header);

#endif
