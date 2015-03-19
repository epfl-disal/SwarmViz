/*
 * sammon_types.h
 *
 * Code generation for function 'sammon'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

#ifndef __SAMMON_TYPES_H__
#define __SAMMON_TYPES_H__

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_sammonStackData
#define typedef_sammonStackData
typedef struct
{
    union
    {
        struct
        {
            real_T y[1000000];
            real_T dv6[1000000];
            real_T dv7[1000000];
        } f0;
        struct
        {
            real_T y[1000000];
            real_T b_y[1000000];
            real_T b[1000000];
            real_T c_y[1000000];
        } f1;
    } u1;
    struct
    {
        real_T D[1000000];
        real_T delta[1000000];
        real_T Dinv[1000000];
        real_T d[1000000];
        real_T dinv[1000000];
        real_T b_D[1000000];
        real_T y_old[2000];
        real_T deltaone[2000];
    } f2;
} sammonStackData;
#endif /*typedef_sammonStackData*/

#endif
/* End of code generation (sammon_types.h) */
