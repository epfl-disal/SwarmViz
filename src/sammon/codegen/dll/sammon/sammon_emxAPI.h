/*
 * sammon_emxAPI.h
 *
 * Code generation for function 'sammon_emxAPI'
 *
 * C source code generated on: Tue Dec 31 15:20:19 2013
 *
 */

#ifndef __SAMMON_EMXAPI_H__
#define __SAMMON_EMXAPI_H__
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
extern emxArray_real_T *emxCreateND_real_T(int32_T numDimensions, int32_T *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(real_T *data, int32_T numDimensions, int32_T *size);
extern emxArray_real_T *emxCreateWrapper_real_T(real_T *data, int32_T rows, int32_T cols);
extern emxArray_real_T *emxCreate_real_T(int32_T rows, int32_T cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);
#ifdef __cplusplus
}
#endif
#endif
/* End of code generation (sammon_emxAPI.h) */
