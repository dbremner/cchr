/****************************************************************************\
* RAIDRACE - A speed-optimized raytracer in C                                *
* Written as a project for the course 'Computer Graphics' H0331a, KULeuven   *
*                                                                            *
* Copyright 2006 Pieter Wuille                                               *
*                                                                            *
\****************************************************************************/

#ifndef _model_h_
#define _model_h_ 1

#include <stdlib.h>

typedef struct {
  void **list;
  int na,nu;
} model_t;

void model_init(model_t *model);
void model_destroy(model_t *model);
void* model_add(model_t *model, void *block);
void model_del(model_t *model, void *block);

#define model_malloc(model,size) (model_add(model,malloc(size)))

#define model_free(model,block) do {\
  free(block);\
  model_del(model,block);\
} while(0);

#endif
