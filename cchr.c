#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "util.h"
#include "cchr.h"
#include "model.h"
#include "alist.h"

typedef struct _expr_t_struct expr_t;
typedef struct _rule_t_struct rule_t;

typedef struct {
  char *name;
  int nargs;
  char **types;
  alist_declare(rule_t *,keptby);
  alist_declare(rule_t *,removedby);
} constraint_t;

typedef struct {
  constraint_t *con;
  expr_t **args;
} constraint_occ_t;

struct _rule_t_struct {
  char *name;
  alist_declare(constraint_occ_t *,kept);
  alist_declare(constraint_occ_t *,removed);
  alist_declare(constraint_occ_t *,added);
  alist_declare(char *,vars);
  expr_t *guard;
};

typedef struct {
  alist_declare(rule_t *,rules);
  alist_declare(constraint_t *,cons);
  alist_declare(char *,exts);
  model_t model;
} cchr_t;

#define EXPR_TYPE_VAR 0
#define EXPR_TYPE_EXT 1
#define EXPR_TYPE_CALL 2

struct _expr_t_struct {
  int type;
  union {
    char *var;
    char *ext;
    expr_t **call;
  }
};

int process_cchr(FILE *in, FILE *out, int *line, int level) {
  char buf[MAXLINELEN];
  cchr_t cchr;
  alist_init(cchr.rules);
  alist_init(cchr.cons);
  alist_init(cchr.exts);
  model_init(&(cchr.model));
  while(1) {
    int ret=lread_wrapper(buf,in,line,level);
    if (ret==LREAD_ERROR) return 1;
    if (ret==LREAD_EOB) break;
    if (ret==LREAD_BOB) {
      fprintf(stderr,"CCHR doesn't support subblocks on line %i",*line);
      return 1;
    }
    char *pos=buf;
    if (starts_with(&pos,"constraint")) {
      while (*pos) {
        while (isspace(*pos) || *pos==',') pos++;
        int len=0;
        while (isalpha(pos[len]) || pos[len]=='_') len++;
        while (isalnum(pos[len]) || pos[len]=='_') len++;
        if (len==0) break;
        char *str=model_malloc(&(cchr.model),len+1);
        strncpy(str,pos,len); str[len]=0;
        pos+=len;
        alist_declare(char*,itypes);
        alist_init(itypes);
        while (isspace(*pos)) pos++;
        if (*pos == '(') {
          pos++;
          while (*pos) {
            while (isspace(*pos) || *pos==',') pos++;
            int ilen=0;
            if (*pos == ')' || *pos==0) break;
            while (pos[ilen] != ',' && pos[ilen] != 0 && pos[ilen] != ')') ilen++;
            while (isspace(pos[ilen-1])) ilen--;
            char *istr=model_malloc(&(cchr.model),len+1);
            strncpy(istr,pos,ilen); istr[ilen]=0;
            alist_add(itypes,istr);
            pos+=ilen;
          }
          pos++;
        }
        constraint_t *co=model_malloc(&(cchr.model),sizeof(constraint_t));
        co->name=str;
        co->nargs=itypes._n;
        co->types=itypes._d;
        alist_init(co->keptby);
        alist_init(co->removedby); /* TODO: model_add these lists after parsing rules */
        model_add(&(cchr.model),co->types);
        alist_add(cchr.cons,co);
      }
    }
    else if (starts_with(&pos,"extern")) {
      while (*pos) {
        while (isspace(*pos) || *pos==',') pos++;
        int len=0;
        while (isalpha(pos[len]) || pos[len]=='_') len++;
        while (isalnum(pos[len]) || pos[len]=='_') len++;
        if (len==0) break;
        char *str=model_malloc(&(cchr.model),len+1);
        strncpy(str,pos,len); str[len]=0;
        alist_add(cchr.exts,str);
        pos+=len;
      }
    } else {
      // CCHR simpagation rule
    }
  }
  model_add(&(cchr.model),cchr.rules._d);
  model_add(&(cchr.model),cchr.cons._d);
  model_add(&(cchr.model),cchr.exts._d);
  model_destroy(&(cchr.model));
  return 0; 
}

