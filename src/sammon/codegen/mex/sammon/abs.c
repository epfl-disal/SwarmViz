/*
 * abs.c
 *
 * Code generation for function 'abs'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "abs.h"

/* Function Definitions */
void b_abs(const real_T x[2000], real_T y[2000])
{
  int32_T k;
  for (k = 0; k < 2000; k++) {
    y[k] = muDoubleScalarAbs(x[k]);
  }
}

/* End of code generation (abs.c) */
