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
#include "lookup3.h" /* for hashing algorithm */
#include "lookup3.c"
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
		fprintf(stderr,"%s%s: " FORMAT_##TYPE " | pid=%i id=%i\n",INIT,#TYPE FORMATARGS_##TYPE,(int)pid_self_,pid_self_!= DCLS_EMPTY_PID ? CSM_IDOFPID(self_) : -1); \
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
  } cchr_cons_ ## NAME ## _t;

#define CSM_CB_DUD_S
#define CSM_CB_DUD_D(NAME) cchr_cons_ ## NAME ## _t NAME;

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
    /* enum cchr_cons_type type; */ \
    int gen_num; \
    union { \
      CONSLIST(CSM_CB_DUD) \
    } data; \
  } cchr_entry_t; \
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
  CONSLIST(CSM_CB_FFC) \
  void static cchr_reactivate_all(void *dummy) { \
  	CONSLIST(CSM_CB_REC) \
  } \
  void static cchr_runtime_free() { \
  	CONSLIST(CSM_CB_FAC) \
	char bla1[]="between part 1 and 2"; \
	CONSLIST(CSM_CB_IdxFree) \
	char bla2[]="between part 2 and 3"; \
  	dcls_destruct(_global_runtime.store); \
  }

#define CSM_CB_REC_S
#define CSM_CB_REC_D(NAME) cchr_reactivate_all_##NAME();

#define CSM_CB_FAC_S
#define CSM_CB_FAC_D(NAME) cchr_free_all_##NAME();

/* callback macro for declaration of fire functions */  
#define CSM_CB_FFD_S
#define CSM_CB_FFD_D(NAME) \
  void static inline cchr_fire_##NAME(cchr_id_t  ARGLIST_##NAME(CSM_CB_FFDAR,)); \
  void static inline cchr_add_##NAME(ARGLIST_##NAME(CSM_CB_FADAR,)); \
  void static inline cchr_reactivate_##NAME(cchr_id_t); \
  void static inline cchr_index_##NAME(cchr_id_t); \
  void static inline cchr_unindex_##NAME(cchr_id_t);


/* callback macro for arguments of declaration of fire functions */
#define CSM_CB_FFDAR_S
#define CSM_CB_FFDAR_D(NAME,TYPE,...) , TYPE NAME

/* callback macro for arguments of declaration of add functions */
#define CSM_CB_FADAR_S ,
#define CSM_CB_FADAR_D(NAME,TYPE,...) TYPE NAME

/* callback macro for code of fire functions */
#define CSM_CB_FFC_S
#define CSM_CB_FFC_D(NAME) \
  void static inline cchr_fire_##NAME(cchr_id_t pid_self_ ARGLIST_##NAME(CSM_CB_FFCAR,)) { \
    int doadd=(pid_self_==DCLS_EMPTY_PID); \
    int oldid; \
    int oldgen; \
    if (doadd) { \
      CONSTRUCT_##NAME; \
    } \
    CSM_DEBUG( \
      CSM_PRINTF("fire ",NAME); \
      _global_runtime.debugindent++; \
    ) \
    RULELIST_##NAME(CSM_CB_FFCCO) \
    CSM_STROUT("final store") \
    CSM_NEEDSELF(NAME) \
    CSM_END \
  } \
  void cchr_add_##NAME( ARGLIST_##NAME(CSM_CB_FFCAA,)) { \
    cchr_fire_##NAME(DCLS_EMPTY_PID ARGLIST_##NAME(CSM_CB_FFCFC,)); \
  } \
  void cchr_reactivate_##NAME(cchr_id_t pid_self_) { \
    CSM_FMTOUT("reactiv: pid=%i",pid_self_); \
    CSM_GENOFPID(self_)++; \
    cchr_fire_##NAME(pid_self_ ARGLIST_##NAME(CSM_CB_FFCRA,NAME)); \
  } \
  void cchr_reactivate_all_##NAME(void) { \
  	CSM_LOOP(NAME,C, \
  	  cchr_reactivate_##NAME(pid_C); \
  	) \
  } \
  void cchr_free_all_##NAME(void) { \
  	CSM_LOOP(NAME,C, \
	  CSM_DESTRUCT_PID(NAME,C); \
  	  CSM_KILL(C,NAME); \
  	) \
  } \
  void cchr_index_##NAME(cchr_id_t pid_self_) { \
    HASHLIST_##NAME(CSM_CB_IdxSet,NAME) \
  } \
  void cchr_unindex_##NAME(cchr_id_t pid_self_) { \
    HASHLIST_##NAME(CSM_CB_IdxUnset,NAME) \
  }
  

