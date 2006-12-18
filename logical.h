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

#define LOGICAL_NODE_TYPE_NONROOT 0
#define LOGICAL_NODE_TYPE_ROOT 1
#define LOGICAL_NODE_TYPE_VAL 2

#define les_typedef(in,out) typedef struct _##out##_struct_ *out; struct _##out##_struct_ { \
	union {
		in val; \
		out par; \
	} _data; \
	logical_node_type_t	_type; \
	int _refcount; \
};

#define les_findtop(var,top) { \
	(top)=(var); \
	while ((top)->_type==LOGICAL_NODE_TYPE_NONROOT) { \
		(top)=(top)->_data.par;
	} \
}

#define les_initval(var,value,type) { \
	(var)=malloc(sizeof((var)[0])); \
	(var)->_data.val=(value); \
	(var)->_type=LOGICAL_NODE_TYPE_VAL; \
	(var)->_refcount=1; \
}

#define les_initeq(var,var2,type) { \
	type _top2; \
	les_findtop(var2,_top2); \
	
}

#endif /*LOGICAL_H_*/
