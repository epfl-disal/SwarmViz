/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 * C source code generated on: Tue Dec 31 15:20:19 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "rdivide.h"
#include "sammon_emxutil.h"

/* Function Definitions */
void rdivide(const emxArray_real_T *y, emxArray_real_T *z)
{
  int32_T i5;
  int32_T loop_ub;
  i5 = z->size[0] * z->size[1];
  z->size[0] = y->size[0];
  z->size[1] = y->size[1];
  emxEnsureCapacity((emxArray__common *)z, i5, (int32_T)sizeof(real_T));
  loop_ub = y->size[0] * y->size[1];
  for (i5 = 0; i5 < loop_ub; i5++) {
    z->data[i5] = 1.0 / y->data[i5];
  }
}

/* End of code generation (rdivide.c) */
