/*
 * sqrt.c
 *
 * Code generation for function 'sqrt'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "sqrt.h"

/* Variable Definitions */
static emlrtRSInfo y_emlrtRSI = { 14, "sqrt",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/elfun/sqrt.m" };

static emlrtRSInfo ab_emlrtRSI = { 20, "eml_error",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/eml_error.m" };

static emlrtRTEInfo emlrtRTEI = { 20, 5, "eml_error",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/eml_error.m" };

/* Function Declarations */
static void eml_error(void);

/* Function Definitions */
static void eml_error(void)
{
  static char_T cv0[4][1] = { { 's' }, { 'q' }, { 'r' }, { 't' } };

  emlrtPushRtStackR2012b(&ab_emlrtRSI, emlrtRootTLSGlobal);
  emlrtErrorWithMessageIdR2012b(emlrtRootTLSGlobal, &emlrtRTEI,
    "Coder:toolbox:ElFunDomainError", 3, 4, 4, cv0);
  emlrtPopRtStackR2012b(&ab_emlrtRSI, emlrtRootTLSGlobal);
}

void b_sqrt(real_T x[1000000])
{
  int32_T k;
  for (k = 0; k < 1000000; k++) {
    if (x[k] < 0.0) {
      emlrtPushRtStackR2012b(&y_emlrtRSI, emlrtRootTLSGlobal);
      eml_error();
      emlrtPopRtStackR2012b(&y_emlrtRSI, emlrtRootTLSGlobal);
    }
  }

  for (k = 0; k < 1000000; k++) {
    x[k] = muDoubleScalarSqrt(x[k]);
  }
}

/* End of code generation (sqrt.c) */
