/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| cchr_csm.h - header file included by compiler output                       |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef _cchr_csm_h_
#define _cchr_csm_h_

#include <stdlib.h>

/* we need dcls */
#include "dcls.h"
/* and alist.h */
#include "alist.h"

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
		fprintf(stderr,"%s%s: " FORMAT_##TYPE " pid=%i id=%i\n",INIT,#TYPE ARGLIST_##TYPE(CSM_CB_FFCFC,),(int)pid_self_,pid_self_!= DCLS_EMPTY_PID ? dcls_get(_global_runtime.store,pid_self_).id : -1); \
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

#define CSM_CB_ENU_S ,
#define CSM_CB_ENU_D(NAME) CCHR_CONS_TYPE_ ## NAME

/* callback macro for history-related data in constraint-specific suspensions */
#define CSM_CB_DTDH_S
#define CSM_CB_DTDH_D(T,V,...) int _phl_##V; alist_declare(int,_ph_##V);

/* callback macro for the arguments of a constraint */
#define CSM_CB_DTDAL_S
#define CSM_CB_DTDAL_D(NAME,TYPE,...) TYPE NAME;

/* callback macro for constraint-specific data in suspensions */ 
#define CSM_CB_DTD_S
#define CSM_CB_DTD_D(NAME) \
  typedef struct { \
    ARGLIST_##NAME(CSM_CB_DTDAL,) \
    CSM_PROP(RULEHOOKS_##NAME(CSM_CB_DTDH,)) \
  } cchr_cons_ ## NAME ## _t;

#define CSM_CB_DUD_S
#define CSM_CB_DUD_D(NAME) cchr_cons_ ## NAME ## _t NAME;

/* main macro */
#define CSM_START \
  enum cchr_cons_type { CONSLIST(CSM_CB_ENU) , CCHR_CONS_COUNT }; \
  CONSLIST(CSM_CB_DTD) \
  typedef struct { \
    enum cchr_cons_type type; \
    int id; \
    int gen_num; \
    union { \
      CONSLIST(CSM_CB_DUD) \
    } data; \
  } cchr_entry_t; \
  typedef struct { \
    dcls_declare(cchr_entry_t,store); \
    int nextid; \
    CSM_DEBUG( int debugindent; ) \
  } cchr_runtime_t; \
  cchr_runtime_t static _global_runtime; \
  void static cchr_runtime_init() { \
    dcls_init(_global_runtime.store,CCHR_CONS_COUNT); \
    _global_runtime.nextid=1; \
    CSM_DEBUG( _global_runtime.debugindent=0; ) \
  } \
  dcls_pid_t static inline cchr_make_entry(enum cchr_cons_type type) { \
    dcls_pid_t ret; \
    dcls_alloc(_global_runtime.store,ret); \
    dcls_get(_global_runtime.store,ret).id=_global_runtime.nextid++; \
    dcls_get(_global_runtime.store,ret).gen_num=0; \
    dcls_get(_global_runtime.store,ret).type=type; \
    return ret; \
  } \
  void static cchr_reactivate_all(void *); \
  void static inline cchr_store(dcls_pid_t pid_self_) { \
    dcls_add_begin(_global_runtime.store,pid_self_,dcls_get(_global_runtime.store,pid_self_).type); \
  } \
  CONSLIST(CSM_CB_FFD) \
  CONSLIST(CSM_CB_FFC) \
  void static cchr_reactivate_all(void *dummy) { \
  	CONSLIST(CSM_CB_REC) \
  } \
  void static cchr_runtime_free() { \
  	CONSLIST(CSM_CB_FAC) \
  	dcls_destruct(_global_runtime.store); \
  }

#define CSM_CB_REC_S
#define CSM_CB_REC_D(NAME) cchr_reactivate_all_##NAME();

#define CSM_CB_FAC_S
#define CSM_CB_FAC_D(NAME) cchr_free_all_##NAME();

/* callback macro for declaration of fire functions */  
#define CSM_CB_FFD_S
#define CSM_CB_FFD_D(NAME) \
  void static inline cchr_fire_##NAME(dcls_pid_t,  ARGLIST_##NAME(CSM_CB_FFDAR,)); \
  void static inline cchr_add_##NAME(ARGLIST_##NAME(CSM_CB_FFDAR,)); \
  void static inline cchr_reactivate_##NAME(dcls_pid_t);


/* callback macro for arguments of declaration of fire functions */
#define CSM_CB_FFDAR_S ,
#define CSM_CB_FFDAR_D(NAME,TYPE,...) TYPE NAME

/* callback macro for code of fire functions */
#define CSM_CB_FFC_S
#define CSM_CB_FFC_D(NAME) \
  void static inline cchr_fire_##NAME(dcls_pid_t pid_self_ ARGLIST_##NAME(CSM_CB_FFCAR,)) { \
    int doadd=(pid_self_==DCLS_EMPTY_PID); \
    int oldid; \
    int oldgen; \
    CSM_DEBUG( \
	  CSM_PRINTF("fire ",NAME); \
      _global_runtime.debugindent++; \
    ) \
    RULELIST_##NAME(CSM_CB_FFCCO) \
    CSM_STROUT("final store") \
    CSM_NEEDSELF \
    CSM_END \
  } \
  void cchr_add_##NAME( ARGLIST_##NAME(CSM_CB_FFCAA,)) { \
  	cchr_fire_##NAME(DCLS_EMPTY_PID ARGLIST_##NAME(CSM_CB_FFCFC,)); \
  } \
  void cchr_reactivate_##NAME(dcls_pid_t pid_self_) { \
  	cchr_fire_##NAME(pid_self_ ARGLIST_##NAME(CSM_CB_FFCRA,NAME)); \
  } \
  void cchr_reactivate_all_##NAME() { \
  	CSM_LOOP(NAME,C, \
  	  cchr_reactivate_##NAME(pid_C); \
  	) \
  } \
  void cchr_free_all_##NAME() { \
  	CSM_LOOP(NAME,C, \
  	  CSM_FREE(C,NAME); \
  	) \
  }
  
