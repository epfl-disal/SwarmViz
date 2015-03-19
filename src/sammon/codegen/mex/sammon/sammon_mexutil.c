/*
 * sammon_mexutil.c
 *
 * Code generation for function 'sammon_mexutil'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "sammon_mexutil.h"

/* Function Definitions */
const mxArray *emlrt_marshallOut(real_T u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = mxCreateDoubleScalar(u);
  emlrtAssign(&y, m0);
  return y;
}

/* End of code generation (sammon_mexutil.c) */
