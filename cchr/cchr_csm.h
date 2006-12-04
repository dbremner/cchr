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

#define CSM_STRINGIFY_(X) #X
#define CSM_STRINGIFY(X) CSM_STRINGIFY_(X)

#ifdef CSM_CONF_DEBUG
#define CSM_DEBUG(...) __VA_ARGS__
#else
#define CSM_DEBUG(...)
#endif

#define CSM_INDENT { CSM_DEBUG( for (int i=0; i<_global_runtime.debugindent; i++) fprintf(stderr,"  "); ) }
#define CSM_PRINTF(INIT,TYPE) CSM_DEBUG( CSM_INDENT { fprintf(stderr,"%s%s: " FORMAT_##TYPE "#%i\n",INIT,#TYPE ARGLIST_##TYPE(CSM_START_DEF5_3_,CSM_START_SEP5_3_),(int)pid_self_); } )
#define CSM_FMTOUT(FMT,...) CSM_DEBUG( { CSM_INDENT fprintf(stderr,FMT "\n",__VA_ARGS__); } )
#define CSM_STROUT(FMT) CSM_DEBUG( { CSM_INDENT fputs(FMT "\n",stderr); } )

#define CSM_START_SEP1_ ,
#define CSM_START_DEF1_(NAME) CCHR_CONS_TYPE_ ## NAME

#define CSM_START_SEP2_
#define CSM_START_DEF2_(NAME) \
  typedef struct { \
    ARGLIST_##NAME(CSM_START_DEF2_1_,CSM_START_SEP2_1_) \
  } cchr_cons_ ## NAME ## _t;

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

#define CSM_IF(EXP,CODE) { if (EXP) { CODE } }
#define CSM_DIFFSELF(VAR) (pid_self_ != pid_##VAR)
#define CSM_DIFF(VAR1,VAR2) (pid_##VAR1 != pid_##VAR2)
#define CSM_KILL_
#define CSM_KILLSELF(TYPE) { if (pid_self_!=DCLS_EMPTY_PID) { DESTRUCT_##TYPE(self_); dcls_empty(_global_runtime.store,pid_self_); CSM_FMTOUT("kill %i (self)",(int)pid_self_); } }
#define CSM_KILL(VAR,TYPE) { DESTRUCT_##TYPE(VAR); dcls_empty(_global_runtime.store,pid_##VAR); CSM_FMTOUT("kill %i",(int)pid_##VAR); }
#define CSM_LOOP(TYPE,VAR,CODE) { dcls_iter(_global_runtime.store,pid_##VAR,CCHR_CONS_TYPE_##TYPE,{CODE}) }
#define CSM_END { CSM_DEBUG(_global_runtime.debugindent--; CSM_STROUT("end fire");) return; }
#define CSM_LARG(TYPE,VAR,NAME) (dcls_get(_global_runtime.store,pid_##VAR).data.TYPE.NAME)
#define CSM_MAKE(TYPE) { \
	if (doadd && pid_self_==DCLS_EMPTY_PID) { \
		pid_self_=cchr_make_entry(CCHR_CONS_TYPE_##TYPE); \
		ARGLIST_##TYPE(CSM_MAKE_DEF1_,CSM_MAKE_SEP1_); \
		CSM_PRINTF("make ",TYPE); \
	} \
	oldid=dcls_get(_global_runtime.store,pid_self_).id; \
	oldgen=dcls_get(_global_runtime.store,pid_self_).gen_num; \
}

#define CSM_ALIVESELF (dcls_used(_global_runtime.store,pid_self_) && dcls_get(_global_runtime.store,pid_self_).id == oldid)
#define CSM_REGENSELF (dcls_get(_global_runtime.store,pid_self_).gen_num != oldgen)
#define CSM_ADD(CON,...) { cchr_fire_##CON(DCLS_EMPTY_PID,__VA_ARGS__); }
#define CSM_ADDE(CON) { cchr_fire_##CON(); }
#define CSM_NEEDSELF { if (doadd) {cchr_store(pid_self_); doadd=0; CSM_FMTOUT("store %i",(int)pid_self_); } }
#define CSM_DEFLOCAL(TYPE,VAR,EXPR) TYPE local_##VAR; {local_##VAR = (EXPR);}
#define CSM_LOCAL(VAR) (local_##VAR)
#define CSM_MESSAGE(...) {fprintf(stderr,__VA_ARGS__);}
#define CSM_NATIVE(CODE) { CODE }

#define CSM_MAKE_DEF1_(CON,NAME,TYPE) dcls_get(_global_runtime.store,pid_self_).data.CON.NAME = arg_##NAME ;
#define CSM_MAKE_SEP1_ 

#endif

CSM_START
