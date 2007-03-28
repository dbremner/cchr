/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| logical.h - builtin equivalence solver (using GUF)                         |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef LOGICAL_H_
#define LOGICAL_H_ 1

#ifdef USE_EFENCE
#define INLINE
#else
#define INLINE inline
#endif

#ifndef DEBUG
#define LOG_DEBUG(...)
#else
#define LOG_DEBUG(...) __VA_ARGS__
#endif

#include "alist.h"

typedef enum  {
	LOGICAL_NODE_TYPE_NONROOT=0, /* not a root */
	LOGICAL_NODE_TYPE_ROOT=1, /* a root without value */
	LOGICAL_NODE_TYPE_VAL=2 /* a root with value */
} logical_node_type_t;

#define logical_nodestr(val)

#define logical_header(in,out) \
	LOG_DEBUG(static int _##out##_nextid = 1;) \
	typedef struct _##out##_struct_ *out; \
	typedef struct { \
		void (*cb)(void*); \
		void *data; \
	} out##_cb_data_t; \
	struct _##out##_struct_ { \
		logical_node_type_t	_type; \
		union { \
			struct { \
				out par; /* parent (for type==NONROOT) */ \
			} nonroot; \
			struct { \
				in val; /* value (for _type==VAL) */ \
				int rank; /* depth of this tree (for type != NONROOT) */ \
				alist_declare(out##_cb_data_t,cbs); /* callbacks upon change of variable data */ \
				out##_cb_data_t cb; \
			} root; \
		} _data; \
		int _refcount; /* reference count */ \
		LOG_DEBUG(int _id;) \
	}; \
	out static INLINE out##_copy(out var); \
	out static INLINE out##_create(); \
	void static INLINE out##_setval(out var,in value); \
	void static out##_seteq(out var1, out var2); \
	void static INLINE out##_destruct(out var); \
	int static INLINE out##_testeq(out var1, out var2); \
	int static INLINE out##_hasval(out var); \
	in static INLINE out##_getval(out var); \
	void static INLINE out##_setcb(out var,void (*cb)(void*),void *data); \
	void static INLINE out##_addcb(out var,void (*cb)(void*),void *data);
	
#define logical_code(in,out,destr) \
	logical_header(in,out) \
	/* requires normalized argument */ \
	void static out##_docallbacks(out var) { \
		if (var->_data.root.cb.cb) { \
			var->_data.root.cb.cb(var->_data.root.cb.data); \
		} \
		for (int i=0; i<alist_len(var->_data.root.cbs); i++) { \
			out##_cb_data_t *cbd=alist_ptr(var->_data.root.cbs,i); \
			cbd->cb(cbd->data); \
		} \
	} \
	out static out##_normalize(out var) { \
		LOG_DEBUG( \
			if (var->_refcount<=0) { \
				LOG_DEBUG(fprintf(stderr,"[normalizing logical (%s) #%i => REFCOUNT==%i !!!]\n",#out,var->_id,var->_refcount);) \
				return NULL; \
			} \
			int oid=var->_id; \
		) \
		if (var->_type==LOGICAL_NODE_TYPE_NONROOT) { /* only when this is no root */ \
			out _top=var; /* temporary top variable */ \
			while (_top->_type==LOGICAL_NODE_TYPE_NONROOT) { /* first search the top */ \
				_top=_top->_data.nonroot.par; /* by recursively going up */ \
			} \
			var=var->_data.nonroot.par; \
			while (var->_type==LOGICAL_NODE_TYPE_NONROOT) { /* then do this again (in var itself) */ \
				var->_refcount--; /* this node will lose a reference */ \
				out _next=var->_data.nonroot.par; /* find who our former parent was */ \
				if (var->_refcount>0) { /* if this node should remain alive */ \
					var->_data.nonroot.par=_top; /* make it point to the top */ \
					_top->_refcount++; /* and increase refcount of top */ \
				} else { /* otherwise */ \
					free(var); /* free memory for this node */ \
				} \
				var=_next; /* move to the next node */ \
			} \
			LOG_DEBUG(fprintf(stderr,"[normalized logical (%s) #%i => #%i]\n",#out,oid,_top->_id);) \
			return _top; \
		} \
		return var; \
	} \
	out static INLINE out##_copy(out var) { \
		out ret=out##_normalize(var); \
		ret->_refcount++; \
		LOG_DEBUG(fprintf(stderr,"[copy logical (%s) #%i => refcount=%i]\n",#out,ret->_id,ret->_refcount);) \
		return ret; \
	} \
	out static INLINE out##_create() { \
		out ret; \
		ret=malloc(sizeof(*ret)); \
		ret->_type=LOGICAL_NODE_TYPE_ROOT; \
		ret->_refcount=1; \
		ret->_data.root.rank=0; \
		alist_init(ret->_data.root.cbs); \
		LOG_DEBUG(ret->_id=_##out##_nextid++;) \
		LOG_DEBUG(fprintf(stderr,"[created logical (%s) #%i]\n",#out,ret->_id);) \
		ret->_data.root.cb.cb=NULL; \
		return ret; \
	} \
	void static INLINE out##_setval(out var,in value) { \
		var=out##_normalize(var); \
		(var)->_type=LOGICAL_NODE_TYPE_VAL; \
		(var)->_data.root.val=value; \
		LOG_DEBUG(fprintf(stderr,"[setval logical (%s #%i]\n",#out,var->_id);) \
		out##_docallbacks(var); \
	} \
	void static out##_seteq(out var1, out var2) { \
		LOG_DEBUG(fprintf(stderr,"[seteq logical (%s) #%i <-> #%i]\n",#out,var1->_id,var2->_id);) \
		var1=out##_normalize(var1); \
		var2=out##_normalize(var2); \
		LOG_DEBUG(fprintf(stderr,"[seteq roots:  (%s) #%i <-> #%i]\n",#out,var1->_id,var2->_id);) \
		if (var1 != var2) { \
			if ((var1)->_data.root.rank<(var2)->_data.root.rank) { /* if rank2<rank1 */ \
				out _tmp=(var1); \
				(var1)=(var2); /* swap var1 and var2 */ \
				(var2)=_tmp; \
			} \
			if ((var2)->_type==LOGICAL_NODE_TYPE_VAL) { /* if to-be-child had a value */ \
				(var1)->_type=LOGICAL_NODE_TYPE_VAL; \
				(var1)->_data.root.val=(var2)->_data.root.val; /* this value is moved to parent */ \
			} \
			alist_addall(var1->_data.root.cbs,var2->_data.root.cbs); /* join callbacks together */ \
			if ((var2)->_data.root.cb.cb) (var1)->_data.root.cb = (var2)->_data.root.cb; /* overwrite single-callback */ \
			(var2)->_type=LOGICAL_NODE_TYPE_NONROOT; /* child becomes type NONROOT */ \
			(var2)->_data.nonroot.par=var1; /* its parent is set */ \
			(var1)->_refcount++; /* its parent's refcount increased */ \
			LOG_DEBUG(fprintf(stderr,"[seteq refc: (%s) #%i=%i #%i=%i]\n",#out,var1->_id,var1->_refcount,var2->_id,var2->_refcount);) \
			if ((var1)->_data.root.rank==(var2)->_data.root.rank) (var1)->_data.root.rank++; /* rank increase if necessary */ \
			out##_docallbacks(var1); \
		} \
	} \
	void static INLINE out##_destruct(out var) { \
		int remtop=1; \
		LOG_DEBUG(fprintf(stderr,"[destruct logical (%s) #%i]\n",#out,var->_id);) \
		out top=out##_normalize(var); \
		LOG_DEBUG(fprintf(stderr,"[destruct root:   (%s) #%i]\n",#out,var->_id);) \
		if (top != var) { \
			var->_refcount--; \
			if (var->_refcount==0) { \
				free(var); \
			} else { \
				remtop=0; \
			} \
		} \
		if (remtop) { \
			top->_refcount--; \
			if (top->_refcount==0) { \
				LOG_DEBUG(fprintf(stderr,"[destruct free:    (%s) #%i]\n",#out,var->_id);) \
				{ destr((top->_data.root.val)); } \
				alist_free(top->_data.root.cbs); \
				free(top); \
			} \
		} \
	} \
	int static INLINE out##_testeq(out var1, out var2) { \
		out var1b=out##_normalize(var1); \
		out var2b=out##_normalize(var2); \
		LOG_DEBUG(fprintf(stderr,"[testeq %p:#%i(#%i) %p:#%i(#%i)]\n",var1,var1->_id,var1b->_id,var2,var2->_id,var2b->_id);) \
		return ((var1b)==(var2b)); \
	} \
	int static INLINE out##_hasval(out var) { \
		var=out##_normalize(var); \
		return (var->_type==LOGICAL_NODE_TYPE_VAL); \
	} \
	in static INLINE out##_getval(out var) { \
		var=out##_normalize(var); \
		return (var)->_data.root.val; \
	} \
	void static INLINE out##_setcb(out var,void (*cb)(void*),void *data) { \
		var=out##_normalize(var); \
		var->_data.root.cb.cb=cb; \
		var->_data.root.cb.data=data; \
	} \
	void static INLINE out##_addcb(out var,void (*cb)(void*),void *data) { \
		var=out##_normalize(var); \
		out##_cb_data_t cbd; \
		cbd.cb=cb; \
		cbd.data=data; \
		alist_add(var->_data.root.cbs,cbd); \
	}

#endif /*LOGICAL_H_*/