#define CSM_CB_IdxArgs_S
#define CSM_CB_IdxArgs_D(A,T,C) {_idx.key.A = CSM_LARG(C,self_,A);}

#define CSM_CB_IdxSet_S
#define CSM_CB_IdxSet_D(H,C) { \
  cchr_contbl_##C##_##H##_t _idx,*_idxp; \
  HASHDEF_##C##_##H(CSM_CB_IdxArgs,C) \
  _idxp=cchr_conht_##C##_##H##_t_find(&(_global_runtime.index_##C.H),&_idx); \
  CSM_FMTOUT("idxset %s/%s in %p(%i elem) found=%p(%i elem)",#H,#C,&(_global_runtime.index_##C.H),(_global_runtime.index_##C.H).used,_idxp,_idxp ? cchr_htdc_t_count(&(_idxp->val)) : -1); \
  cchr_idxlist_t pidx={.pid=pid_self_,.id=CSM_IDOFPID(self_)}; \
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
    cchr_idxlist_t pidx={.pid=pid_self_,.id=CSM_IDOFPID(self_)}; \
    cchr_htdc_t_unset(&(_idxp->val),&pidx); \
    if (cchr_htdc_t_count(&(_idxp->val))==0) { \
      CSM_STROUT("idxunset: completely removing element"); \
      cchr_conht_##C##_##H##_t_unset(&(_global_runtime.index_##C.H),&_idx); \
    } \
  } \
}

#define CSM_CB_FFCRA_S
#define CSM_CB_FFCRA_D(NAME,TYPE,CON) ,CSM_LARG(CON,self_,NAME)

/* callback macro for arguments of code of fire functions */ 
#define CSM_CB_FFCAR_S
#define CSM_CB_FFCAR_D(NAME,TYPE,...) , TYPE NAME

/* callback macro for inclusion of constraint-occurrence code in fire functions */
#define CSM_CB_FFCCO_S
#define CSM_CB_FFCCO_D(NAME) { CSM_STROUT("try " #NAME); CODELIST_##NAME }

/* callback macro for arguments of code of add functions */
#define CSM_CB_FFCAA_S ,
#define CSM_CB_FFCAA_D(NAME,TYPE,...) TYPE NAME

/* callback macro for arguments passed to fire function in add functions */
#define CSM_CB_FFCFC_S
#define CSM_CB_FFCFC_D(NAME,TYPE,...) , NAME


#define CSM_ARG(TYPE,NAME) (NAME)

#define CSM_IF(EXP,CODE) { \
	if (EXP) { \
		CODE \
	} \
}
#define CSM_DIFFSELF(VAR) (pid_self_ != pid_##VAR)
#define CSM_DIFF(VAR1,VAR2) (pid_##VAR1 != pid_##VAR2)

/* callback macro for freeing propagation history records */ 
#define CSM_CB_FPH_D(T,V,A) { \
	cchr_propstr_##V##_t_free(&(dcls_get(_global_runtime.store,pid_##A).data.T._ph_##V)); \
}
#define CSM_CB_FPH_S

/* after a killself should always be a CSM_END */
#define CSM_KILLSELF(TYPE) { \
	if (pid_self_!=DCLS_EMPTY_PID) { \
	    CSM_KILL(self_,TYPE) \
	} \
}

