/*
 * sammon_emxutil.h
 *
 * Code generation for function 'sammon_emxutil'
 *
 * C source code generated on: Tue Dec 31 15:20:19 2013
 *
 */

#ifndef __SAMMON_EMXUTIL_H__
#define __SAMMON_EMXUTIL_H__
/* Include files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"

#include "rtwtypes.h"
#include "sammon_types.h"

/* Function Declarations */
#ifdef __cplusplus
extern "C" {
#endif
extern void b_emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
extern void emxEnsureCapacity(emxArray__common *emxArray, int32_T oldNumel, int32_T elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int32_T numDimensions);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (sammon_emxutil.h) */
