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


struct _rule_t_struct {
  char *name;
  expr_t **kept;
  expr_t **removed;
  expr_t **body;
  alist_declare(char *,vars);
  expr_t *guard;
};

typedef struct {
  alist_declare(rule_t *,rules);
  alist_declare(constraint_t *,cons);
  alist_declare(char *,exts);
  model_t model;
} cchr_t;

#define EXPR_TYPE_NONE (-1)
#define EXPR_TYPE_VAR 0
#define EXPR_TYPE_EXT 1
#define EXPR_TYPE_CALL 2
#define EXPR_TYPE_CONS 3


struct _expr_t_struct {
  int type;
  union {
    char *var;
    char *ext;
    struct {
      expr_t *func;
      expr_t **args;
      int nargs;
    } call;
    struct {
      constraint_t *con;
      expr_t **args;
    } cons;
  } data;
};

expr_t *parse_expr(cchr_t *chr, rule_t *rule, char **pos);
expr_t **parse_exprlist(cchr_t *chr, rule_t *rule, char **pos, int *nargs);
void dump_expr(expr_t *expr,FILE *out);

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
    } else { // CCHR simpagation rule
      rule_t *rule=malloc(sizeof(rule_t));
      rule->name=NULL;
      alist_init(rule->vars);
      rule->guard=NULL;
      while (isspace(*pos)) pos++;
      int len=0;
      while (isalpha(pos[len]) || pos[len]=='_') len++;
      while (isalnum(pos[len]) || pos[len]=='_') len++;
      int spc=0;
      while (isspace(pos[len+spc])) spc++;
      if (pos[len+spc]=='@') {
        rule->name=model_malloc(&(cchr.model),len+1);
        strncpy(rule->name,pos,len); rule->name[len]=0;
        pos+=(len+spc+1);
      }
      int nkept=0;
      expr_t **expr_kept=parse_exprlist(&cchr,rule,&pos,&nkept);
      if (expr_kept==NULL) return 1; // invalid expression
      while (isspace(*pos)) pos++;
      int nremoved=0;
      expr_t ** expr_removed=NULL;
      if (strlen(pos)>=1 && (pos[0]=='/' || pos[0]=='\\')) {
        pos++;
        expr_removed=parse_exprlist(&cchr,rule,&pos,&nremoved);
        if (!expr_removed) return 1;
        while (isspace(*pos)) pos++;
      }
      if (strlen(pos)>=3 && !strncmp(pos,"==>",3)) {
        if (expr_removed) {
          fprintf(stderr,"cannot put have removed constraints in a propagation (==>) rule\n");
          return 1;
        }
        pos+=3;
      } else if (strlen(pos)>=3 && !strncmp(pos,"<=>",3)) {
        if (!expr_removed) {
          expr_removed=expr_kept;
          nremoved=nkept;
          expr_kept=NULL;
          nkept=0;
        }
        pos+=3;
      } else {
        fprintf(stderr,"unexpected string: [%s]\n",pos);
      }
      int nbody;
      expr_t **expr_body=parse_exprlist(&cchr,rule,&pos,&nbody);
      expr_t *guard=NULL;
      if (!expr_body) return 1;
      while (isspace(*pos)) pos++;
      if (strlen(pos)>=1 && pos[0]=='|') {
        if (nbody>1) {
          fprintf(stderr,"cannot have more than one constraint in guard\n");
          return 1;
        }
        if (nbody==1) guard=expr_body[0];
        pos++;
        expr_body=parse_exprlist(&cchr,rule,&pos,&nbody);
        if (!expr_body) return 1;
      }
      /*fprintf(out,"cchr_%s: ",rule->name);
      int j=0;
      while (j<nkept) {
        if (j) fprintf(out,",");
        dump_expr(expr_kept[j],out);
        j++;
      }
      fprintf(out," \\ ");
      j=0;
      while (j<nremoved) {
        if (j) fprintf(out,",");
        dump_expr(expr_removed[j],out);
        j++;
      }
      fprintf(out," <=> ");
      if (guard) {
        dump_expr(guard,out);
        fprintf(out," | ");
      }
      j=0;
      while (j<nbody) {
        if (j) fprintf(out,",");
        dump_expr(expr_body[j],out);
        j++;
      }
      fprintf(out,"\n");*/
      model_add(&(cchr.model),rule->vars._d);
      rule->kept=expr_kept;
      rule->removed=expr_removed;
      rule->body=expr_body;
      rule->guard=guard;
      
    }
  }
  model_add(&(cchr.model),cchr.rules._d);
  model_add(&(cchr.model),cchr.cons._d);
  model_add(&(cchr.model),cchr.exts._d);
  model_destroy(&(cchr.model));
  return 0; 
}

expr_t **parse_exprlist(cchr_t *chr, rule_t *rule, char **pos, int *nargs) {
  alist_declare(expr_t *,args);
  alist_init(args);
  do {
    while (isspace(**pos)) (*pos)++;
    if (**pos == ')' || **pos==0) break;
    expr_t *rt=parse_expr(chr,rule,pos);
    if (rt==NULL) {alist_free(args); fprintf(stderr,"(arg %i NULL)\n",alist_len(args)); return NULL;}
    while (isspace(**pos)) (*pos)++;
    alist_add(args,rt);
    if (**pos != ',') break;
    (*pos)++;
  } while(1);
  *nargs=alist_len(args);
  alist_add(args,NULL);
  expr_t **ret=alist_ptr(args,0);
  model_add(&(chr->model),ret);
  return ret;
}

