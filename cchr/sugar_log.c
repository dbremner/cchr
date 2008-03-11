/**
 * Syntaxtic sugar for logical variables in CCHR
 */

#include "analyse.h"
#include "semtree.h"
#include "output.h"

/* apply syntactic sugar (automatic generation of contraint-specific add/kill/init/destr hooks for logicals) */
void static apply_post_sugar(sem_cchr_t *out, int cid) {
  sem_constr_t *con=alist_ptr(out->cons,cid);
  for (int i=0; i<alist_len(con->types); i++) {
    int type=alist_get(con->types,i);
    if (type>=0) {
      sem_vartype_t *typ=alist_ptr(out->types,type);
      if (typ->log_ground>=0) { /* logical */
        sem_typeocc_t *n;
        alist_new(typ->log_idx,n);
        n->con=cid;
        n->arg=i;
        alist_declare(sem_exprpart_t,el);
	alist_init(el);
	sem_exprpart_t *elp;
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("{"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_copy",typ->name));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_var(elp,i+1);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(";"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("}"));
	alist_addall(con->init.parts,el);
	alist_free(el);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("{"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_destruct",typ->name));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_var(elp,i+1);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(";"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("}"));
	alist_addall(con->destr.parts,el);
	alist_free(el);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("{"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("CSM_IDX_ADD"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_getextrap",typ->name));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_var(elp,i+1);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("->"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_%i_arg%i",con->name,alist_len(con->types),i+1));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(","));
	alist_new(el,elp);sem_exprpart_init_var(elp,0);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(";"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("CSM_IDX_ADD"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_getextrap",typ->name));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_var(elp,i+1);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("->"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_%i_ra",con->name,alist_len(con->types)));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(","));
	alist_new(el,elp);sem_exprpart_init_var(elp,0);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(";"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("}"));
	alist_addall(con->add.parts,el);
	alist_free(el);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("{"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("CSM_IDX_DEL"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_getextrap",typ->name));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_var(elp,i+1);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("->"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_%i_arg%i",con->name,alist_len(con->types),i+1));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(","));
	alist_new(el,elp);sem_exprpart_init_var(elp,0);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(";"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("CSM_IDX_DEL"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_getextrap",typ->name));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("("));
	alist_new(el,elp);sem_exprpart_init_var(elp,i+1);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("->"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,make_message("%s_%i_ra",con->name,alist_len(con->types)));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(","));
	alist_new(el,elp);sem_exprpart_init_var(elp,0);
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(")"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string(";"));
	alist_new(el,elp);sem_exprpart_init_lit(elp,copy_string("}"));
	alist_addall(con->kill.parts,el);
	alist_free(el);
      }
    }
  }
}

void static apply_pre_sugar(sem_cchr_t *out, int cid) {
  sem_constr_t *con=alist_ptr(out->cons,cid);
  for (int i=0; i<alist_len(con->types); i++) {
    int type=alist_get(con->types,i);
    if (type>=0) {
      sem_vartype_t *typ=alist_ptr(out->types,type);
      if (typ->log_ground>=0) { /* logical */
        /* set equality function for logicals */
        typ->equality=make_message("%s_testeq",typ->name);
      }
    }
  }
}

int sugar_log_pre_analyse(sem_cchr_t *cchr) {
  for (int i=0; i<alist_len(cchr->cons); i++) {
    apply_pre_sugar(cchr,i);
  }
  return 0;
}

int sugar_log_post_analyse(sem_cchr_t *cchr) {
  for (int i=0; i<alist_len(cchr->cons); i++) {
    apply_post_sugar(cchr,i);
  }
  return 0;
}

