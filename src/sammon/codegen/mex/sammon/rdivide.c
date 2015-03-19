/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "rdivide.h"

/* Function Definitions */
void b_rdivide(const real_T x[2000], const real_T y[2000], real_T z[2000])
{
  int32_T i;
  for (i = 0; i < 2000; i++) {
    z[i] = x[i] / y[i];
  }
}

void rdivide(real_T x, const real_T y[1000000], real_T z[1000000])
{
  int32_T i1;
  for (i1 = 0; i1 < 1000000; i1++) {
    z[i1] = x / y[i1];
  }
}

/* End of code generation (rdivide.c) */
