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

#define CSM_STRINGIFY_(X) #X
#define CSM_STRINGIFY(X) CSM_STRINGIFY_(X)

#ifdef CSM_CONF_DEBUG
#define CSM_DEBUG(...) __VA_ARGS__
#else
#define CSM_DEBUG(...)
#endif

#define CSM_INDENT { \
	CSM_DEBUG( \
		for (int i=0; i<_global_runtime.debugindent; i++) fprintf(stderr,"  "); \
	) \
}
#define CSM_PRINTF(INIT,TYPE) CSM_DEBUG( \
	CSM_INDENT \
	{ \
		fprintf(stderr,"%s%s: " FORMAT_##TYPE " pid=%i id=%i\n",INIT,#TYPE ARGLIST_##TYPE(CSM_START_DEF5_3_,CSM_START_SEP5_3_),(int)pid_self_,pid_self_!= DCLS_EMPTY_PID ? dcls_get(_global_runtime.store,pid_self_).id : -1); \
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

#define CSM_START_SEP1_ ,
#define CSM_START_DEF1_(NAME) CCHR_CONS_TYPE_ ## NAME

#define CSM_START_SEP2_
#define CSM_START_DEF2_(NAME) \
  typedef struct { \
    ARGLIST_##NAME(CSM_START_DEF2_1_,CSM_START_SEP2_1_) \
    RULEHOOKS_##NAME(CSM_CB_CLPH_D,CSM_SB_CLPH_S,) \
  } cchr_cons_ ## NAME ## _t;

#define CSM_CB_CLPH_D(T,V,A) int _phl_##V; alist_declare(int,_ph_##V);
#define CSM_CB_CLPH_S

#define CSM_START_SEP2_1_
#define CSM_START_DEF2_1_(CON,NAME,TYPE) TYPE NAME;

#define CSM_START_SEP3_
#define CSM_START_DEF3_(NAME) cchr_cons_ ## NAME ## _t NAME;

#define CSM_START_SEP4_
#define CSM_START_DEF4_(NAME) void static inline cchr_fire_##NAME(dcls_pid_t,  ARGLIST_##NAME(CSM_START_DEF4_1_,CSM_START_SEP4_1_));

#define CSM_START_SEP4_1_ ,
#define CSM_START_DEF4_1_(CON,NAME,TYPE) TYPE NAME

#define CSM_START_SEP5_
#define CSM_START_DEF5_(NAME) \
  void static inline cchr_fire_##NAME(dcls_pid_t pid_self_ ARGLIST_##NAME(CSM_START_DEF5_1_,CSM_START_SEP5_1_)) { \
    int doadd=(pid_self_==DCLS_EMPTY_PID); \
    int oldid; \
    int oldgen; \
    CSM_DEBUG( \
	  CSM_PRINTF("fire ",NAME); \
      _global_runtime.debugindent++; \
    ) \
    RULELIST_##NAME(CSM_START_DEF5_2_,CSM_START_SEP5_2_) \
    CSM_NEEDSELF \
    CSM_END \
  } \
  void cchr_add_##NAME( ARGLIST_##NAME(CSM_START_DEF5_4_,CSM_START_SEP5_4_)) { \
  	cchr_fire_##NAME(DCLS_EMPTY_PID ARGLIST_##NAME(CSM_START_DEF5_3_,CSM_START_SEP5_3_)); \
  }

#define CSM_START_SEP5_1_
#define CSM_START_DEF5_1_(CON,NAME,TYPE) , TYPE arg_##NAME

#define CSM_START_SEP5_2_
#define CSM_START_DEF5_2_(NAME) { CODELIST_##NAME }

#define CSM_START_SEP5_3_
#define CSM_START_DEF5_3_(CON,NAME,TYPE) , arg_##NAME

#define CSM_START_SEP5_4_ ,
#define CSM_START_DEF5_4_(CON,NAME,TYPE) TYPE arg_##NAME


