/*
 * power.c
 *
 * Code generation for function 'power'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "power.h"

/* Function Definitions */
void b_power(const real_T a[2000], real_T y[2000])
{
  int32_T k;
  for (k = 0; k < 2000; k++) {
    y[k] = a[k] * a[k];
  }
}

void c_power(const real_T a[1000000], real_T y[1000000])
{
  int32_T k;
  for (k = 0; k < 1000000; k++) {
    y[k] = muDoubleScalarPower(a[k], 3.0);
  }
}

void power(const real_T a[1000000], real_T y[1000000])
{
  int32_T k;
  for (k = 0; k < 1000000; k++) {
    y[k] = a[k] * a[k];
  }
}

/* End of code generation (power.c) */
