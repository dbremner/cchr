/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| cchr_csm.h - header file included by compiler output                       |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef _cchr_csm_h_
#define _cchr_csm_h_

#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#include "dcls.h" /* for doubly-linked lists (constraint store) */
#include "lookup3.h" /* for hashing algorithm: declarations */
#include "lookup3.c" /* the hashing algorithm itself */
#include "ht_cuckoo.h" /* for hashtable */

#define cchr_id_t dcls_pid_t

/* some debug output macro's */
#define CSM_STRINGIFY_(X) #X
#define CSM_STRINGIFY(X) CSM_STRINGIFY_(X)

#ifdef CSM_CONF_DEBUG
#define CSM_DEBUG(...) __VA_ARGS__
#else
#define CSM_DEBUG(...)
#endif

#ifdef CSM_CONF_NOPROP
#define CSM_PROP(...)
#define CSM_NOPROP(...) __VA_ARGS__
#else
#define CSM_PROP(...) __VA_ARGS__
#define CSM_NOPROP(...)
#endif

#define CSM_INDENT { \
	CSM_DEBUG( \
		for (int i=0; i<_global_runtime.debugindent; i++) fprintf(stderr,"  "); \
	) \
}
#define CSM_PRINTF(INIT,TYPE) CSM_DEBUG( \
	CSM_INDENT \
	{ \
		fprintf(stderr,"%s%s: " FORMAT_##TYPE " | pid=%i id=%i\n",INIT,#TYPE FORMATARGS_##TYPE,(int)pid_self_,pid_self_!= DCLS_EMPTY_PID ? CSM_IDOFPID(pid_self_) : -1); \
	} \
)
#define CSM_FMTOUT(FMT,...) CSM_DEBUG( \
	{ \
		CSM_INDENT \
		fprintf(stderr,FMT "\n",__VA_ARGS__); \
	} \
)
#define CSM_FMTOUTX(FMT,POS,...) CSM_DEBUG( \
	{ \
		if ((POS)==0) CSM_INDENT; \
		fprintf(stderr,FMT,__VA_ARGS__); \
		if ((POS)==2) fputs("\n",stderr); \
	} \
)
#define CSM_STROUT(FMT) CSM_DEBUG( \
	{ \
		CSM_INDENT \
		fputs(FMT "\n",stderr); \
	} \
)
#define CSM_STROUTX(FMT,POS) CSM_DEBUG( \
	{ \
		if ((POS)==0) CSM_INDENT; \
		fputs(FMT,stderr); \
		if ((POS)==2) fputs("\n",stderr); \
	} \
)

/****** MACRO CALLBACKS ********/

#define CSM_CB_TypeEnum_S ,
#define CSM_CB_TypeEnum_D(NAME) CCHR_CONS_TYPE_ ## NAME

#define CSM_CB_IdxDefDefList_D(A,T,X) T A;
#define CSM_CB_IdxDefDefList_S
  
