/*
 * sum.h
 *
 * Code generation for function 'sum'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

#ifndef __SUM_H__
#define __SUM_H__
/* Include files */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"

#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "sammon_types.h"

/* Function Declarations */
extern real_T b_sum(const real_T x[1000000]);
#ifdef __WATCOMC__
#pragma aux b_sum value [8087];
#endif
extern void c_sum(const real_T x[2000], real_T y[1000]);
extern void d_sum(const real_T x[1000000], real_T y[1000]);
extern real_T e_sum(const real_T x[1000]);
#ifdef __WATCOMC__
#pragma aux e_sum value [8087];
#endif
extern void sum(const real_T x[1000000], real_T y[1000]);
#endif
/* End of code generation (sum.h) */
