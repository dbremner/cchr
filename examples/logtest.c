#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef USE_EFENCE
#include <efence.h>
#endif

#include "../logical.h"

logical_typedef(int,int_log_t);

void test(int_log_t *v1,int_log_t *v2) {
	logical_normalize(*v1,int_log_t);
	logical_normalize(*v2,int_log_t);
	logical_seteq(*v1,*v2,int_log_t);
}

int main(int argc,char **argv) {
	int_log_t v1;
	int_log_t v2;
	int_log_t v3;
	logical_init(v1);
	logical_init(v2);
	logical_init(v3);
	logical_setval(v3,5);
	logical_normalize(v3,int_log_t);
	assert(logical_hasval(v3));
	assert(logical_getval(v3)==5);
	logical_seteq(v1,v2,int_log_t);
	logical_normalize(v1,int_log_t);
	logical_normalize(v2,int_log_t);
	assert(logical_testeq(v1,v2));
	assert(!logical_testeq(v1,v3));
	assert(!logical_testeq(v2,v3));
	assert(!logical_hasval(v1));
	assert(!logical_hasval(v2));
	assert(logical_hasval(v3));
	assert(logical_getval(v3)==5);
	logical_seteq(v2,v3,int_log_t);
	logical_normalize(v1,int_log_t);
	logical_normalize(v2,int_log_t);
	logical_normalize(v3,int_log_t);
	assert(logical_testeq(v1,v2));
	assert(logical_testeq(v2,v3));
	assert(logical_testeq(v3,v1));
	assert(logical_getval(v1)==5);
	assert(logical_getval(v2)==5);
	assert(logical_getval(v3)==5);
	logical_destruct(v3,int_log_t,logical_void);
	logical_normalize(v1,int_log_t);
	logical_normalize(v2,int_log_t);
	assert(logical_testeq(v1,v2));
	logical_destruct(v2,int_log_t,logical_void);
	logical_normalize(v1,int_log_t);
	assert(logical_getval(v1)==5);
	logical_destruct(v1,int_log_t,logical_void);
	return 0;
}