#define CSM_CB_IdxDefDef_S
#define CSM_CB_IdxDefDef_D(H,C) \
  typedef struct { \
    struct { \
      HASHDEF_##C##_##H(CSM_CB_IdxDefDefList,) \
    } key; \
    cchr_htdc_t val; \
  } cchr_contbl_##C##_##H##_t; \
  uint32_t static inline cchr_contbl_##C##_##H##_hash1(cchr_contbl_##C##_##H##_t *val) { return (uint32_t)hashbytes(&((val)->key),sizeof((val)->key),0x23C6EF37UL); } \
  uint32_t static inline cchr_contbl_##C##_##H##_hash2(cchr_contbl_##C##_##H##_t *val) { return (uint32_t)hashbytes(&((val)->key),sizeof((val)->key),0x2A54FF53UL); } \
  int static inline cchr_contbl_##C##_##H##_eq(cchr_contbl_##C##_##H##_t *v1,cchr_contbl_##C##_##H##_t *v2) { return eq((v1)->key,(v2)->key); } \
  ht_cuckoo_code(cchr_conht_##C##_##H##_t, cchr_contbl_##C##_##H##_t, cchr_contbl_##C##_##H##_hash1, cchr_contbl_##C##_##H##_hash2, cchr_contbl_##C##_##H##_eq, CSM_CTCB_DEFINED, CSM_CTCB_INIT, CSM_CTCB_UNDEF) 

#define CSM_CB_HistTypeDef_S
#define CSM_CB_HistTypeDef_D(T,V,...) \
  CSM_PROP( \
    typedef struct { \
      int used; \
      cchr_id_t hist[RULE_KEPT_##V-1]; \
    } cchr_propent_ ##V## _t; \
    uint32_t static inline cchr_propent_##V##_hash1(cchr_propent_##V##_t *val) { return (uint32_t)hashword(val->hist,(RULE_KEPT_##V-1)*sizeof(cchr_id_t)/4,0x2B7E1516UL); } \
    uint32_t static inline cchr_propent_##V##_hash2(cchr_propent_##V##_t *val) { return (uint32_t)hashword(val->hist,(RULE_KEPT_##V-1)*sizeof(cchr_id_t)/4,0x3243F6A8UL); } \
    int static inline cchr_propent_##V##_eq(cchr_propent_##V##_t *v1,cchr_propent_##V##_t *v2) { \
      for (int i=0; i<RULE_KEPT_##V-1; i++) { \
        if (v1->hist[i] != v2->hist[i]) return 0; \
      } \
      return 1; \
    } \
    ht_cuckoo_code(cchr_propstr_##V##_t, cchr_propent_##V##_t, cchr_propent_##V##_hash1, cchr_propent_##V##_hash2, cchr_propent_##V##_eq,CSM_HTCB_DEFINED,CSM_HTCB_UNDEF,CSM_HTCB_UNDEF) \
  )

#define CSM_CB_IdxDef_S
#define CSM_CB_IdxDef_D(V) HASHLIST_##V(CSM_CB_IdxDefDef,V)

#define CSM_CB_IdxInit_S
#define CSM_CB_IdxInit_D(V) HASHLIST_##V(CSM_CB_IdxInitList,V)

#define CSM_CB_IdxFree_S
#define CSM_CB_IdxFree_D(V) HASHLIST_##V(CSM_CB_IdxFreeList,V)

#define CSM_CB_IdxInitList_S
#define CSM_CB_IdxInitList_D(H,C) cchr_conht_##C##_##H##_t_init(&(_global_runtime.index_##C.H));

#define CSM_CB_IdxFreeList_S
#define CSM_CB_IdxFreeList_D(H,C) cchr_conht_##C##_##H##_t_free(&(_global_runtime.index_##C.H));

#define CSM_CB_HTDD_S
#define CSM_CB_HTDD_D(V) struct { \
  HASHLIST_##V(CSM_CB_HTDL,V) \
} index_##V;

#define CSM_CB_HTDL_S
#define CSM_CB_HTDL_D(H,C) cchr_conht_##C##_##H##_t H;

/* callback macro for history-related data in constraint-specific suspensions */
#define CSM_CB_DTDH_S
#define CSM_CB_DTDH_D(T,V,...) cchr_propstr_##V##_t _ph_##V;

/* callback macro for the arguments of a constraint */
#define CSM_CB_DTDAL_S
#define CSM_CB_DTDAL_D(NAME,TYPE,...) TYPE NAME;

/* callback macro to copy the arguments of a constraint into local vars */
#define CSM_CB_DTDAC_S
#define CSM_CB_DTDAC_D(NAME,TYPE,CON) CSM_CVAR(NAME,CON)=args.data.CON.NAME;

#define CSM_HTCB_DEFINED(VAL) ((VAL)->used)
#define CSM_HTCB_UNDEF(VAL) {(VAL)->used=0;}

#define CSM_CTCB_DEFINED(VAL) (cchr_htdc_t_mem(&(VAL)->val))
#define CSM_CTCB_UNDEF(VAL) {cchr_htdc_t_free(&((VAL)->val));}
#define CSM_CTCB_INIT(VAL) {cchr_htdc_t_init(&((VAL)->val));}

/* callback macro for constraint-specific data in suspensions */ 
#define CSM_CB_DTD_S
#define CSM_CB_DTD_D(NAME) \
  RULEHOOKS_##NAME(CSM_CB_HistTypeDef,) \
  typedef struct { \
    ARGLIST_##NAME(CSM_CB_DTDAL,) \
    CSM_PROP(RULEHOOKS_##NAME(CSM_CB_DTDH,)) \
  } cchr_cons_ ## NAME ## _t; \
  typedef struct { \
    ARGLIST_##NAME(CSM_CB_DTDAL,) \
  } cchr_args_ ## NAME ## _t; \
  typedef struct { \
    ARGLIST_##NAME(CSM_CB_DTDAL,) \
    int doadd,oldgen,oldid; \
  } cchr_cls_## NAME ##_t;
  

#define CSM_CB_DUD_S
#define CSM_CB_DUD_D(NAME) cchr_cons_ ## NAME ## _t NAME;

#define CSM_CB_DUA_S
#define CSM_CB_DUA_D(NAME) cchr_args_ ## NAME ## _t NAME;

#define CSM_HTDC_DEFINED(VAL) ((VAL)->id != 0)
#define CSM_HTDC_UNDEF(VAL) {(VAL)->id = 0;}
#define CSM_HTDC_HASH1(VAL) hashbytes(&((VAL)->id),sizeof(int),0x16A09E66UL)
#define CSM_HTDC_HASH2(VAL) hashbytes(&((VAL)->id),sizeof(int),0x1BB67AE8UL)
#define CSM_HTDC_EQ(V1,V2) ((V1)->id==(V2)->id)

/* main macro */
#define CSM_START \
  enum cchr_cons_type { CONSLIST(CSM_CB_TypeEnum) , CCHR_CONS_COUNT }; \
  CONSLIST(CSM_CB_DTD) \
  CONSLIST(CSM_CB_IdxDef) \
  typedef struct { \
    int gen_num; \
    union { \
      CONSLIST(CSM_CB_DUD) \
    } data; \
  } cchr_entry_t; \
  typedef struct cchr_args_struct_ cchr_args_t; \
  struct cchr_args_struct_ { \
    cchr_id_t con; \
    cchr_id_t pid; \
    union { \
      CONSLIST(CSM_CB_DUA) \
    } data; \
  }; \
  typedef struct { \
    dcls_declare(cchr_entry_t,store); \
    CONSLIST(CSM_CB_HTDD) \
    CSM_DEBUG( int debugindent; ) \
  } cchr_runtime_t; \
  cchr_runtime_t static _global_runtime; \
  void static cchr_runtime_init() { \
    dcls_init(_global_runtime.store,CCHR_CONS_COUNT); \
    CONSLIST(CSM_CB_IdxInit) \
    CSM_DEBUG( _global_runtime.debugindent=0; ) \
  } \
  cchr_id_t static inline cchr_make_entry(enum cchr_cons_type type) { \
    cchr_id_t ret; \
    dcls_alloc(_global_runtime.store,ret); \
    dcls_get(_global_runtime.store,ret).gen_num=0; \
    /* dcls_get(_global_runtime.store,ret).type=type; */ \
    return ret; \
  } \
  void static cchr_reactivate_all(void *); \
  void static inline cchr_store(cchr_id_t pid_self_,enum cchr_cons_type type) { \
    dcls_add_begin(_global_runtime.store,pid_self_,type); \
  } \
  CONSLIST(CSM_CB_FFD) \
  typedef struct { \
    void *rp; \
    size_t back; \
    cchr_id_t pid; \
  } cchr_stackframe_t; \
  void static inline cchr_fire(cchr_args_t args) { \
    cchr_id_t pid_self_=0; \
    char *stack=malloc(128); \
    size_t ss=128,ds=0,sp=0; /* stack size, data size, stack position */ \
    switch (args.con) { \
      CONSLIST(CSM_CB_FFID) \
    } \
    CONSLIST(CSM_CB_FFIC) \
    fire_end: \
    CSM_DEBUG( \
      _global_runtime.debugindent--; \
      CSM_STROUT("end fire"); \
    ) \
    if (sp==0) { \
      free(stack); \
      return; \
    } else { \
      size_t back=((cchr_stackframe_t*)(stack+sp))->back; \
      sp -= back; \
      pid_self_=((cchr_stackframe_t*)(stack+sp))->pid; \
      CSM_FMTOUT("restored stack frame | sp=%i",sp); \
      goto *(((cchr_stackframe_t*)(stack+sp))->rp); \
    } \
  } \
  CONSLIST(CSM_CB_FFC) \
  void static cchr_reactivate_all(void *dummy) { \
  	CONSLIST(CSM_CB_REC) \
  } \
  void static cchr_runtime_free() { \
  	CONSLIST(CSM_CB_FAC) \
	CONSLIST(CSM_CB_IdxFree) \
  	dcls_destruct(_global_runtime.store); \
  }

#define CSM_CB_REC_S
#define CSM_CB_REC_D(NAME) cchr_reactivate_all_##NAME();

#define CSM_CB_FAC_S
#define CSM_CB_FAC_D(NAME) cchr_free_all_##NAME();

/* callback macro for declaration of fire functions */  
#define CSM_CB_FFD_S
#define CSM_CB_FFD_D(NAME) \
  typedef union { \
    RULELIST_##NAME(CSM_CB_FFIDC) \
  } cchr_bls_##NAME##_t; \
  int static inline cchr_fire_##NAME(cchr_args_t*); \
  void static inline cchr_add_##NAME(ARGLIST_##NAME(CSM_CB_FADAR,)); \
  void static inline cchr_reactivate_##NAME(cchr_id_t); \
  void static inline cchr_cont_add_##NAME(cchr_args_t*,ARGLIST_##NAME(CSM_CB_FADAR,)); \
  void static inline cchr_cont_reactivate_##NAME(cchr_args_t*,cchr_id_t); \
  void static inline cchr_index_##NAME(cchr_id_t); \
  void static inline cchr_unindex_##NAME(cchr_id_t);


/* callback macro for arguments of declaration of fire functions */
#define CSM_CB_FFDAR_S
#define CSM_CB_FFDAR_D(NAME,TYPE,...) , TYPE NAME

/* callback macro for arguments of declaration of add functions */
#define CSM_CB_FADAR_S ,
#define CSM_CB_FADAR_D(NAME,TYPE,...) TYPE NAME

/* callback macro for switch to correct inlined fire function */
#define CSM_CB_FFID_S
#define CSM_CB_FFID_D(NAME) case CCHR_CONS_TYPE_##NAME: goto fire_##NAME;

#define CSM_CB_FFVDC_S
#define CSM_CB_FFVDC_D(TYPE,NAME,...) TYPE NAME;

#define CSM_CB_FFIDC_S
#define CSM_CB_FFIDC_D(NAME) \
  struct { \
    NSLIST_##NAME(CSM_CB_FFVDC,) \
  } NAME;

/* callback macro for inline code of fire functions */
#define CSM_CB_FFIC_S
#define CSM_CB_FFIC_D(NAME) \
  fire_##NAME: { \
    size_t ssn=sp+ds+sizeof(cchr_stackframe_t)+sizeof(cchr_bls_##NAME##_t)+sizeof(cchr_cls_##NAME##_t); \
    if (ssn>ss) { \
      ss+=ssn; \
      stack=realloc(stack,ss); \
      CSM_FMTOUT("stack size: need %i, have %i, increased to %i bytes",ssn,ss-ssn,ss); \
    } \
    if (ds) { \
      ((cchr_stackframe_t*)(stack+sp))->pid=pid_self_; \
      sp += ds; \
      ((cchr_stackframe_t*)(stack+sp))->back=ds; \
      CSM_FMTOUT("stack frame added | sp=%i",sp); \
    } \
    ARGLIST_##NAME(CSM_CB_DTDAC,NAME) \
    pid_self_=args.pid; \
    CSM_CVAR(doadd,NAME)=(pid_self_==DCLS_EMPTY_PID); \
    if (CSM_CVAR(doadd,NAME)) { \
      CONSTRUCT_##NAME\
    } \
    CSM_DEBUG( \
      CSM_PRINTF("fire ",NAME); \
      _global_runtime.debugindent++; \
    ) \
    RULELIST_##NAME(CSM_CB_FFCCO) \
    CSM_STROUT("final store") \
    CSM_NEEDSELF(NAME) \
    CSM_END \
  }

/* callback macro for code of fire functions */
#define CSM_CB_FFC_S
#define CSM_CB_FFC_D(NAME) \
  void static inline cchr_cont_add_##NAME(cchr_args_t *args, ARGLIST_##NAME(CSM_CB_FFCAA,)) { \
    args->con=CCHR_CONS_TYPE_##NAME; \
    args->pid=DCLS_EMPTY_PID; \
    ARGLIST_##NAME(CSM_CB_FFCFC,NAME) \
  } \
  void cchr_add_##NAME( ARGLIST_##NAME(CSM_CB_FFCAA,)) { \
    cchr_args_t args; \
    cchr_cont_add_##NAME(&args,ARGLIST_##NAME(CSM_CB_FFPAA,)); \
    cchr_fire(args); \
  } \
  void static inline cchr_cont_reactivate_##NAME(cchr_args_t *args, cchr_id_t pid_self_) { \
    args->con=CCHR_CONS_TYPE_##NAME; \
    args->pid=pid_self_; \
    ARGLIST_##NAME(CSM_CB_FFCRA,NAME); \
  } \
  void cchr_reactivate_##NAME(cchr_id_t pid_self_) { \
    cchr_args_t args; \
    cchr_cont_reactivate_##NAME(&args,pid_self_); \
    CSM_FMTOUT("reactiv: pid=%i",pid_self_); \
    CSM_GENOFPID(pid_self_)++; \
    cchr_fire(args); \
  } \
  void cchr_reactivate_all_##NAME(void) { \
    CSM_DECLOOP(C,CSM_CB_FFVDC,) \
    CSM_LOOP(NAME,C,local, \
      cchr_reactivate_##NAME(CSM_PID(C,local)); \
    ) \
  } \
  void cchr_free_all_##NAME(void) { \
    CSM_DECLOOP(C,CSM_CB_FFVDC,) \
    CSM_LOOP(NAME,C,local, \
      CSM_DESTRUCT_PID(NAME,C,local); \
      CSM_KILL(C,local,NAME); \
    ) \
  } \
  void cchr_index_##NAME(cchr_id_t pid_self_) { \
    HASHLIST_##NAME(CSM_CB_IdxSet,NAME) \
  } \
  void cchr_unindex_##NAME(cchr_id_t pid_self_) { \
    HASHLIST_##NAME(CSM_CB_IdxUnset,NAME) \
  }
  