#define CSM_CB_FFCRA_S
#define CSM_CB_FFCRA_D(NAME,TYPE,CON) ,CSM_LARG(CON,self_,NAME)

/* callback macro for arguments of code of fire functions */ 
#define CSM_CB_FFCAR_S
#define CSM_CB_FFCAR_D(NAME,TYPE,...) , TYPE arg_##NAME

/* callback macro for inclusion of constraint-occurrence code in fire functions */
#define CSM_CB_FFCCO_S
#define CSM_CB_FFCCO_D(NAME) { CSM_STROUT("try " #NAME); CODELIST_##NAME }

/* callback macro for arguments of code of add functions */
#define CSM_CB_FFCAA_S ,
#define CSM_CB_FFCAA_D(NAME,TYPE,...) TYPE arg_##NAME

/* callback macro for arguments passed to fire function in add functions */
#define CSM_CB_FFCFC_S
#define CSM_CB_FFCFC_D(NAME,TYPE,...) , arg_##NAME


#define CSM_ARG(TYPE,NAME) (arg_##NAME)

#define CSM_IF(EXP,CODE) { \
	if (EXP) { \
		CODE \
	} \
}
#define CSM_DIFFSELF(VAR) (pid_self_ != pid_##VAR)
#define CSM_DIFF(VAR1,VAR2) (pid_##VAR1 != pid_##VAR2)

/* callback macro for freeing propagation history records */ 
#define CSM_CB_FPH_D(T,V,A) { \
	alist_free(dcls_get(_global_runtime.store,pid_##A).data.T._ph_##V); \
}
#define CSM_CB_FPH_S

/* after a killself should always be a CSM_END (with a body and a CSM_FREESELF in between) */
#define CSM_KILLSELF(TYPE) { \
	if (pid_self_!=DCLS_EMPTY_PID) { \
		CSM_PROP(RULEHOOKS_##TYPE(CSM_CB_FPH,self_);) \
		dcls_remove(_global_runtime.store,pid_self_); \
		CSM_FMTOUT("kill pid=%i (self)",(int)pid_self_); \
	} \
}

/* after a kill should always be a CSM_FREE (before a CSM_END) */
#define CSM_KILL(VAR,TYPE) { \
	CSM_PROP(RULEHOOKS_##TYPE(CSM_CB_FPH,VAR);) \
	dcls_remove(_global_runtime.store,pid_##VAR); \
	CSM_FMTOUT("kill pid=%i",(int)pid_##VAR); \
}

#define CSM_DESTRUCT_PID(TYPE,PID) DESTRUCT_##TYPE CSM_CB_DPH_F(TYPE,PID)
#define CSM_CB_DPH_F(TYPE,PID) (ARGLIST_##TYPE(CSM_CB_DPH,TYPE,PID))
#define CSM_CB_DPH_S ,
#define CSM_CB_DPH_D(ARG,TYPE,CON,PID) CSM_LARG(CON,PID,ARG)

#define CSM_DESTRUCT_SELF(TYPE) DESTRUCT_##TYPE CSM_CB_DSH_F(TYPE)
#define CSM_CB_DSH_F(TYPE) (ARGLIST_##TYPE(CSM_CB_DSH,TYPE))
#define CSM_CB_DSH_S ,
#define CSM_CB_DSH_D(ARG,TYPE,CON) CSM_ARG(CON,ARG)

#define CSM_FREESELF(TYPE) { \
	CSM_DESTRUCT_SELF(TYPE); \
	if (pid_self_!=DCLS_EMPTY_PID) { \
		dcls_free(_global_runtime.store,pid_self_); \
		CSM_FMTOUT("free pid=%i (self)",(int)pid_self_); \
	} \
}

#define CSM_FREE(VAR,TYPE) { \
	CSM_DESTRUCT_PID(TYPE,VAR); \
	CSM_PROP(RULEHOOKS_##TYPE(CSM_CB_FPH,VAR);) \
	dcls_free(_global_runtime.store,pid_##VAR); \
	CSM_FMTOUT("free pid=%i",(int)pid_##VAR); \
}

#define CSM_LOOP(TYPE,VAR,CODE) { \
	dcls_iter(_global_runtime.store,pid_##VAR,CCHR_CONS_TYPE_##TYPE,{ \
		CODE \
	}) \
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
		CSM_PRINTF("make ",TYPE); \
	} \
	oldid=dcls_get(_global_runtime.store,pid_self_).id; \
	oldgen=dcls_get(_global_runtime.store,pid_self_).gen_num; \
	RULEHOOKS_##TYPE(CSM_CB_PHI,); \
}

/* callback macro for constraint suspension argument setting */ 
#define CSM_CB_MAKSA_S 
#define CSM_CB_MAKSA_D(NAME,TYPE,CON) dcls_get(_global_runtime.store,pid_self_).data.CON.NAME = arg_##NAME ;

#define CSM_CB_PHI_D(T,V,A) CSM_PROP( \
	alist_init(dcls_get(_global_runtime.store,pid_self_).data.T._ph_##V); \
	dcls_get(_global_runtime.store,pid_self_).data.T._phl_##V=0; \
)
#define CSM_CB_PHI_S

#define CSM_ALIVESELF (dcls_used(_global_runtime.store,pid_self_) && dcls_get(_global_runtime.store,pid_self_).id == oldid)
#define CSM_REGENSELF (dcls_get(_global_runtime.store,pid_self_).gen_num != oldgen)
#define CSM_ADD(CON,...) { \
	cchr_fire_##CON(DCLS_EMPTY_PID,__VA_ARGS__); \
}
#define CSM_ADDE(CON) { \
	cchr_fire_##CON(); \
}
#define CSM_NEEDSELF { \
	if (doadd) { \
		cchr_store(pid_self_); \
		doadd=0; \
		CSM_FMTOUT("store pid=%i",(int)pid_self_); \
	} \
}
#define CSM_DEFLOCAL(TYPE,VAR,EXPR) TYPE local_##VAR = EXPR;
#define CSM_DECLOCAL(TYPE,VAR) TYPE local_##VAR;
#define CSM_IMMLOCAL(TYPE,VAR,EXPR) const CSM_DEFLOCAL(TYPE,VAR,EXPR)
#define CSM_LOCAL(VAR) (local_##VAR)

