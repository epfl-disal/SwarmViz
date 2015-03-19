/*
 * sqrt.c
 *
 * Code generation for function 'sqrt'
 *
 * C source code generated on: Tue Dec 31 15:20:19 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "sqrt.h"

/* Function Definitions */
void b_sqrt(emxArray_real_T *x)
{
  int32_T i10;
  int32_T k;
  i10 = x->size[0] * x->size[1];
  for (k = 0; k < i10; k++) {
    x->data[(int32_T)(1.0 + (real_T)k) - 1] = sqrt(x->data[(int32_T)(1.0 +
      (real_T)k) - 1]);
  }
}

/* End of code generation (sqrt.c) */