#define CSM_CB_IdxArgs_S
#define CSM_CB_IdxArgs_D(A,T,C) {_idx.key.A = CSM_PARG(C,pid_self_,A);}

#define CSM_CB_IdxSet_S
#define CSM_CB_IdxSet_D(H,C) { \
  cchr_contbl_##C##_##H##_t _idx,*_idxp; \
  HASHDEF_##C##_##H(CSM_CB_IdxArgs,C) \
  _idxp=cchr_conht_##C##_##H##_t_find(&(_global_runtime.index_##C.H),&_idx); \
  CSM_FMTOUT("idxset %s/%s in %p(%i elem) found=%p(%i elem)",#H,#C,&(_global_runtime.index_##C.H),(_global_runtime.index_##C.H).used,_idxp,_idxp ? cchr_htdc_t_count(&(_idxp->val)) : -1); \
  cchr_idxlist_t pidx={.pid=pid_self_,.id=CSM_IDOFPID(pid_self_)}; \
  if (_idxp) { \
    cchr_htdc_t_set(&(_idxp->val),&pidx); \
  } else { \
    cchr_htdc_t_init(&(_idx.val)); \
    cchr_htdc_t_set(&(_idx.val),&pidx); \
    cchr_conht_##C##_##H##_t_set(&(_global_runtime.index_##C.H),&_idx); \
  } \
}
  
