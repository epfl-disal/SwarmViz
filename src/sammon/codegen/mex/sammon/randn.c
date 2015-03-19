/*
 * randn.c
 *
 * Code generation for function 'randn'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "randn.h"
#include "sammon_mexutil.h"

/* Variable Definitions */
static emlrtRSInfo bb_emlrtRSI = { 88, "randn",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/randfun/randn.m" };

static emlrtMCInfo emlrtMCI = { 88, 9, "randn",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/randfun/randn.m" };

/* Function Declarations */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[2000]);
static const mxArray *b_randn(const mxArray *b, const mxArray *c, emlrtMCInfo
  *location);
static void e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[2000]);
static void emlrt_marshallIn(const mxArray *c_randn, const char_T *identifier,
  real_T y[2000]);

/* Function Definitions */
static void b_emlrt_marshallIn(const mxArray *u, const emlrtMsgIdentifier
  *parentId, real_T y[2000])
{
  e_emlrt_marshallIn(emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_randn(const mxArray *b, const mxArray *c, emlrtMCInfo
  *location)
{
  const mxArray *pArrays[2];
  const mxArray *m3;
  pArrays[0] = b;
  pArrays[1] = c;
  return emlrtCallMATLABR2012b(emlrtRootTLSGlobal, 1, &m3, 2, pArrays, "randn",
    TRUE, location);
}

static void e_emlrt_marshallIn(const mxArray *src, const emlrtMsgIdentifier
  *msgId, real_T ret[2000])
{
  int32_T iv3[2];
  int32_T i3;
  int32_T i4;
  for (i3 = 0; i3 < 2; i3++) {
    iv3[i3] = 1000 + -998 * i3;
  }

  emlrtCheckBuiltInR2012b(emlrtRootTLSGlobal, msgId, src, "double", FALSE, 2U,
    iv3);
  for (i3 = 0; i3 < 2; i3++) {
    for (i4 = 0; i4 < 1000; i4++) {
      ret[i4 + 1000 * i3] = (*(real_T (*)[2000])mxGetData(src))[i4 + 1000 * i3];
    }
  }

  emlrtDestroyArray(&src);
}

static void emlrt_marshallIn(const mxArray *c_randn, const char_T *identifier,
  real_T y[2000])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = identifier;
  thisId.fParent = NULL;
  b_emlrt_marshallIn(emlrtAlias(c_randn), &thisId, y);
  emlrtDestroyArray(&c_randn);
}

void randn(real_T r[2000])
{
  emlrtPushRtStackR2012b(&bb_emlrtRSI, emlrtRootTLSGlobal);
  emlrt_marshallIn(b_randn(emlrt_marshallOut(1000.0), emlrt_marshallOut(2.0),
    &emlrtMCI), "randn", r);
  emlrtPopRtStackR2012b(&bb_emlrtRSI, emlrtRootTLSGlobal);
}

/* End of code generation (randn.c) */
