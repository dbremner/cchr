#include <stdint.h>

#include "cchr_csm.h"

#define CONSLIST(DEF,SEP) DEF(gcd_1)
#define ARGLIST_gcd_1(DEF,SEP) DEF(arg1,uint64_t)
#define RULELIST_gcd_1(DEF,SEP) DEF(gcd_1_rule1) SEP DEF(gcd_1_rule2) SEP DEF(gcd_1_rule3)

#define CODELIST_gcd_1_rule1 \
  CSM_ENSURE(CSM_ARG(arg1)==0, \
    CSM_KILLSELF \
    CSM_END \
  ) \

#define CODELIST_gcd_1_rule2 \
  CSM_LOOP(gcd_1,I, \
    CSM_ENSURE_DIFF(I, \
      CSM_ENSURE(CSM_ARG(arg1)>=CSM_LARG(gcd_1,I,arg1), \
        CSM_KILLSELF \
        CSM_ADD(gcd_1,CSM_ARG(arg1)-CSM_LARG(gcd_1,I,arg1)) \
        CSM_END \
      ) \
    ) \
  )

#define CODELIST_gcd_1_rule3 \
  CSM_MAKE \
  CSM_LOOP(gcd_1,J, \
    CSM_ENSURE_DIFF(J, \
      CSM_ENSURE(CSM_LARG(gcd_1,J,arg1) >= CSM_ARG(arg1), \
        CSM_KILL(J) \
        CSM_ADD(gcd_1,CSM_LARG(gcd_1,J,arg1)-CSM_ARG(arg1)) \
      ) \
    ) \
  )

CSM_START