/* ret.data.call.nargs=alist_len(args);
   ret.data.call.args=alist_ptr(args,0);
   if (**pos == ')') (*pos)++;
      ret.data.call.func=inner;

*/

expr_t *parse_expr(cchr_t *chr, rule_t *rule, char **pos) {
  expr_t ret;
  ret.type=EXPR_TYPE_NONE;
  while (isspace(**pos)) (*pos)++;
  char *npos=*pos;
  int len=0;
  while (isalpha((*pos)[len]) || (*pos)[len]=='_') len++;
  while (isalnum((*pos)[len]) || (*pos)[len]=='_') len++;
  int spc=0;
  if (len==0) return NULL;
  while (isspace((*pos)[len+spc])) spc++;
  (*pos)+=(len+spc);
  expr_t **args=NULL;
  //printf("['%.*s': parsing args...]\n",len,npos);
  int nargs=0;
  if ((**pos) == '(') {
    (*pos)++;
    args=parse_exprlist(chr,rule,pos,&nargs);
    if (args==NULL) return NULL;
    if (**pos == ')') (*pos)++;
    //printf("['%.*s': parsed %i args]\n",len,npos,nargs);
  } else {
    //printf("['%.*s': no args]\n",len,npos);
  }
  //printf("[after '%.*s': <%s>]\n",len,npos,*pos);
  if (ret.type==EXPR_TYPE_NONE) {
    int k=0;
    while (k<alist_len(chr->cons)) {
      if (nargs==alist_get(chr->cons,k)->nargs && strlen(alist_get(chr->cons,k)->name)==len && !strncmp(alist_get(chr->cons,k)->name,npos,len)) break;
      k++;
    }
    if (k<alist_len(chr->cons)) {
      //printf("['%.*s': seems constraint]\n",len,npos);
      ret.type=EXPR_TYPE_CONS;
      ret.data.cons.con=alist_get(chr->cons,k);
      ret.data.cons.args=args;
    }
  }
  if (ret.type==EXPR_TYPE_NONE) {
    int n=0;
    while (n<alist_len(chr->exts)) {
      if (strlen(alist_get(chr->exts,n))==len && !strncmp(alist_get(chr->exts,n),npos,len)) break;
      n++;
    }
    if (n<alist_len(chr->exts)) {
      //printf("['%.*s': seems external]\n",len,npos);
      ret.type=EXPR_TYPE_EXT;
      ret.data.ext=alist_get(chr->exts,n);
      if (args) {
        expr_t *inner=model_malloc(&(chr->model),sizeof(expr_t));
        *inner=ret;
        ret.type=EXPR_TYPE_CALL;
        ret.data.call.func=inner;
        ret.data.call.args=args;
        ret.data.call.nargs=nargs;
      }
    }
  }
  if (ret.type==EXPR_TYPE_NONE && !args && isupper((npos)[0])) {
    //printf("['%.*s': seems var]\n",len,npos);
    ret.type=EXPR_TYPE_VAR;
    int j=0;
    //printf("['%.*s': searching through %i existing vars]\n",len,npos,alist_len(rule->vars));
    while (j<alist_len(rule->vars)) {
      if (strlen(alist_get(rule->vars,j))==len && !strncmp(alist_get(rule->vars,j),npos,len)) break;
      j++;
    }
    if (j<alist_len(rule->vars)) {
      ret.data.var=alist_get(rule->vars,j);
    } else {
      char *vnam=model_malloc(&(chr->model),len+1);
      strncpy(vnam,npos,len); vnam[len]=0;
      alist_add(rule->vars,vnam);
      ret.data.var=vnam;
    }
  }
  if (ret.type==EXPR_TYPE_NONE) {
    fprintf(stderr,"(<%s> neither var,ext or cons)\n",npos);
    return NULL;
  }
  //printf("['%.*s': allocating type %i]\n",len,npos,ret.type);
  expr_t *rr=model_malloc(&(chr->model),sizeof(expr_t));
  *rr=ret;
  return rr;
}

void dump_expr(expr_t *expr,FILE *out) {
  switch (expr->type) {
    case EXPR_TYPE_VAR:
      fprintf(out,"var_%s",expr->data.var);
      break;
    case EXPR_TYPE_EXT:
      fprintf(out,"ext_%s",expr->data.ext);
      break;
    case EXPR_TYPE_CALL:
      dump_expr(expr->data.call.func,out);
      fprintf(out,".call(");
      int j=0;
      while (j<expr->data.call.nargs) {
        if (j) fprintf(out,",");
        dump_expr(expr->data.call.args[j],out);
        j++;
      }
      fprintf(out,")");
      break;
    case EXPR_TYPE_CONS:
      fprintf(out,"con_%s(",expr->data.cons.con->name);
      int k=0;
      while (k<expr->data.cons.con->nargs) {
        if (k) fprintf(out,",");
        dump_expr(expr->data.cons.args[k],out);
        k++;
      }
      fprintf(out,")");
      break;
    default:
      fprintf(out,"unk_%i",expr->type);
  }
}
