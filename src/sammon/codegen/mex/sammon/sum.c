/*
 * sum.c
 *
 * Code generation for function 'sum'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "sum.h"

/* Function Definitions */
real_T b_sum(const real_T x[1000000])
{
  real_T y;
  int32_T k;
  y = x[0];
  for (k = 0; k < 999999; k++) {
    y += x[k + 1];
  }

  return y;
}

void c_sum(const real_T x[2000], real_T y[1000])
{
  int32_T iy;
  int32_T ixstart;
  int32_T j;
  iy = -1;
  ixstart = 999;
  for (j = 0; j < 1000; j++) {
    ixstart++;
    iy++;
    y[iy] = x[ixstart - 1000] + x[ixstart];
  }
}

void d_sum(const real_T x[1000000], real_T y[1000])
{
  int32_T ix;
  int32_T iy;
  int32_T i;
  int32_T ixstart;
  real_T s;
  ix = -1;
  iy = -1;
  for (i = 0; i < 1000; i++) {
    ixstart = ix + 1;
    ix++;
    s = x[ixstart];
    for (ixstart = 0; ixstart < 999; ixstart++) {
      ix++;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

real_T e_sum(const real_T x[1000])
{
  real_T y;
  int32_T k;
  y = x[0];
  for (k = 0; k < 999; k++) {
    y += x[k + 1];
  }

  return y;
}

void sum(const real_T x[1000000], real_T y[1000])
{
  int32_T iy;
  int32_T ixstart;
  int32_T j;
  int32_T ix;
  real_T s;
  int32_T k;
  iy = -1;
  ixstart = -1;
  for (j = 0; j < 1000; j++) {
    ixstart++;
    ix = ixstart;
    s = x[ixstart];
    for (k = 0; k < 999; k++) {
      ix += 1000;
      s += x[ix];
    }

    iy++;
    y[iy] = s;
  }
}

/* End of code generation (sum.c) */