#define CSM_MESSAGE(...) { \
	fprintf(stderr,__VA_ARGS__); \
}
#define CSM_NATIVE(CODE) { \
	CODE \
}

#define CSM_HISTCHECK(RULE,CODE,...) CSM_PROP(PROPHIST_##RULE(CSM_CB_HC,__VA_ARGS__,RULE,CODE)) CSM_NOPROP({CODE})
#define CSM_CB_HC_I(HOOK,RULE,CODE,COND) { \
	int ok_=1; \
	cchr_entry_t *p_=dcls_ptr(_global_runtime.store,pid_##HOOK); \
	for (int i_=0; i_<p_->data.PROPHIST_HOOK_##RULE._phl_##RULE; i_++) { \
		if (1 COND) { \
			CSM_FMTOUT("histfail %s (on %s:%i)",#RULE,#HOOK,dcls_get(_global_runtime.store,pid_##HOOK).id); \
			ok_=0; \
			break; \
		} \
	} \
	/*CSM_FMTOUT("histchk %s on id=%i%s",#RULE,dcls_get(_global_runtime.store,pid_##HOOK).id,ok_ ? ": ok" : "");*/ \
	if (ok_) { \
		CODE \
	} \
}
#define CSM_CB_HC_D(PID,HOOK,POS,RULE,CODE) && (alist_get(p_->data.PROPHIST_HOOK_##RULE._ph_##RULE,(i_*((RULE_KEPT_##RULE)-1))+POS)==dcls_get(_global_runtime.store,pid_##PID).id)
#define CSM_CB_HC_S(RULE,CODE)

#define CSM_HISTADD(RULE,...) CSM_PROP(PROPHIST_##RULE(CSM_CB_HA,__VA_ARGS__,RULE))
#define CSM_CB_HA_I(HOOK,RULE,COND) { \
	cchr_entry_t *p_=dcls_ptr(_global_runtime.store,pid_##HOOK); \
	int i_= ++(p_->data.PROPHIST_HOOK_##RULE._phl_##RULE); \
	alist_ensure(p_->data.PROPHIST_HOOK_##RULE._ph_##RULE,(i_*((RULE_KEPT_##RULE)-1))); \
	CSM_FMTOUTX("histadd %s (",0,#RULE); \
	COND \
	CSM_FMTOUTX(") to %s:%i",2,#HOOK,dcls_get(_global_runtime.store,pid_##HOOK).id); \
}
#define CSM_CB_HA_D(PID,HOOK,POS,RULE) alist_add(p_->data.PROPHIST_HOOK_##RULE._ph_##RULE,dcls_get(_global_runtime.store,pid_##PID).id); CSM_DEBUG(if (POS>0) CSM_STROUTX(",",1); CSM_FMTOUTX("%s:%i",1,#PID,dcls_get(_global_runtime.store,pid_##PID).id); );
#define CSM_CB_HA_S(RULE)

#endif

CSM_START