#define CSM_CB_IdxUnset_S
#define CSM_CB_IdxUnset_D(H,C) { \
  cchr_contbl_##C##_##H##_t _idx,*_idxp; \
  HASHDEF_##C##_##H(CSM_CB_IdxArgs,C) \
  _idxp=cchr_conht_##C##_##H##_t_find(&(_global_runtime.index_##C.H),&_idx); \
  CSM_FMTOUT("idxunset %s/%s in %p(%i elem) found=%p(%i elem)",#H,#C,&(_global_runtime.index_##C.H),(_global_runtime.index_##C.H).used,_idxp,_idxp ? cchr_htdc_t_count(&(_idxp->val)) : -1); \
  if (_idxp) { \
    cchr_idxlist_t pidx={.pid=pid_self_,.id=CSM_IDOFPID(pid_self_)}; \
    cchr_htdc_t_unset(&(_idxp->val),&pidx); \
    if (cchr_htdc_t_count(&(_idxp->val))==0) { \
      CSM_STROUT("idxunset: completely removing element"); \
      cchr_conht_##C##_##H##_t_unset(&(_global_runtime.index_##C.H),&_idx); \
    } \
  } \
}

#define CSM_CB_FFCRA_S
#define CSM_CB_FFCRA_D(NAME,TYPE,CON) args->data.CON.NAME=CSM_PARG(CON,pid_self_,NAME);

/* callback macro for arguments of code of fire functions */ 
#define CSM_CB_FFCAR_S
#define CSM_CB_FFCAR_D(NAME,TYPE,...) , TYPE NAME

/* callback macro for inclusion of constraint-occurrence code in fire functions */
#define CSM_CB_FFCCO_S
#define CSM_CB_FFCCO_D(NAME) { CSM_STROUT("try " #NAME); CODELIST_##NAME }

/* callback macro for arguments of code of add functions */
#define CSM_CB_FFCAA_S ,
#define CSM_CB_FFCAA_D(NAME,TYPE,...) TYPE NAME

/* callback macro to pass function arguments */
#define CSM_CB_FFPAA_S ,
#define CSM_CB_FFPAA_D(NAME,TYPE,...) NAME

/* callback macro for arguments passed to fire function in add functions */
#define CSM_CB_FFCFC_S
#define CSM_CB_FFCFC_D(NAME,TYPE,CON) args->data.CON.NAME=NAME;

#define CSM_ARG(CON,NAME) CSM_CVAR(NAME,CON)