#define CSM_KILL(VAR,TYPE) { \
	CSM_FMTOUT("kill pid=%s(%i) - start",#VAR,(int)pid_##VAR); \
	CSM_PROP(RULEHOOKS_##TYPE(CSM_CB_FPH,VAR);) \
	cchr_unindex_##TYPE(pid_##VAR); \
	KILL_##TYPE(VAR); \
	dcls_free(_global_runtime.store,pid_##VAR); \
	CSM_FMTOUT("kill pid=%s(%i) - end",#VAR,(int)pid_##VAR); \
}

#define CSM_DESTRUCT_PID(TYPE,PID) DESTRUCT_##TYPE CSM_CB_DPH_F(TYPE,PID)
#define CSM_CB_DPH_F(TYPE,PID) (ARGLIST_##TYPE(CSM_CB_DPH,TYPE,PID))
#define CSM_CB_DPH_S ,
#define CSM_CB_DPH_D(ARG,TYPE,CON,PID) CSM_LARG(CON,PID,ARG)

#define CSM_DESTRUCT_SELF(TYPE) DESTRUCT_##TYPE CSM_CB_DSH_F(TYPE)
#define CSM_CB_DSH_F(TYPE) (ARGLIST_##TYPE(CSM_CB_DSH,TYPE))
#define CSM_CB_DSH_S ,
#define CSM_CB_DSH_D(ARG,TYPE,CON) CSM_ARG(CON,ARG)

#define CSM_DESTRUCT(TYPE,...) DESTRUCT_##TYPE(__VA_ARGS__)
#define CSM_DESTRUCTE(TYPE) DESTRUCT_##TYPE()

#define CSM_LOOP(TYPE,VAR,CODE) { \
	CSM_FMTOUT("loop over %s in %s:",#TYPE,#VAR); \
	dcls_iter(_global_runtime.store,pid_##VAR,CCHR_CONS_TYPE_##TYPE,{ \
	        __label__ csm_loop_##VAR; \
		cchr_id_t id_##VAR=CSM_IDOFPID(VAR); \
		CSM_FMTOUT("inside loop (over %s in %s): pid=%i",#TYPE,#VAR,pid_##VAR); \
		{ \
		  CODE \
		} \
	        csm_loop_##VAR: {} \
	}) \
}

#define CSM_LOOPNEXT(VAR) goto csm_loop_##VAR;
#define CSM_DEFIDXVAR(CON,HASH,VAR) cchr_contbl_##CON##_##HASH##_t _idxvar_##VAR;
#define CSM_SETIDXVAR(CON,HASH,VAR,NAM,ARG) { _idxvar_##VAR.key.NAM = (ARG); CSM_FMTOUT("in setIDXVAR: VAR=%s NAM=%s ARG=%i",#VAR,#NAM,ARG);}

#define CSM_IDXLOOP(CON,HASH,VAR,CODE) { \
	cchr_contbl_##CON##_##HASH##_t *_idx_##VAR = cchr_conht_##CON##_##HASH##_t_find(&(_global_runtime.index_##CON.HASH),&_idxvar_##VAR); \
	if (_idx_##VAR) { \
	  CSM_FMTOUT("in idxloop (%s.%s var=%s)",#CON,#HASH,#VAR); \
	  for (cchr_idxlist_t *_idxlst_##VAR = cchr_htdc_t_first(&(_idx_##VAR->val)); _idxlst_##VAR != NULL; _idxlst_##VAR=cchr_htdc_t_next(&(_idx_##VAR->val),_idxlst_##VAR) ) { \
	    __label__ csm_loop_##VAR; \
            cchr_id_t pid_##VAR = _idxlst_##VAR->pid; \
	    cchr_id_t id_##VAR=CSM_IDOFPID(VAR); \
            { \
	      CODE \
            } \
	    csm_loop_##VAR: {} \
	  } \
	} \
}

#define CSM_IDXUNILOOP(CON,HASH,VAR,CODE) { \
	cchr_contbl_##CON##_##HASH##_t *_idx_##VAR = cchr_conht_##CON##_##HASH##_t_find(&(_global_runtime.index_##CON.HASH),&_idxvar_##VAR); \
	if (_idx_##VAR) { \
	  CSM_FMTOUT("in IDXUNILOOP (%s.%s var=%s)",#CON,#HASH,#VAR); \
	  cchr_htdc_t _idxcopy_##VAR; \
	  cchr_htdc_t_copy(&(_idx_##VAR->val),&_idxcopy_##VAR); \
	  for (cchr_idxlist_t *_idxlst_##VAR = cchr_htdc_t_first(&_idxcopy_##VAR); _idxlst_##VAR != NULL; _idxlst_##VAR=cchr_htdc_t_next(&_idxcopy_##VAR,_idxlst_##VAR) ) { \
	    __label__ csm_loop_##VAR; \
            cchr_id_t pid_##VAR = _idxlst_##VAR->pid; \
	    cchr_id_t id_##VAR=CSM_IDOFPID(VAR); \
            if (CSM_ALIVEPID(VAR) && (CSM_IDOFPID(VAR)==_idxlst_##VAR->id)) { \
	      CODE \
            } \
	    csm_loop_##VAR: {} \
	  } \
          CSM_UNIEND(CON,VAR) \
	} \
}

#define CSM_UNIEND(CON,VAR) {CSM_FMTOUT("UNIEND con=%s var=%s",#CON,#VAR); cchr_htdc_t_freecopy(&_idxcopy_##VAR); }

#define CSM_LOGLOOP(CON,VAR,ENT,TYPE,ARG,CODE) { \
  cchr_htdc_t *_log_##VAR=&(TYPE##_getextrap(ARG)->ENT); \
  CSM_FMTOUT("in LOGLOOP (%s;%s var=%s)",#CON,#ENT,#VAR); \
  for (cchr_idxlist_t *_idxlst_##VAR = cchr_htdc_t_first(_log_##VAR); _idxlst_##VAR != NULL; _idxlst_##VAR=cchr_htdc_t_next(_log_##VAR,_idxlst_##VAR) ) { \
    __label__ csm_loop_##VAR; \
    cchr_id_t pid_##VAR = _idxlst_##VAR->pid; \
    cchr_id_t id_##VAR=CSM_IDOFPID(VAR); \
    { \
      CSM_FMTOUT("in LOGLOOP (%s;%s var=%s): pid=%i id=%i",#CON,#ENT,#VAR,pid_##VAR,CSM_IDOFPID(VAR)); \
      CODE \
    } \
    csm_loop_##VAR: {} \
  } \
}

#define CSM_LOGUNILOOP(CON,VAR,ENT,TYPE,ARG,CODE) { \
  cchr_htdc_t *_log_##VAR=&(TYPE##_getextrap(ARG)->ENT); \
  CSM_FMTOUT("in LOGUNILOOP (%s;%s var=%s)",#CON,#ENT,#VAR); \
  cchr_htdc_t _idxcopy_##VAR; \
  cchr_htdc_t_copy(_log_##VAR,&_idxcopy_##VAR); \
  for (cchr_idxlist_t *_idxlst_##VAR = cchr_htdc_t_first(&_idxcopy_##VAR); _idxlst_##VAR != NULL; _idxlst_##VAR=cchr_htdc_t_next(&_idxcopy_##VAR,_idxlst_##VAR) ) { \
    __label__ csm_loop_##VAR; \
    cchr_id_t pid_##VAR = _idxlst_##VAR->pid; \
    cchr_id_t id_##VAR=CSM_IDOFPID(VAR); \
    if (CSM_ALIVEPID(VAR) && (CSM_IDOFPID(VAR)==_idxlst_##VAR->id)) { \
      CSM_FMTOUT("in LOGUNILOOP (%s;%s var=%s): pid=%i id=%i",#CON,#ENT,#VAR,pid_##VAR,CSM_IDOFPID(VAR)); \
      CODE \
    } \
    csm_loop_##VAR: {} \
  } \
  CSM_UNIEND(CON,VAR) \
}

#define CSM_END { \
	CSM_DEBUG( \
		_global_runtime.debugindent--; \
		CSM_STROUT("end fire"); \
	) \
	return; \
}
#define CSM_LARG(TYPE,VAR,NAME) (dcls_get(_global_runtime.store,pid_##VAR).data.TYPE.NAME)
#define CSM_MAKE(TYPE) { \
	if (doadd && pid_self_==DCLS_EMPTY_PID) { \
		pid_self_=cchr_make_entry(CCHR_CONS_TYPE_##TYPE); \
		ARGLIST_##TYPE(CSM_CB_MAKSA,TYPE); \
		RULEHOOKS_##TYPE(CSM_CB_PHI,); \
		CSM_PRINTF("make ",TYPE); \
	} \
	oldid=CSM_IDOFPID(self_); \
	oldgen=CSM_GENOFPID(self_); \
}

/* callback macro for constraint suspension argument setting */ 
#define CSM_CB_MAKSA_S 
#define CSM_CB_MAKSA_D(NAME,TYPE,CON) dcls_get(_global_runtime.store,pid_self_).data.CON.NAME = NAME ;

#define CSM_CB_PHI_D(T,V,A) CSM_PROP( \
	cchr_propstr_##V##_t_init(&(dcls_get(_global_runtime.store,pid_self_).data.T._ph_##V)); \
)
#define CSM_CB_PHI_S

#define CSM_IDOFPID(PID) (dcls_id(_global_runtime.store,pid_##PID))
#define CSM_GENOFPID(PID) (dcls_get(_global_runtime.store,pid_##PID).gen_num)
#define CSM_ALIVEPID(PID) (dcls_used(_global_runtime.store,pid_##PID))

#define CSM_DEADSELF(CODE) CSM_IF((!CSM_ALIVEPID(self_) || CSM_IDOFPID(self_)!=oldid || CSM_GENOFPID(self_)!=oldgen),CODE)
#define CSM_DEAD(PID,CODE) CSM_IF((!CSM_ALIVEPID(PID) || CSM_IDOFPID(PID)!=id_##PID),CODE)

#define CSM_ADD(CON,...) { \
	cchr_fire_##CON(DCLS_EMPTY_PID,__VA_ARGS__); \
}
#define CSM_ADDE(CON) { \
	cchr_fire_##CON(DCLS_EMPTY_PID); \
}
#define CSM_TADD(CON,...) { \
	CSM_ADD(CON,__VA_ARGS__); \
	CSM_END \
}
#define CSM_TADDE(CON,...) { \
	CSM_ADDE(CON); \
	CSM_END \
}
#define CSM_NEEDSELF(CON) { \
	if (doadd) { \
		CSM_MAKE(CON) \
		CSM_FMTOUT("store pid=%i - begin",(int)pid_self_); \
		cchr_store(pid_self_,CCHR_CONS_TYPE_##CON); \
		cchr_index_##CON(pid_self_); \
		ADD_##CON(self_); \
		doadd=0; \
		CSM_FMTOUT("store pid=%i - end",(int)pid_self_); \
	} \
}
#define CSM_DEFLOCAL(TYPE,VAR,EXPR) TYPE local_##VAR = EXPR;
#define CSM_DECLOCAL(TYPE,VAR) TYPE local_##VAR;
#define CSM_IMMLOCAL(TYPE,VAR,EXPR) CSM_DEFLOCAL(TYPE const,VAR,EXPR)
#define CSM_LOCAL(VAR) (local_##VAR)


#define CSM_MESSAGE(...) { \
	fprintf(stderr,__VA_ARGS__); \
}
#define CSM_NATIVE(...) { \
	 __VA_ARGS__ \
}

#define CSM_PID(PID) (pid_##PID)

#define CSM_HISTCHECK(RULE,CODE,...) CSM_PROP(PROPHIST_##RULE(CSM_CB_HC,__VA_ARGS__,RULE,CODE)) CSM_NOPROP({CODE})
#define CSM_CB_HC_I(HOOK,RULE,CODE,COND) { \
	int ok_=1; \
	cchr_entry_t *p_=dcls_ptr(_global_runtime.store,pid_##HOOK); \
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
	cchr_entry_t *p_=dcls_ptr(_global_runtime.store,pid_##HOOK); \
	CSM_FMTOUT("histadd pre: [pid=%i cnt=%i id=%i]",pid_##HOOK,p_->data.PROPHIST_HOOK_##RULE._ph_##RULE.used,CSM_IDOFPID(HOOK)); \
	cchr_propent_##RULE##_t ent_={.used=1}; \
	CSM_FMTOUTX("histadd %s (",0,#RULE); \
	COND; \
	CSM_FMTOUTX(") to %s:%i [pid=%i cnt=%i]",2,#HOOK,CSM_IDOFPID(HOOK),pid_##HOOK,p_->data.PROPHIST_HOOK_##RULE._ph_##RULE.used); \
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

