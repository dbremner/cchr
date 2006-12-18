/****************************************************************************\
| CCHR - A CHR-in-C to C compiler                                            |
| logical.h - builtin equivalence solver                                     |
| written by Pieter Wuille                                                   |
\****************************************************************************/ 

#ifndef LOGICAL_H_
#define LOGICAL_H_ 1

typedef enum  {
	LOGICAL_NODE_TYPE_NONROOT=0,
	LOGICAL_NODE_TYPE_ROOT=1,
	LOGICAL_NODE_TYPE_VAL=2
} logical_node_type_t;

#define logical_typedef(in,out) typedef struct _##out##_struct_ *out; struct _##out##_struct_ { \
	union {
		in val; \
		out par; \
	} _data; \
	logical_node_type_t	_type; \
	int _refcount; \
	int _rank; \
};

#define logical_normalize(var,type) { \
	if ((var)->_type==LOGICAL_NODE_TYPE_NONROOT) {
		type _top=(var);
		while (_top->_type==LOGICAL_NODE_TYPE_NONROOT) { \
			_top=_top->_data.par; \
		} \
		while ((var)->_type==LOGICAL_NODE_TYPE_NONROOT) { \
			type _next=(var)->_data.par; \
			if ((var)->_refcount>0) { \
				(var)->_data.par=_top; \
				_top->_refcount++; \
			} else { \
				free((var)); \
			} \
			(var)=_next; \
			(var)->_refcount--; \
		} \
	} \
}

/* @pre: var is unitialised */
#define logical_init(var) { \
	(var)=malloc(sizeof((var)[0])); \
	(var)->_type=LOGICAL_NONE_TYPE_ROOT; \
	(var)->_refcount=1; \
	(var)->_rank=0; \
}

/* @pre: var is normalized */
#define logical_setval(var,val,type) { \
	(var)->_type=LOGICAL_NODE_TYPE_VAL; \
	(var)->_data.val=val; \
}

/* @pre: var1 and var2 are normalized */
#define logical_seteq(var1,var2,type) { \
	int _inc=0; \
	if ((var1)->_rank<(var2)->_rank) { \
		type _tmp=(var1); \
		(var1)=(var2); \
		(var2)=_tmp; \
	} \
	(var2)->_data.par=(var1); \
	if ((var2)->_type==LOGICAL_NODE_TYPE_VAL) { \
		(var1)->_type=LOGICAL_NODE_TYPE_VAL; \
		(var1)->_data.val=(var2)->_data.val; \
	}
	if ((var1)->_rank==(var2)->_rank) (var1)->rank++; \
}

/* @pre: var is normalised */
#define logical_destruct(var,type,destr) { \
	(var)->_refcount--; \
	if ((var)->_refcount==0) { \
		if ((var)->_type==LOGICAL_NONE_TYPE_VAL) { destr((var)->_data.val); } \
		free((var)); \
		(var)=NULL; \
	}	
}

/* @pre: var is normalised */
#define logical_testeq(var1,var2) ( \
	(var1)==(var2) || \
	( \
		(var1)->type==LOGICAL_NONE_TYPE_VAL && \
		(var2)->type==LOGICAL_NONE_TYPE_VAL && \
		(var1)->_data.val==(var2)->_data.val \
	) \
)

/* @pre: var is normalised */
#define logical_hasval(var) ((var)->_type==LOGICAL_NONE_TYPE_VAL)

/* @pre: var is normalised */
#define logical_getval(var) ((var)->_data.val)

#endif /*LOGICAL_H_*/
