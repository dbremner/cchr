/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| logical.h - builtin equivalence solver (using GUF)                         |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef LOGICAL_H_
#define LOGICAL_H_ 1

#include "alist.h"

typedef enum  {
	LOGICAL_NODE_TYPE_NONROOT=0, /* not a root */
	LOGICAL_NODE_TYPE_ROOT=1, /* a root without value */
	LOGICAL_NODE_TYPE_VAL=2 /* a root with value */
} logical_node_type_t;


#define logical_header(in,out) \
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
	}; \
	out static inline out##_create(); \
	void static inline out##_setval(out var,in value); \
	void static out##_seteq(out var1, out var2); \
	void static inline out##_destruct(out var,void (*cb)(in)); \
	int static inline out##_testeq(out var1, out var2); \
	int static inline out##_hasval(out var); \
	in static inline out##_getval(out var); \
	void static inline out##_setcb(out var,void (*cb)(void*),void *data); \
	void static inline out##_addcb(out var,void (*cb)(void*),void *data);
	
#define logical_code(in,out) \
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
			return _top; \
		} \
		return var; \
	} \
	out static inline out##_create() { \
		out ret; \
		ret=malloc(sizeof(*ret)); \
		ret->_type=LOGICAL_NODE_TYPE_ROOT; \
		ret->_refcount=1; \
		ret->_data.root.rank=0; \
		alist_init(ret->_data.root.cbs); \
		ret->_data.root.cb.cb=NULL; \
		return ret; \
	} \
	void static inline out##_setval(out var,in value) { \
		var=out##_normalize(var); \
		(var)->_type=LOGICAL_NODE_TYPE_VAL; \
		(var)->_data.root.val=value; \
		out##_docallbacks(var); \
	} \
	void static out##_seteq(out var1, out var2) { \
		var1=out##_normalize(var1); \
		var2=out##_normalize(var2); \
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
			if ((var1)->_data.root.rank==(var2)->_data.root.rank) (var1)->_data.root.rank++; /* rank increase if necessary */ \
			out##_docallbacks(var1); \
		} \
	} \
	void static inline out##_destruct(out var,void (*cb)(in)) { \
		int remtop=1; \
		out top=out##_normalize(var); \
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
				if (cb && top->_type==LOGICAL_NODE_TYPE_VAL) { cb(top->_data.root.val); } \
				alist_free(top->_data.root.cbs); \
				free(top); \
			} \
		} \
	} \
	int static inline out##_testeq(out var1, out var2) { \
		var1=out##_normalize(var1); \
		var2=out##_normalize(var2); \
		return ((var1)==(var2) || \
			( \
				(var1)->_type==LOGICAL_NODE_TYPE_VAL && \
				(var2)->_type==LOGICAL_NODE_TYPE_VAL && \
				(var1)->_data.root.val==(var2)->_data.root.val \
			)); \
	} \
	int static inline out##_hasval(out var) { \
		var=out##_normalize(var); \
		return (var->_type==LOGICAL_NODE_TYPE_VAL); \
	} \
	in static inline out##_getval(out var) { \
		var=out##_normalize(var); \
		return (var)->_data.root.val; \
	} \
	void static inline out##_setcb(out var,void (*cb)(void*),void *data) { \
		var=out##_normalize(var); \
		var->_data.root.cb.cb=cb; \
		var->_data.root.cb.data=data; \
	} \
	void static inline out##_addcb(out var,void (*cb)(void*),void *data) { \
		var=out##_normalize(var); \
		out##_cb_data_t cbd; \
		cbd.cb=cb; \
		cbd.data=data; \
		alist_add(var->_data.root.cbs,cbd); \
	}

#endif /*LOGICAL_H_*/
