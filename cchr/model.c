/****************************************************************************\
* RAIDRACE - A speed-optimized raytracer in C                                *
* Written as a project for the course 'Computer Graphics' H0331a, KULeuven   *
*                                                                            *
* Copyright 2006 Pieter Wuille                                               *
*                                                                            *
\****************************************************************************/

#include "model.h"

#include <stdlib.h>
#include <string.h>

void model_init(model_t *model) {
  model->list=NULL;
  model->na=0;
  model->nu=0;
}

void model_destroy(model_t *model) {
  int j=0;
  while (j<model->nu) {
    if (model->list[j]) free(model->list[j]);
    j++;
  }
  free(model->list);
  model_init(model);
}

void* model_add(model_t *model, void *block) {
  model->nu++;
  if (model->na<model->nu) {
    model->na=(5*model->nu/4+3);
    model->list=realloc(model->list,model->na*sizeof(void*));
  }
  model->list[model->nu-1]=block;
  return block;
}

void model_del(model_t *model, void *block) {
  int j=0;
  while (j<model->nu) {
    if (model->list[j]==block) {
      model->list[j]=NULL;
      break;
    }
    j++;
  }
  while (j>0 && (model->list[j-1]==NULL)) j--;
  model->nu=j;
}