#define CSM_IF(EXP,CODE) { \
	if (EXP) { \
		CODE \
	} \
}
#define CSM_DIFFSELF(VAR,NS) (pid_self_ != CSM_PID(VAR,NS))
#define CSM_DIFF(VAR1,VAR2,NS) (CSM_PID(VAR1,NS) != CSM_PID(VAR2,NS))

/* callback macro for freeing propagation history records */ 
#define CSM_CB_FPH_D(T,V,A) { \
	cchr_propstr_##V##_t_free(&(dcls_get(_global_runtime.store,A).data.T._ph_##V)); \
}
#define CSM_CB_FPH_S

/* after a killself should always be a CSM_END */
#define CSM_KILLSELF(TYPE) { \
	if (pid_self_!=DCLS_EMPTY_PID) { \
	    CSM_KILL_(pid_self_,TYPE) \
	} \
}

#define CSM_KILL(VAR,NS,TYPE) CSM_KILL_(CSM_PID(VAR,NS),TYPE)
	
#define CSM_KILL_(PID,TYPE) { \
	CSM_FMTOUT("kill pid=%s(%i) - start",#PID,(int)(PID)); \
	CSM_PROP(RULEHOOKS_##TYPE(CSM_CB_FPH,PID);) \
	cchr_unindex_##TYPE(PID); \
	KILL_##TYPE(PID); \
	dcls_free(_global_runtime.store,PID); \
	CSM_FMTOUT("kill pid=%s(%i) - end",#PID,(int)(PID)); \
}

#define CSM_DESTRUCT_PID(TYPE,PID,NS) DESTRUCT_##TYPE CSM_CB_DPH_F(TYPE,PID,NS)
#define CSM_CB_DPH_F(TYPE,PID,NS) (ARGLIST_##TYPE(CSM_CB_DPH,TYPE,PID,NS))
#define CSM_CB_DPH_S ,
#define CSM_CB_DPH_D(ARG,TYPE,CON,PID,NS) CSM_LARG(CON,PID,NS,ARG)

#define CSM_DESTRUCT_SELF(TYPE) DESTRUCT_##TYPE CSM_CB_DSH_F(TYPE)
#define CSM_CB_DSH_F(TYPE) (ARGLIST_##TYPE(CSM_CB_DSH,TYPE))
#define CSM_CB_DSH_S ,
#define CSM_CB_DSH_D(ARG,TYPE,CON) CSM_ARG(CON,ARG)

#define CSM_DESTRUCT(TYPE,...) DESTRUCT_##TYPE(__VA_ARGS__)
#define CSM_DESTRUCTE(TYPE) DESTRUCT_##TYPE()

#define CSM_DECPID(VAR,CB,...) CB##_D(cchr_id_t,pid_##VAR,__VA_ARGS__)
#define CSM_DECID(VAR,CB,...) CB##_D(cchr_id_t,id_##VAR,__VA_ARGS__)
#define CSM_DECLOOP(VAR,CB,...) dcls_dec_iterx(iter_##VAR,CB,__VA_ARGS__) CB##_S CSM_DECID(VAR,CB,__VA_ARGS__) CB##_S CSM_DECPID(VAR,CB,__VA_ARGS__)

#define CSM_LOOP(TYPE,VAR,NS,CODE) { \
	CSM_FMTOUT("loop over %s in %s:",#TYPE,#VAR); \
	dcls_iterx(_global_runtime.store,CSM_PID(VAR,NS),CSM_VAR(iter_##VAR,NS),CCHR_CONS_TYPE_##TYPE,{ \
	        __label__ csm_loop_##VAR; \
		CSM_ID(VAR,NS)=CSM_IDOFPID(CSM_PID(VAR,NS)); \
		CSM_FMTOUT("inside loop (over %s in %s@%s): pid=%i",#TYPE,#VAR,#NS,CSM_PID(VAR,NS)); \
		{ \
		  CODE \
		} \
	        csm_loop_##VAR: {} \
	}) \
}

#define CSM_LOOPNEXT(VAR,NS) goto csm_loop_##VAR;
// #define CSM_DEFIDXVAR(CON,HASH,VAR,NS) cchr_contbl_##CON##_##HASH##_t idxvar_##VAR;
#define CSM_IDXVAR(CON,HASH,VAR,NS,NAM,ARG) { CSM_VAR(idxvar_##VAR.key.NAM,NS) = (ARG); CSM_FMTOUT("in setIDXVAR: VAR=%s@%s NAM=%s ARG=%i",#VAR,#NS,#NAM,ARG);}

#define CSM_DECIDXLOOP(VAR,CB,CON,HASH,...) CSM_DECID(VAR,CB,__VA_ARGS__) CB##_S CSM_DECPID(VAR,CB,__VA_ARGS__) CB##_S CB##_D(cchr_contbl_##CON##_##HASH##_t *,idx_##VAR,__VA_ARGS__) CB##_S CB##_D(cchr_idxlist_t *,idxlst_##VAR,__VA_ARGS__) CB##_S CB##_D(cchr_contbl_##CON##_##HASH##_t,idxvar_##VAR,__VA_ARGS__)

#define CSM_IDXLOOP(CON,HASH,VAR,NS,CODE) { \
	CSM_VAR(idx_##VAR,NS)=cchr_conht_##CON##_##HASH##_t_find(&(_global_runtime.index_##CON.HASH),&CSM_VAR(idxvar_##VAR,NS)); \
	if (CSM_VAR(idx_##VAR,NS)) { \
	  CSM_FMTOUT("in idxloop (%s.%s var=%s@%s)",#CON,#HASH,#VAR,#NS); \
	  for (CSM_VAR(idxlst_##VAR,NS) = cchr_htdc_t_first(&(CSM_VAR(idx_##VAR,NS)->val)); CSM_VAR(idxlst_##VAR,NS) != NULL; CSM_VAR(idxlst_##VAR,NS)=cchr_htdc_t_next(&(CSM_VAR(idx_##VAR,NS)->val),CSM_VAR(idxlst_##VAR,NS)) ) { \
	    __label__ csm_loop_##VAR; \
	    CSM_PID(VAR,NS) = CSM_VAR(idxlst_##VAR,NS)->pid; \
	    CSM_ID(VAR,NS)=CSM_IDOFPID(CSM_PID(VAR,NS)); \
            { \
	      CODE \
            } \
	    csm_loop_##VAR: {} \
	  } \
	} \
}

#define CSM_DECIDXUNILOOP(VAR,CB,CON,HASH,...) CSM_DECID(VAR,CB,__VA_ARGS__) CB##_S CSM_DECPID(VAR,CB,__VA_ARGS__) CB##_S CB##_D(cchr_contbl_##CON##_##HASH##_t *,idx_##VAR,__VA_ARGS__) CB##_S CB##_D(cchr_idxlist_t *,idxlst_##VAR,__VA_ARGS__) CB##_S CB##_D(cchr_htdc_t,idxcopy_##VAR,__VA_ARGS__) CB##_S CB##_D(cchr_contbl_##CON##_##HASH##_t,idxvar_##VAR,__VA_ARGS__)

#define CSM_IDXUNILOOP(CON,HASH,VAR,NS,CODE) { \
	CSM_VAR(idx_##VAR,NS) = cchr_conht_##CON##_##HASH##_t_find(&(_global_runtime.index_##CON.HASH),&CSM_VAR(idxvar_##VAR,NS)); \
	if (CSM_VAR(idx_##VAR,NS)) { \
	  CSM_FMTOUT("in IDXUNILOOP (%s.%s var=%s@%s)",#CON,#HASH,#VAR,#NS); \
	  cchr_htdc_t_copy(&(CSM_VAR(idx_##VAR,NS)->val),&CSM_VAR(idxcopy_##VAR,NS)); \
	  for (CSM_VAR(idxlst_##VAR,NS) = cchr_htdc_t_first(&CSM_VAR(idxcopy_##VAR,NS)); CSM_VAR(idxlst_##VAR,NS) != NULL; CSM_VAR(idxlst_##VAR,NS)=cchr_htdc_t_next(&CSM_VAR(idxcopy_##VAR,NS),CSM_VAR(idxlst_##VAR,NS)) ) { \
	    __label__ csm_loop_##VAR; \
	    CSM_PID(VAR,NS) = CSM_VAR(idxlst_##VAR,NS)->pid; \
	    CSM_ID(VAR,NS)=CSM_IDOFPID(CSM_PID(VAR,NS)); \
            if (CSM_ALIVEPID(CSM_PID(VAR,NS)) && (CSM_IDOFPID(CSM_PID(VAR,NS))==CSM_VAR(idxlst_##VAR,NS)->id)) { \
	      CODE \
            } \
	    csm_loop_##VAR: {} \
	  } \
          CSM_UNIEND(CON,VAR,NS) \
	} \
}

#define CSM_UNIEND(CON,VAR,NS) {CSM_FMTOUT("UNIEND con=%s var=%s@%s",#CON,#VAR,#NS); cchr_htdc_t_freecopy(&CSM_VAR(idxcopy_##VAR,NS)); }

#define CSM_DECLOGLOOP(VAR,CB,...) CSM_DECID(VAR,CB,__VA_ARGS__) CB##_S CSM_DECPID(VAR,CB,__VA_ARGS__) CB##_S CB##_D(cchr_htdc_t *,log_##VAR,__VA_ARGS__) CB##_S CB##_D(cchr_idxlist_t *,idxlst_##VAR,__VA_ARGS__)

#define CSM_LOGLOOP(CON,VAR,NS,ENT,TYPE,ARG,CODE) { \
  CSM_VAR(log_##VAR,NS)=(&(TYPE##_getextrap(ARG)->ENT)); \
  CSM_FMTOUT("in LOGLOOP (%s;%s var=%s@%s)",#CON,#ENT,#VAR,#NS); \
  for (CSM_VAR(idxlst_##VAR,NS) = cchr_htdc_t_first(CSM_VAR(log_##VAR,NS)); CSM_VAR(idxlst_##VAR,NS) != NULL; CSM_VAR(idxlst_##VAR,NS)=cchr_htdc_t_next(CSM_VAR(log_##VAR,NS),CSM_VAR(idxlst_##VAR,NS)) ) { \
    __label__ csm_loop_##VAR; \
    CSM_PID(VAR,NS)=CSM_VAR(idxlst_##VAR,NS)->pid; \
    CSM_ID(VAR,NS)=CSM_IDOFPID(CSM_PID(VAR,NS)); \
    { \
      CSM_FMTOUT("in LOGLOOP (%s;%s var=%s@%s): pid=%i id=%i",#CON,#ENT,#VAR,#NS,CSM_PID(VAR,NS),CSM_IDOFPID(CSM_PID(VAR,NS))); \
      CODE \
    } \
    csm_loop_##VAR: {} \
  } \
}

#define CSM_DECLOGUNILOOP(VAR,CB,...) CSM_DECID(VAR,CB,__VA_ARGS__) CB##_S CSM_DECPID(VAR,CB,__VA_ARGS__) CB##_S CB##_D(cchr_htdc_t *,log_##VAR,__VA_ARGS__) CB##_S CB##_D(cchr_idxlist_t *,idxlst_##VAR,__VA_ARGS__) CB##_S CB##_D(cchr_htdc_t,idxcopy_##VAR,__VA_ARGS__)

#define CSM_LOGUNILOOP(CON,VAR,NS,ENT,TYPE,ARG,CODE) { \
  CSM_VAR(log_##VAR,NS)=(&(TYPE##_getextrap(ARG)->ENT)); \
  CSM_FMTOUT("in LOGUNILOOP (%s;%s var=%s@%s)",#CON,#ENT,#VAR,#NS); \
  cchr_htdc_t_copy(CSM_VAR(log_##VAR,NS),&CSM_VAR(idxcopy_##VAR,NS)); \
  for (CSM_VAR(idxlst_##VAR,NS) = cchr_htdc_t_first(&CSM_VAR(idxcopy_##VAR,NS)); CSM_VAR(idxlst_##VAR,NS) != NULL; CSM_VAR(idxlst_##VAR,NS)=cchr_htdc_t_next(&CSM_VAR(idxcopy_##VAR,NS),CSM_VAR(idxlst_##VAR,NS)) ) { \
    __label__ csm_loop_##VAR; \
    CSM_PID(VAR,NS)=CSM_VAR(idxlst_##VAR,NS)->pid; \
    CSM_ID(VAR,NS)=CSM_IDOFPID(CSM_PID(VAR,NS)); \
    if (CSM_ALIVEPID(CSM_PID(VAR,NS)) && (CSM_IDOFPID(CSM_PID(VAR,NS))==CSM_VAR(idxlst_##VAR,NS)->id)) { \
      CSM_FMTOUT("in LOGUNILOOP (%s;%s var=%s@%s): pid=%i id=%i",#CON,#ENT,#VAR,#NS,CSM_PID(VAR,NS),CSM_IDOFPID(CSM_PID(VAR,NS))); \
      CODE \
    } \
    csm_loop_##VAR: {} \
  } \
  CSM_UNIEND(CON,VAR,NS) \
}

#define CSM_END { \
	goto fire_end; \
}

#define CSM_PARG(TYPE,PID,NAME) (dcls_get(_global_runtime.store,PID).data.TYPE.NAME)
#define CSM_LARG(TYPE,VAR,NS,NAME) CSM_PARG(TYPE,CSM_PID(VAR,NS),NAME)

#define CSM_MAKE(TYPE) { \
	if (CSM_CVAR(doadd,TYPE) && pid_self_==DCLS_EMPTY_PID) { \
		pid_self_=cchr_make_entry(CCHR_CONS_TYPE_##TYPE); \
		ARGLIST_##TYPE(CSM_CB_MAKSA,TYPE); \
		RULEHOOKS_##TYPE(CSM_CB_PHI,); \
		CSM_PRINTF("make ",TYPE); \
	} \
	CSM_CVAR(oldid,TYPE)=CSM_IDOFPID(pid_self_); \
	CSM_CVAR(oldgen,TYPE)=CSM_GENOFPID(pid_self_); \
}

/* callback macro for constraint suspension argument setting */ 
#define CSM_CB_MAKSA_S 
#define CSM_CB_MAKSA_D(NAME,TYPE,CON) dcls_get(_global_runtime.store,pid_self_).data.CON.NAME = CSM_ARG(CON,NAME) ;

#define CSM_CB_PHI_D(T,V,A) CSM_PROP( \
	cchr_propstr_##V##_t_init(&(dcls_get(_global_runtime.store,pid_self_).data.T._ph_##V)); \
)
#define CSM_CB_PHI_S

#define CSM_IDOFPID(PID) (dcls_id(_global_runtime.store,PID))
#define CSM_GENOFPID(PID) (dcls_get(_global_runtime.store,PID).gen_num)
#define CSM_ALIVEPID(PID) (dcls_used(_global_runtime.store,PID))

#define CSM_DEADSELF(TYPE,CODE) CSM_IF((!CSM_ALIVEPID(pid_self_) || CSM_IDOFPID(pid_self_)!=CSM_CVAR(oldid,TYPE) || CSM_GENOFPID(pid_self_)!=CSM_CVAR(oldgen,TYPE)),CODE)
#define CSM_DEAD(PID,NS,CODE) CSM_IF((!CSM_ALIVEPID(CSM_PID(PID,NS)) || CSM_IDOFPID(CSM_PID(PID,NS))!=CSM_ID(PID,NS)),CODE)

#define CSM_TAILFIRE(CON) { \
  ds=0; \
  CSM_FMTOUT("tail fire %s | sp=%i ds=0",#CON,sp) \
  CSM_DEBUG( \
    _global_runtime.debugindent--; \
  ) \
  goto fire_##CON; \
}

/*#define CSM_TAILFIRE CSM_FIRE*/

#define CSM_FIRE(CON) { \
  __label__ rp; \
  ((cchr_stackframe_t*)(stack+sp))->rp=(&&rp); \
  ds = sizeof(cchr_stackframe_t)+sizeof(cchr_bls_##CON##_t)+sizeof(cchr_cls_##CON##_t); \
  CSM_FMTOUT("goto fire %s | sp=%i ds=%i",#CON,sp,ds) \
  goto fire_##CON; \
  rp: {} \
  CSM_FMTOUT("resume from fire %s | sp=%i",#CON,sp) \
}

#define CSM_ADD(CON,...) { \
  cchr_cont_add_##CON(&args,__VA_ARGS__); \
  CSM_FIRE(CON) \
}
	
#define CSM_ADDE(CON) { \
  cchr_cont_add_##CON(&args); \
  CSM_FIRE(CON); \
}

#define CSM_TADD(CON,...) { \
  cchr_cont_add_##CON(&args,__VA_ARGS__); \
  CSM_TAILFIRE(CON); \
  CSM_END; \
}
#define CSM_TADDE(CON) { \
  cchr_cont_add_##CON(&args); \
  CSM_TAILFIRE(CON); \
  CSM_END; \
}
#define CSM_NEEDSELF(CON) { \
	if (CSM_CVAR(doadd,CON)) { \
		CSM_MAKE(CON) \
		CSM_FMTOUT("store pid=%i - begin",(int)pid_self_); \
		cchr_store(pid_self_,CCHR_CONS_TYPE_##CON); \
		cchr_index_##CON(pid_self_); \
		ADD_##CON(pid_self_); \
		CSM_CVAR(doadd,CON)=0; \
		CSM_FMTOUT("store pid=%i - end",(int)pid_self_); \
	} \
}

#define NSPACE_local(VAR) CSM_SPACE_LOCAL(VAR)

#define CSM_SPACE_FIRE(NS,CON,VAR) ((cchr_bls_##CON##_t*)(stack+sp+sizeof(cchr_stackframe_t)+sizeof(cchr_cls_##CON##_t)))->NS.VAR
#define CSM_SPACE_LOCAL(VAR) VAR

#define CSM_CVAR(VAR,CON) ((cchr_cls_##CON##_t*)(stack+sp+sizeof(cchr_stackframe_t)))->VAR
#define CSM_VAR(VAR,NS) NSPACE_##NS(VAR)
#define CSM_LOCAL(VAR,NS) (CSM_VAR(local_##VAR,NS))
#define CSM_DEFLOCAL(VAR,NS,EXPR) {CSM_LOCAL(VAR,NS)=(EXPR);}
#define CSM_DECLOCAL(TYPE,VAR,CB,...) CB##_D(TYPE,local_##VAR,__VA_ARGS__)


#define CSM_MESSAGE(...) { \
	fprintf(stderr,__VA_ARGS__); \
}
#define CSM_NATIVE(...) { \
	 __VA_ARGS__ \
}

#define CSM_PID_SELF(NS) pid_self_
#define CSM_PID(VAR,NS) CSM_VAR(pid_##VAR,NS)
#define CSM_ID(VAR,NS) CSM_VAR(id_##VAR,NS)

#define CSM_HISTCHECK(RULE,CODE,...) CSM_PROP(PROPHIST_##RULE(CSM_CB_HC,__VA_ARGS__,RULE,CODE)) CSM_NOPROP({CODE})
#define CSM_CB_HC_I(HOOK,RULE,CODE,COND) { \
	int ok_=1; \
	cchr_entry_t *p_=dcls_ptr(_global_runtime.store,HOOK); \
	cchr_propent_##RULE##_t ent_={.used=1}; \
	COND; \
	if (cchr_propstr_##RULE##_t_have(&(p_->data.PROPHIST_HOOK_##RULE._ph_##RULE),&ent_)) { \
		CSM_FMTOUT("histfail %s (on %s:%i)",#RULE,#HOOK,CSM_IDOFPID(HOOK)); \
		ok_=0; \
	} else {\
		CODE \
	} \
}
#define CSM_CB_HC_D(PID,HOOK,POS,RULE,CODE) ent_.hist[(POS)]=CSM_IDOFPID(PID);
#define CSM_CB_HC_S(RULE,CODE)

#define CSM_HISTADD(RULE,...) CSM_PROP(PROPHIST_##RULE(CSM_CB_HA,__VA_ARGS__,RULE))
#define CSM_CB_HA_I(HOOK,RULE,COND) { \
	cchr_entry_t *p_=dcls_ptr(_global_runtime.store,HOOK); \
	CSM_FMTOUT("histadd pre: [pid=%i cnt=%i id=%i]",HOOK,p_->data.PROPHIST_HOOK_##RULE._ph_##RULE.used,CSM_IDOFPID(HOOK)); \
	cchr_propent_##RULE##_t ent_={.used=1}; \
	CSM_FMTOUTX("histadd %s (",0,#RULE); \
	COND; \
	CSM_FMTOUTX(") to %s:%i [pid=%i cnt=%i]",2,#HOOK,CSM_IDOFPID(HOOK),HOOK,p_->data.PROPHIST_HOOK_##RULE._ph_##RULE.used); \
	cchr_propstr_##RULE##_t_set(&(p_->data.PROPHIST_HOOK_##RULE._ph_##RULE),&ent_); \
}
#define CSM_CB_HA_D(PID,HOOK,POS,RULE) ent_.hist[(POS)]=CSM_IDOFPID(PID); CSM_DEBUG(if (POS>0) CSM_STROUTX(",",1); CSM_FMTOUTX("%s:%i",1,#PID,CSM_IDOFPID(PID)); );
#define CSM_CB_HA_S(RULE)

/***** additional helper macro's *****/

#define cchr_consloop(var,type,code) dcls_iter(_global_runtime.store,var,CCHR_CONS_TYPE_##type,{cchr_cons_##type##_t * _##var##_data= (&(dcls_ptr(_global_runtime.store,j)->data.type)); {code}})
#define cchr_consarg(var,type,num) (_##var##_data->arg##num)


#define alt(expr,...) (expr)
#define eq(v1,v2) ((sizeof((v1)) == sizeof((v2))) && !memcmp(&(v1),&(v2),sizeof((v1))))

/****** real declarations *****/

typedef struct {
  int id;
  cchr_id_t pid;
} cchr_idxlist_t;

ht_cuckoo_code(cchr_htdc_t,cchr_idxlist_t,CSM_HTDC_HASH1,CSM_HTDC_HASH2,CSM_HTDC_EQ,CSM_HTDC_DEFINED,CSM_HTDC_UNDEF,CSM_HTDC_UNDEF)

#endif

