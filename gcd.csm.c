#include <stdint.h>

#include "cchr_csm.h"

CSM_TYPES_BEGIN
  CSM_TYPE(gcd_1)
CSM_TYPES_END

#define ARGTYPES_gcd_1(DEF,SEP) DEF(arg1,uint64_t)

CSM_DEF(gcd_1)

CSM_DEF_DATASTRUCT

CSM_CONS_BEGIN(gcd_1)
  CSM_RULE_BEGIN
    CSM_ENSURE(CSM_ARG(arg1)==0)
    CSM_KILLSELF
    CSM_STOP
  CSM_RULE_END
  CSM_RULE_BEGIN
    CSM_LOOP_BEGIN(gcd_1,J)
      CSM_ENSURE_DIFF(I,J)
      CSM_ENSURE(CSM_LARG(J,arg1)>=CSM_LARG(I,arg1))
#ifdef CSM_TAILREC
      CSM_SETARG(arg1,
      J_arg1=J_arg1-I_arg1;
      CSM_TAILREC
      CSM_KILLSELF
      CSM_ADD(gcd_1,J_arg1-I_arg1)
      CSM_STOP
    CSM_LOOP_END(gcd_1,J)
  CSM_RULE_END(I)
  CSM_MAKE
  CSM_RULE_BEGIN(J)
    CSM_LOOP_BEGIN(gcd_1,I)
      CSM_ENSURE_DIFF(I,J)
      CSM_ENSURE(J_arg1 >= I_arg1)
      CSM_KILL(J)
      CSM_ADD(gcd_1,J_arg1-I_arg1)
    CSM_LOOP_END(gcd_1,J)
  CSM_RULE_END(J)
CSM_CONS_END(gcd_1)