void static codegen_sugar(sem_cchr_t *cchr, output_t *code, output_t *header, int tid) {
  sem_vartype_t *typ=alist_ptr(cchr->types,tid);
  sem_vartype_t *gtyp=alist_ptr(cchr->types,typ->log_ground);
  output_string(header,"#include \"logical.h\"\n\n");
  alist_declare(char*,cids);
  alist_declare(char*,cods);
  alist_init(cids);
  alist_init(cods);
  for (int i=0; i<alist_len(typ->log_idx); i++) {
    sem_typeocc_t *to=alist_ptr(typ->log_idx,i);
    sem_constr_t *con=alist_ptr(cchr->cons,to->con);
    char *a1=make_message("%s_%i_arg%i",con->name,alist_len(con->types),to->arg+1);
    char *a2=make_message("%s_%i_ra",con->name,alist_len(con->types));
    int found=0;
    for (int j=0; j<alist_len(cids); j++) {
      if (!strcmp(alist_get(cids,j),a2)) {found=1; break;}
    }
    alist_add(cids,a1);
    if (!found) {
      alist_add(cids,a2);
      alist_add(cods,make_message("%s_%i",con->name,alist_len(con->types)));
    }
  }
  output_indent(header,"typedef struct {","}");
  for (int i=0; i<alist_len(cids); i++) {
    char *s=alist_get(cids,i);
    output_fmt(header,"CSM_IDX_DEFINE(%s);\n",s);
  }
  output_unindent(header);
  output_fmt(header," %s_tag_t;\n\n",typ->name);
  output_fmt(header,"logical_header(%s,%s_tag_t,%s)\n\n",gtyp->name,typ->name,typ->name);
  output_string(code,"\n");
  output_fmt(code,"#define %s_cb_created(val) ",typ->name);
  output_indent(code,"{ \\","}\n");
  for (int i=0; i<alist_len(cids); i++) {
    char* s=alist_get(cids,i);
    output_fmt(code,"CSM_IDX_INIT(%s_getextrap(val)->%s); \\\n",typ->name,s);
  }
  output_unindent(code);
  output_string(code,"\n");
  output_fmt(code,"#define %s_cb_merged(val1,val2) ",typ->name);
  output_indent(code,"{ \\","}\n");
  for (int i=0; i<alist_len(cids); i++) {
    char* s=alist_get(cids,i);
    output_fmt(code,"CSM_IDX_MERGE(%s_getextrap(val1)->%s,%s_getextrap(val2)->%s); \\\n",typ->name,s,typ->name,s);
  }
  output_unindent(code);
  output_string(code,"\n");
  output_fmt(code,"#define %s_cb_changed(val) { %s_reactivate(val); } \n\n",typ->name,typ->name);
  output_fmt(code,"#define %s_cb_destrval(val) \n\n",typ->name,typ->name);
  output_fmt(code,"#define %s_cb_destrtag(val) ",typ->name);
  output_indent(code,"{ \\","}\n");
  for (int i=0; i<alist_len(cids); i++) {
    char* s=alist_get(cids,i);
    output_fmt(code,"CSM_IDX_DESTR(%s_getextrap(val)->%s); \\\n",typ->name,s);
  }
  output_unindent(code);
  output_string(code,"\n\n");
  output_fmt(code,"#define %s_reactivate(val) ",typ->name);
  output_indent(code,"{ \\","}\n");
  for (int i=0; i<alist_len(cods); i++) {
    char* s=alist_get(cods,i);
    output_fmt(code,"CSM_IDX_REACT(val,%s,%s); \\\n",s,typ->name);
  }
  output_unindent(code);
  output_string(code,"\n\n");
  output_fmt(code,"logical_code(%s,%s_tag_t,%s,%s_cb)\n\n",gtyp->name,typ->name,typ->name,typ->name);
  for (int i=0; i<alist_len(cids); i++) {
    free(alist_get(cids,i));
  }
  for (int i=0; i<alist_len(cods); i++) {
    free(alist_get(cods,i));
  }
  alist_free(cids);
  alist_free(cods);
}

int sugar_log_codegen(sem_cchr_t *cchr, output_t *code, output_t *header) {
  for (int i=0; i<alist_len(cchr->types); i++) {
    sem_vartype_t *typ=alist_ptr(cchr->types,i);
    if (typ->log_ground >= 0) codegen_sugar(cchr,code,header,i);
  }
  return 0;
}
