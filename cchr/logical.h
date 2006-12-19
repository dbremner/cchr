/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| logical.h - builtin equivalence solver (using GUF)                         |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef LOGICAL_H_
#define LOGICAL_H_ 1

typedef enum  {
	LOGICAL_NODE_TYPE_NONROOT=0, /* not a root */
	LOGICAL_NODE_TYPE_ROOT=1, /* a root without value */
	LOGICAL_NODE_TYPE_VAL=2 /* a root with value */
} logical_node_type_t;

#define logical_typedef(in,out) typedef struct _##out##_struct_ *out; struct _##out##_struct_ { \
	logical_node_type_t	_type; \
	union { \
		struct { \
			out par; /* parent (for type==NONROOT) */ \
		} nonroot; \
		struct { \
			in val; /* value (for _type==VAL) */ \
			int rank; /* depth of this tree (for type != NONROOT) */ \
		} root; \
	} _data; \
	int _refcount; /* reference count */ \
};

/* make var and all its parents point to their (common) root, and remove all
 * unnecessary nodes on the way */
#define logical_normalize(var,type) { \
	if ((var)->_type==LOGICAL_NODE_TYPE_NONROOT) { /* only when this is no root */ \
		type _top=(var); /* temporary top variable */ \
		while (_top->_type==LOGICAL_NODE_TYPE_NONROOT) { /* first search the top */ \
			_top=_top->_data.nonroot.par; /* by recursively going up */ \
		} \
		while ((var)->_type==LOGICAL_NODE_TYPE_NONROOT) { /* then do this again (in var itself) */ \
			(var)->_refcount--; /* this node will lose a reference */ \
			type _next=(var)->_data.nonroot.par; /* find who our former parent was */ \
			if ((var)->_refcount>0) { /* if this node should remain alive */ \
				(var)->_data.nonroot.par=_top; /* make it point to the top */ \
				_top->_refcount++; /* and increase refcount of top */ \
			} else { /* otherwise */ \
				free((var)); /* free memory for this node */ \
			} \
			(var)=_next; /* move to the next node */ \
		} \
	} \
}

/* initialize a logical variable */
/* @pre: var is unitialised */
#define logical_init(var) { \
	(var)=malloc(sizeof((var)[0])); \
	(var)->_type=LOGICAL_NODE_TYPE_ROOT; \
	(var)->_refcount=1; \
	(var)->_data.root.rank=0; \
}

/* give a logical variable a value */
/* @pre: var is normalized */
#define logical_setval(var,value) { \
	(var)->_type=LOGICAL_NODE_TYPE_VAL; \
	(var)->_data.root.val=value; \
}

/* state that var1 and var2 have the same value (whether this is known
 * already or not */
/* @pre: var1 and var2 are normalized */
#define logical_seteq(var1,var2,type) { \
	if ((var1)->_data.root.rank<(var2)->_data.root.rank) { /* if rank2<rank1 */ \
		type _tmp=(var1); \
		(var1)=(var2); /* swap var1 and var2 */ \
		(var2)=_tmp; \
	} \
	if ((var2)->_type==LOGICAL_NODE_TYPE_VAL) { /* if to-be-child had a value */ \
		(var1)->_type=LOGICAL_NODE_TYPE_VAL; \
		(var1)->_data.root.val=(var2)->_data.root.val; /* this value is moved to parent */ \
	} \
	(var2)->_type=LOGICAL_NODE_TYPE_NONROOT; /* child becomes type NONROOT */\
	(var2)->_data.nonroot.par=(var1); /* its parent is set */ \
	(var1)->_refcount++; /* its parent's refcount increased */ \
	if ((var1)->_data.root.rank==(var2)->_data.root.rank) (var1)->_data.root.rank++; /* rank increase if necessary */ \
}

/* destructor for logical variables */
/* @pre: var is normalised */
#define logical_destruct(var,type,destr) { \
	(var)->_refcount--; \
	if ((var)->_refcount==0) { \
		if ((var)->_type==LOGICAL_NODE_TYPE_VAL) { destr((var)->_data.root.val); } \
		free((var)); \
		(var)=NULL; \
	} \
}

/* callback for 'destr' argument of logical_destruct, if no destructor is needed */ 
#define logical_void(foo)

/* check whether var1 and var2 are equal (whether through seteq()'s or through same value) */ 
/* @pre: var1 and var2 are normalised */
#define logical_testeq(var1,var2) ( \
	(var1)==(var2) || \
	( \
		(var1)->_type==LOGICAL_NODE_TYPE_VAL && \
		(var2)->_type==LOGICAL_NODE_TYPE_VAL && \
		(var1)->_data.root.val==(var2)->_data.root.val \
	) \
)

/* check whether var's value is known */
/* @pre: var is normalised */
#define logical_hasval(var) ((var)->_type==LOGICAL_NODE_TYPE_VAL)

/* retrieve var's value */
/* @pre: var is normalised and logical_hasval() is true */
#define logical_getval(var) ((var)->_data.root.val)

#endif /*LOGICAL_H_*/
