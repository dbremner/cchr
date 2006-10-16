#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "util.h"
#include "cchr.h"
#include "model.h"
#include "alist.h"

typedef struct {
  char *name;
  int nargs;
  char **types;
  
} constraint_t;

typedef struct _expr_t_struct expr_t;

typedef struct {
  constraint_t *con;
  expr_t **args;
} constraint_occ_t;

typedef struct {
  char *name;
  alist_declare(constraint_occ_t *,kept);
  alist_declare(constraint_occ_t *,removed);
  alist_declare(constraint_occ_t *,added);
  alist_declare(char *,vars);
  expr_t *guard;
} rule_t;

typedef struct {
  alist_declare(rule_t *,rules);
  alist_declare(containt_t *,cons);
  alist_declare(char *,exts);
  model_t model;
} cchr_t;

int process_cchr(FILE *in, FILE *out, int *line, int level) {
  char buf[MAXLINELEN];
  cchr_t cchr;
  alist_init(cchr.rules);
  alist_init(cchr.cons);
  alist_init(cchs.exts);
  model_init(&(cchr.model));
  while(1) {
    int ret=lread_wrapper(buf,in,line,level);
    if (ret==LREAD_ERROR) return 1;
    if (ret==LREAD_EOB) return 0;
    if (ret==LREAD_BOB) {
      fprintf(stderr,"CCHR doesn't support subblocks on line %i",*line);
      return 1;
    }
    char *pos=buf;
    if (starts_with(pos,"constraint")) {
    }
    if (starts_with(pos,"extern")) {
      while (*pos) {
        while (isspace(*pos) || *pos==',') pos++;
        int len=0;
        while (isalpha(pos[len]) || pos[len]=='_') len++;
        while (isalnum(pos[len]) || pos[len]=='_') len++;
      }
    }
  }
  return 0; 
}