#define CSM_START \
  enum cchr_cons_type { CONSLIST(CSM_START_DEF1_,CSM_START_SEP1_) , CCHR_CONS_COUNT }; \
  CONSLIST(CSM_START_DEF2_,CSM_START_SEP2_) \
  typedef struct { \
    enum cchr_cons_type type; \
    int id; \
    int gen_num; \
    union { \
      CONSLIST(CSM_START_DEF3_,CSM_START_SEP3_) \
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
  void static inline cchr_store(dcls_pid_t pid_self_) { \
    dcls_add_begin(_global_runtime.store,pid_self_,dcls_get(_global_runtime.store,pid_self_).type); \
  } \
  CONSLIST(CSM_START_DEF4_,CSM_START_SEP4_) \
  CONSLIST(CSM_START_DEF5_,CSM_START_SEP5_) \
  

#define CSM_ARG(TYPE,NAME) (arg_##NAME)

#define CSM_IF(EXP,CODE) { \
	if (EXP) { \
		CODE \
	} \
}
#define CSM_DIFFSELF(VAR) (pid_self_ != pid_##VAR)
#define CSM_DIFF(VAR1,VAR2) (pid_##VAR1 != pid_##VAR2)

#define CSM_KILLSELF(TYPE) { \
	if (pid_self_!=DCLS_EMPTY_PID) { \
		DESTRUCT_##TYPE(self_); \
		RULEHOOKS_##TYPE(CSM_CB_FPH_D,CSM_CB_FPH_S,self_); \
		dcls_empty(_global_runtime.store,pid_self_); \
		CSM_FMTOUT("kill pid=%i (self)",(int)pid_self_); \
	} \
}

#define CSM_KILL(VAR,TYPE) { \
	DESTRUCT_##TYPE(VAR); \
	RULEHOOKS_##TYPE(CSM_CB_FPH_D,CSM_CB_FPH_S,VAR); \
	dcls_empty(_global_runtime.store,pid_##VAR); \
	CSM_FMTOUT("kill pid=%i",(int)pid_##VAR); \
}

#define CSM_LOOP(TYPE,VAR,CODE) { \
	dcls_iter(_global_runtime.store,pid_##VAR,CCHR_CONS_TYPE_##TYPE,{ \
		CODE \
	}) \
}

#define CSM_CB_FPH_D(T,V,A) { alist_free(dcls_get(_global_runtime.store,pid_##A).data.T._ph_##V); }
#define CSM_CB_FPH_S

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
		ARGLIST_##TYPE(CSM_MAKE_DEF1_,CSM_MAKE_SEP1_); \
		CSM_PRINTF("make ",TYPE); \
	} \
	oldid=dcls_get(_global_runtime.store,pid_self_).id; \
	oldgen=dcls_get(_global_runtime.store,pid_self_).gen_num; \
	RULEHOOKS_##TYPE(CSM_CB_PHI_D,CSM_CB_PHI_S,); \
}

#define CSM_CB_PHI_D(T,V,A) alist_init(dcls_get(_global_runtime.store,pid_self_).data.T._ph_##V);
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

#define CSM_LOCAL(VAR) (local_##VAR)
#define CSM_MESSAGE(...) { \
	fprintf(stderr,__VA_ARGS__); \
}
#define CSM_NATIVE(CODE) { \
	CODE \
}

#define CSM_HISTCHECK(RULE,CODE,...) PROPHIST_##RULE(CSM_CB_HC,__VA_ARGS__,RULE,CODE)
#define CSM_CB_HC_I(HOOK,RULE,CODE,COND) { \
	int ok_=1; \
	cchr_entry_t *p_=dcls_ptr(_global_runtime.store,pid_##HOOK); \
	for (int i_=0; i_<p_->data.PROPHIST_HOOK_##RULE._phl_##RULE; i_++) { \
		if (1 COND) { \
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

#define CSM_HISTADD(RULE,...) PROPHIST_##RULE(CSM_CB_HA,__VA_ARGS__,RULE)
#define CSM_CB_HA_I(HOOK,RULE,COND) { \
	cchr_entry_t *p_=dcls_ptr(_global_runtime.store,pid_##HOOK); \
	int i_= ++(p_->data.PROPHIST_HOOK_##RULE._phl_##RULE); \
	alist_ensure(p_->data.PROPHIST_HOOK_##RULE._ph_##RULE,(i_*((RULE_KEPT_##RULE)-1))); \
	CSM_FMTOUTX("histadd %s (",0,#RULE); \
	COND \
	CSM_FMTOUTX(") to id=%i",2,dcls_get(_global_runtime.store,pid_##HOOK).id); \
}
#define CSM_CB_HA_D(PID,HOOK,POS,RULE) alist_add(p_->data.PROPHIST_HOOK_##RULE._ph_##RULE,dcls_get(_global_runtime.store,pid_##PID).id); CSM_DEBUG(if (POS>0) CSM_STROUTX(",",1); CSM_FMTOUTX("%i",1,dcls_get(_global_runtime.store,pid_##PID).id); );
#define CSM_CB_HA_S(RULE)

#define CSM_MAKE_DEF1_(CON,NAME,TYPE) dcls_get(_global_runtime.store,pid_self_).data.CON.NAME = arg_##NAME ;
#define CSM_MAKE_SEP1_ 

#endif

CSM_START
