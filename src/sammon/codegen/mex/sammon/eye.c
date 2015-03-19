/*
 * eye.c
 *
 * Code generation for function 'eye'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "eye.h"

/* Function Definitions */
void eye(real_T I[1000000])
{
  int32_T i;
  memset(&I[0], 0, 1000000U * sizeof(real_T));
  for (i = 0; i < 1000; i++) {
    I[i + 1000 * i] = 1.0;
  }
}

/* End of code generation (eye.c) */
