/*
 * power.c
 *
 * Code generation for function 'power'
 *
 * C source code generated on: Tue Dec 31 15:20:19 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "power.h"
#include "sammon_emxutil.h"

/* Function Declarations */
static real_T rt_powd_snf(real_T u0, real_T u1);

/* Function Definitions */
static real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T d0;
  real_T d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = rtNaN;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

void b_power(const emxArray_real_T *a, emxArray_real_T *y)
{
  uint32_T uv1[2];
  int32_T i8;
  int32_T k;
  for (i8 = 0; i8 < 2; i8++) {
    uv1[i8] = (uint32_T)a->size[i8];
  }

  i8 = y->size[0] * y->size[1];
  y->size[0] = (int32_T)uv1[0];
  y->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)y, i8, (int32_T)sizeof(real_T));
  i8 = (int32_T)uv1[0] << 1;
  for (k = 0; k < i8; k++) {
    y->data[(int32_T)(1.0 + (real_T)k) - 1] = a->data[(int32_T)(1.0 + (real_T)k)
      - 1] * a->data[(int32_T)(1.0 + (real_T)k) - 1];
  }
}

void c_power(const emxArray_real_T *a, emxArray_real_T *y)
{
  uint32_T uv2[2];
  int32_T i9;
  int32_T k;
  for (i9 = 0; i9 < 2; i9++) {
    uv2[i9] = (uint32_T)a->size[i9];
  }

  i9 = y->size[0] * y->size[1];
  y->size[0] = (int32_T)uv2[0];
  y->size[1] = (int32_T)uv2[1];
  emxEnsureCapacity((emxArray__common *)y, i9, (int32_T)sizeof(real_T));
  i9 = (int32_T)uv2[0] * (int32_T)uv2[1];
  for (k = 0; k < i9; k++) {
    y->data[(int32_T)(1.0 + (real_T)k) - 1] = rt_powd_snf(a->data[(int32_T)(1.0
      + (real_T)k) - 1], 3.0);
  }
}

void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  uint32_T uv0[2];
  int32_T i4;
  int32_T k;
  for (i4 = 0; i4 < 2; i4++) {
    uv0[i4] = (uint32_T)a->size[i4];
  }

  i4 = y->size[0] * y->size[1];
  y->size[0] = (int32_T)uv0[0];
  y->size[1] = (int32_T)uv0[1];
  emxEnsureCapacity((emxArray__common *)y, i4, (int32_T)sizeof(real_T));
  i4 = (int32_T)uv0[0] * (int32_T)uv0[1];
  for (k = 0; k < i4; k++) {
    y->data[(int32_T)(1.0 + (real_T)k) - 1] = a->data[(int32_T)(1.0 + (real_T)k)
      - 1] * a->data[(int32_T)(1.0 + (real_T)k) - 1];
  }
}

/* End of code generation (power.c) */
