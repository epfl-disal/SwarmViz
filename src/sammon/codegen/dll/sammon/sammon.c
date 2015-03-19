/*
 * sammon.c
 *
 * Code generation for function 'sammon'
 *
 * C source code generated on: Tue Dec 31 15:20:19 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "sammon_emxutil.h"
#include "sum.h"
#include "power.h"
#include "rdivide.h"
#include "sqrt.h"
#include "eye.h"
#include "randn.h"

/* Function Declarations */
static void b_euclid(const emxArray_real_T *x, const emxArray_real_T *y,
                     emxArray_real_T *d);
static void euclid(const emxArray_real_T *x, const emxArray_real_T *y,
                   emxArray_real_T *d);

/* Function Definitions */
static void b_euclid(const emxArray_real_T *x, const emxArray_real_T *y,
                     emxArray_real_T *d)
{
  emxArray_real_T *a;
  emxArray_real_T *b;
  emxArray_real_T *r2;
  emxArray_real_T *r3;
  int32_T i7;
  int32_T unnamed_idx_1;
  int32_T br;
  emxArray_real_T *b_b;
  int32_T ar;
  emxArray_real_T *b_y;
  uint32_T unnamed_idx_0;
  uint32_T b_unnamed_idx_1;
  int32_T cr;
  int32_T ic;
  int32_T ib;
  int32_T ia;
  emxArray_real_T *b_a;
  emxArray_real_T *r4;
  b_emxInit_real_T(&a, 1);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&r2, 2);
  b_emxInit_real_T(&r3, 1);

  /*  all done */
  b_power(x, r2);
  b_sum(r2, a);
  b_power(y, r2);
  b_sum(r2, r3);
  i7 = b->size[0] * b->size[1];
  b->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)b, i7, (int32_T)sizeof(real_T));
  unnamed_idx_1 = r3->size[0];
  i7 = b->size[0] * b->size[1];
  b->size[1] = unnamed_idx_1;
  emxEnsureCapacity((emxArray__common *)b, i7, (int32_T)sizeof(real_T));
  br = r3->size[0];
  emxFree_real_T(&r2);
  for (i7 = 0; i7 < br; i7++) {
    b->data[i7] = r3->data[i7];
  }

  emxFree_real_T(&r3);
  emxInit_real_T(&b_b, 2);
  i7 = b_b->size[0] * b_b->size[1];
  b_b->size[0] = 2;
  b_b->size[1] = y->size[0];
  emxEnsureCapacity((emxArray__common *)b_b, i7, (int32_T)sizeof(real_T));
  br = y->size[0];
  for (i7 = 0; i7 < br; i7++) {
    for (ar = 0; ar < 2; ar++) {
      b_b->data[ar + b_b->size[0] * i7] = y->data[i7 + y->size[0] * ar];
    }
  }

  emxInit_real_T(&b_y, 2);
  unnamed_idx_0 = (uint32_T)x->size[0];
  b_unnamed_idx_1 = (uint32_T)b_b->size[1];
  i7 = b_y->size[0] * b_y->size[1];
  b_y->size[0] = (int32_T)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)b_y, i7, (int32_T)sizeof(real_T));
  i7 = b_y->size[0] * b_y->size[1];
  b_y->size[1] = (int32_T)b_unnamed_idx_1;
  emxEnsureCapacity((emxArray__common *)b_y, i7, (int32_T)sizeof(real_T));
  br = (int32_T)unnamed_idx_0 * (int32_T)b_unnamed_idx_1;
  for (i7 = 0; i7 < br; i7++) {
    b_y->data[i7] = 0.0;
  }

  if ((x->size[0] == 0) || (b_b->size[1] == 0)) {
  } else {
    unnamed_idx_1 = x->size[0] * (b_b->size[1] - 1);
    cr = 0;
    while ((x->size[0] > 0) && (cr <= unnamed_idx_1)) {
      i7 = cr + x->size[0];
      for (ic = cr; ic + 1 <= i7; ic++) {
        b_y->data[ic] = 0.0;
      }

      cr += x->size[0];
    }

    br = 0;
    cr = 0;
    while ((x->size[0] > 0) && (cr <= unnamed_idx_1)) {
      ar = -1;
      for (ib = br; ib + 1 <= br + 2; ib++) {
        if (b_b->data[ib] != 0.0) {
          ia = ar;
          i7 = cr + x->size[0];
          for (ic = cr; ic + 1 <= i7; ic++) {
            ia++;
            b_y->data[ic] += b_b->data[ib] * x->data[ia];
          }
        }

        ar += x->size[0];
      }

      br += 2;
      cr += x->size[0];
    }
  }

  emxFree_real_T(&b_b);
  emxInit_real_T(&b_a, 2);
  emxInit_real_T(&r4, 2);
  unnamed_idx_1 = y->size[0];
  cr = x->size[0];
  i7 = b_a->size[0] * b_a->size[1];
  b_a->size[0] = a->size[0];
  b_a->size[1] = unnamed_idx_1;
  emxEnsureCapacity((emxArray__common *)b_a, i7, (int32_T)sizeof(real_T));
  br = a->size[0];
  for (i7 = 0; i7 < br; i7++) {
    for (ar = 0; ar < unnamed_idx_1; ar++) {
      b_a->data[i7 + b_a->size[0] * ar] = a->data[i7];
    }
  }

  emxFree_real_T(&a);
  i7 = r4->size[0] * r4->size[1];
  r4->size[0] = cr;
  r4->size[1] = b->size[1];
  emxEnsureCapacity((emxArray__common *)r4, i7, (int32_T)sizeof(real_T));
  for (i7 = 0; i7 < cr; i7++) {
    br = b->size[1];
    for (ar = 0; ar < br; ar++) {
      r4->data[i7 + r4->size[0] * ar] = b->data[b->size[0] * ar];
    }
  }

  emxFree_real_T(&b);
  i7 = d->size[0] * d->size[1];
  d->size[0] = b_a->size[0];
  d->size[1] = b_a->size[1];
  emxEnsureCapacity((emxArray__common *)d, i7, (int32_T)sizeof(real_T));
  br = b_a->size[1];
  for (i7 = 0; i7 < br; i7++) {
    unnamed_idx_1 = b_a->size[0];
    for (ar = 0; ar < unnamed_idx_1; ar++) {
      d->data[ar + d->size[0] * i7] = (b_a->data[ar + b_a->size[0] * i7] +
        r4->data[ar + r4->size[0] * i7]) - 2.0 * b_y->data[ar + b_y->size[0] *
        i7];
    }
  }

  emxFree_real_T(&r4);
  emxFree_real_T(&b_a);
  emxFree_real_T(&b_y);
  b_sqrt(d);
}

static void euclid(const emxArray_real_T *x, const emxArray_real_T *y,
                   emxArray_real_T *d)
{
  emxArray_real_T *a;
  emxArray_real_T *b;
  emxArray_real_T *b_b;
  emxArray_real_T *r0;
  int32_T i2;
  int32_T unnamed_idx_1;
  int32_T ar;
  int32_T i3;
  emxArray_real_T *b_y;
  int32_T cr;
  int32_T br;
  uint32_T unnamed_idx_0;
  uint32_T b_unnamed_idx_1;
  int32_T ic;
  int32_T ib;
  int32_T ia;
  emxArray_real_T *b_a;
  emxArray_real_T *r1;
  b_emxInit_real_T(&a, 1);
  emxInit_real_T(&b, 2);
  emxInit_real_T(&b_b, 2);
  b_emxInit_real_T(&r0, 1);

  /*  all done */
  power(x, b_b);
  sum(b_b, a);
  power(y, b_b);
  sum(b_b, r0);
  i2 = b->size[0] * b->size[1];
  b->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)b, i2, (int32_T)sizeof(real_T));
  unnamed_idx_1 = r0->size[0];
  i2 = b->size[0] * b->size[1];
  b->size[1] = unnamed_idx_1;
  emxEnsureCapacity((emxArray__common *)b, i2, (int32_T)sizeof(real_T));
  ar = r0->size[0];
  for (i2 = 0; i2 < ar; i2++) {
    b->data[i2] = r0->data[i2];
  }

  emxFree_real_T(&r0);
  i2 = b_b->size[0] * b_b->size[1];
  b_b->size[0] = y->size[1];
  b_b->size[1] = y->size[0];
  emxEnsureCapacity((emxArray__common *)b_b, i2, (int32_T)sizeof(real_T));
  ar = y->size[0];
  for (i2 = 0; i2 < ar; i2++) {
    unnamed_idx_1 = y->size[1];
    for (i3 = 0; i3 < unnamed_idx_1; i3++) {
      b_b->data[i3 + b_b->size[0] * i2] = y->data[i2 + y->size[0] * i3];
    }
  }

  emxInit_real_T(&b_y, 2);
  if ((x->size[1] == 1) || (b_b->size[0] == 1)) {
    i2 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = x->size[0];
    b_y->size[1] = b_b->size[1];
    emxEnsureCapacity((emxArray__common *)b_y, i2, (int32_T)sizeof(real_T));
    ar = x->size[0];
    for (i2 = 0; i2 < ar; i2++) {
      unnamed_idx_1 = b_b->size[1];
      for (i3 = 0; i3 < unnamed_idx_1; i3++) {
        b_y->data[i2 + b_y->size[0] * i3] = 0.0;
        cr = x->size[1];
        for (br = 0; br < cr; br++) {
          b_y->data[i2 + b_y->size[0] * i3] += x->data[i2 + x->size[0] * br] *
            b_b->data[br + b_b->size[0] * i3];
        }
      }
    }
  } else {
    unnamed_idx_0 = (uint32_T)x->size[0];
    b_unnamed_idx_1 = (uint32_T)b_b->size[1];
    i2 = b_y->size[0] * b_y->size[1];
    b_y->size[0] = (int32_T)unnamed_idx_0;
    emxEnsureCapacity((emxArray__common *)b_y, i2, (int32_T)sizeof(real_T));
    i2 = b_y->size[0] * b_y->size[1];
    b_y->size[1] = (int32_T)b_unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)b_y, i2, (int32_T)sizeof(real_T));
    ar = (int32_T)unnamed_idx_0 * (int32_T)b_unnamed_idx_1;
    for (i2 = 0; i2 < ar; i2++) {
      b_y->data[i2] = 0.0;
    }

    if ((x->size[0] == 0) || (b_b->size[1] == 0)) {
    } else {
      unnamed_idx_1 = x->size[0] * (b_b->size[1] - 1);
      cr = 0;
      while ((x->size[0] > 0) && (cr <= unnamed_idx_1)) {
        i2 = cr + x->size[0];
        for (ic = cr; ic + 1 <= i2; ic++) {
          b_y->data[ic] = 0.0;
        }

        cr += x->size[0];
      }

      br = 0;
      cr = 0;
      while ((x->size[0] > 0) && (cr <= unnamed_idx_1)) {
        ar = -1;
        i2 = br + x->size[1];
        for (ib = br; ib + 1 <= i2; ib++) {
          if (b_b->data[ib] != 0.0) {
            ia = ar;
            i3 = cr + x->size[0];
            for (ic = cr; ic + 1 <= i3; ic++) {
              ia++;
              b_y->data[ic] += b_b->data[ib] * x->data[ia];
            }
          }

          ar += x->size[0];
        }

        br += x->size[1];
        cr += x->size[0];
      }
    }
  }

  emxFree_real_T(&b_b);
  emxInit_real_T(&b_a, 2);
  emxInit_real_T(&r1, 2);
  unnamed_idx_1 = y->size[0];
  cr = x->size[0];
  i2 = b_a->size[0] * b_a->size[1];
  b_a->size[0] = a->size[0];
  b_a->size[1] = unnamed_idx_1;
  emxEnsureCapacity((emxArray__common *)b_a, i2, (int32_T)sizeof(real_T));
  ar = a->size[0];
  for (i2 = 0; i2 < ar; i2++) {
    for (i3 = 0; i3 < unnamed_idx_1; i3++) {
      b_a->data[i2 + b_a->size[0] * i3] = a->data[i2];
    }
  }

  emxFree_real_T(&a);
  i2 = r1->size[0] * r1->size[1];
  r1->size[0] = cr;
  r1->size[1] = b->size[1];
  emxEnsureCapacity((emxArray__common *)r1, i2, (int32_T)sizeof(real_T));
  for (i2 = 0; i2 < cr; i2++) {
    ar = b->size[1];
    for (i3 = 0; i3 < ar; i3++) {
      r1->data[i2 + r1->size[0] * i3] = b->data[b->size[0] * i3];
    }
  }

  emxFree_real_T(&b);
  i2 = d->size[0] * d->size[1];
  d->size[0] = b_a->size[0];
  d->size[1] = b_a->size[1];
  emxEnsureCapacity((emxArray__common *)d, i2, (int32_T)sizeof(real_T));
  ar = b_a->size[1];
  for (i2 = 0; i2 < ar; i2++) {
    unnamed_idx_1 = b_a->size[0];
    for (i3 = 0; i3 < unnamed_idx_1; i3++) {
      d->data[i3 + d->size[0] * i2] = (b_a->data[i3 + b_a->size[0] * i2] +
        r1->data[i3 + r1->size[0] * i2]) - 2.0 * b_y->data[i3 + b_y->size[0] *
        i2];
    }
  }

  emxFree_real_T(&r1);
  emxFree_real_T(&b_a);
  emxFree_real_T(&b_y);
  b_sqrt(d);
}

void sammon(const emxArray_real_T *x, emxArray_real_T *y)
{
  emxArray_real_T *D;
  emxArray_real_T *delta;
  int32_T i0;
  int32_T b_D;
  int32_T br;
  emxArray_real_T *Dinv;
  emxArray_real_T *d;
  emxArray_real_T *dinv;
  emxArray_real_T *c_D;
  emxArray_real_T *b_delta;
  emxArray_real_T *b_x;
  real_T E;
  int32_T i;
  emxArray_real_T *deltaone;
  emxArray_real_T *g;
  emxArray_real_T *y2;
  emxArray_real_T *H;
  emxArray_real_T *s;
  emxArray_real_T *C;
  emxArray_real_T *b_C;
  emxArray_real_T *c_delta;
  emxArray_real_T *d_D;
  emxArray_real_T *b_deltaone;
  boolean_T exitg1;
  boolean_T guard2 = FALSE;
  uint32_T unnamed_idx_0;
  int32_T ic;
  int32_T ar;
  int32_T ib;
  int32_T ia;
  int32_T i1;
  boolean_T guard1 = FALSE;
  int32_T exitg3;
  boolean_T exitg2;
  int32_T b_y[2];
  real_T E_new;
  real_T u1;
  emxInit_real_T(&D, 2);
  emxInit_real_T(&delta, 2);

  /* #codgen */
  /*  */
  /*  SAMMON - apply Sammon's nonlinear mapping  */
  /*  */
  /*     Y = SAMMON(X) applies Sammon's nonlinear mapping procedure on */
  /*     multivariate data X, where each row represents a pattern and each column */
  /*     represents a feature.  On completion, Y contains the corresponding */
  /*     co-ordinates of each point on the map.  By default, a two-dimensional */
  /*     map is created.  Note if X contains any duplicated rows, SAMMON will */
  /*     fail (ungracefully).  */
  /*  */
  /*     [Y,E] = SAMMON(X) also returns the value of the cost function in E (i.e. */
  /*     the stress of the mapping). */
  /*  */
  /*     An N-dimensional output map is generated by Y = SAMMON(X,N) . */
  /*  */
  /*     A set of optimisation options can also be specified using a third */
  /*     argument, Y = SAMMON(X,N,OPTS) , where OPTS is a structure with fields: */
  /*  */
  /*        MaxIter        - maximum number of iterations */
  /*        TolFun         - relative tolerance on objective function */
  /*        MaxHalves      - maximum number of step halvings */
  /*        Input          - {'raw','distance'} if set to 'distance', X is  */
  /*                         interpreted as a matrix of pairwise distances. */
  /*        Display        - {'off', 'on', 'iter'} */
  /*        Initialisation - {'pca', 'random'} */
  /*  */
  /*     The default options structure can be retrieved by calling SAMMON with */
  /*     no parameters. */
  /*  */
  /*     References : */
  /*  */
  /*        [1] Sammon, John W. Jr., "A Nonlinear Mapping for Data Structure */
  /*            Analysis", IEEE Transactions on Computers, vol. C-18, no. 5, */
  /*            pp 401-409, May 1969. */
  /*  */
  /*     See also : SAMMON_TEST */
  /*  */
  /*  File        : sammon.m */
  /*  */
  /*  Date        : Monday 12th November 2007. */
  /*  */
  /*  Author      : Gavin C. Cawley and Nicola L. C. Talbot */
  /*  */
  /*  Description : Simple vectorised MATLAB implementation of Sammon's non-linear */
  /*                mapping algorithm [1]. */
  /*  */
  /*  References  : [1] Sammon, John W. Jr., "A Nonlinear Mapping for Data */
  /*                    Structure Analysis", IEEE Transactions on Computers, */
  /*                    vol. C-18, no. 5, pp 401-409, May 1969. */
  /*  */
  /*  History     : 10/08/2004 - v1.00 */
  /*                11/08/2004 - v1.10 Hessian made positive semidefinite */
  /*                13/08/2004 - v1.11 minor optimisation */
  /*                12/11/2007 - v1.20 initialisation using the first n principal */
  /*                                   components. */
  /*  */
  /*  Thanks      : Dr Nick Hamilton (nick@maths.uq.edu.au) for supplying the */
  /*                code for implementing initialisation using the first n */
  /*                principal components (introduced in v1.20). */
  /*  */
  /*  To do       : The current version does not take advantage of the symmetry */
  /*                of the distance matrix in order to allow for easy */
  /*                vectorisation.  This may not be a good choice for very large */
  /*                datasets, so perhaps one day I'll get around to doing a MEX */
  /*                version using the BLAS library etc. for very large datasets. */
  /*  */
  /*  Copyright   : (c) Dr Gavin C. Cawley, November 2007. */
  /*  */
  /*     This program is free software; you can redistribute it and/or modify */
  /*     it under the terms of the GNU General Public License as published by */
  /*     the Free Software Foundation; either version 2 of the License, or */
  /*     (at your option) any later version. */
  /*  */
  /*     This program is distributed in the hope that it will be useful, */
  /*     but WITHOUT ANY WARRANTY; without even the implied warranty of */
  /*     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
  /*     GNU General Public License for more details. */
  /*  */
  /*     You should have received a copy of the GNU General Public License */
  /*     along with this program; if not, write to the Free Software */
  /*     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */
  /*  */
  /*  use the default options structure */
  /*  create distance matrix unless given by parameters */
  euclid(x, x, D);

  /*  remaining initialisation */
  eye(x->size[0], delta);
  i0 = D->size[0] * D->size[1];
  emxEnsureCapacity((emxArray__common *)D, i0, (int32_T)sizeof(real_T));
  b_D = D->size[0];
  br = D->size[1];
  br *= b_D;
  for (i0 = 0; i0 < br; i0++) {
    D->data[i0] += delta->data[i0];
  }

  emxInit_real_T(&Dinv, 2);
  emxInit_real_T(&d, 2);
  rdivide(D, Dinv);
  randn(x->size[0], y);
  b_euclid(y, y, d);
  eye(x->size[0], delta);
  i0 = d->size[0] * d->size[1];
  emxEnsureCapacity((emxArray__common *)d, i0, (int32_T)sizeof(real_T));
  b_D = d->size[0];
  br = d->size[1];
  br *= b_D;
  for (i0 = 0; i0 < br; i0++) {
    d->data[i0] += delta->data[i0];
  }

  emxInit_real_T(&dinv, 2);
  emxInit_real_T(&c_D, 2);
  rdivide(d, dinv);
  i0 = c_D->size[0] * c_D->size[1];
  c_D->size[0] = D->size[0];
  c_D->size[1] = D->size[1];
  emxEnsureCapacity((emxArray__common *)c_D, i0, (int32_T)sizeof(real_T));
  br = D->size[0] * D->size[1];
  for (i0 = 0; i0 < br; i0++) {
    c_D->data[i0] = D->data[i0] - d->data[i0];
  }

  emxInit_real_T(&b_delta, 2);
  power(c_D, delta);
  i0 = b_delta->size[0] * b_delta->size[1];
  b_delta->size[0] = delta->size[0];
  b_delta->size[1] = delta->size[1];
  emxEnsureCapacity((emxArray__common *)b_delta, i0, (int32_T)sizeof(real_T));
  br = delta->size[0] * delta->size[1];
  emxFree_real_T(&c_D);
  for (i0 = 0; i0 < br; i0++) {
    b_delta->data[i0] = delta->data[i0] * Dinv->data[i0];
  }

  emxInit_real_T(&b_x, 2);
  c_sum(b_delta, b_x);
  E = d_sum(b_x);

  /*  get on with it */
  i = 0;
  emxFree_real_T(&b_delta);
  emxInit_real_T(&deltaone, 2);
  emxInit_real_T(&g, 2);
  emxInit_real_T(&y2, 2);
  emxInit_real_T(&H, 2);
  b_emxInit_real_T(&s, 1);
  emxInit_real_T(&C, 2);
  emxInit_real_T(&b_C, 2);
  emxInit_real_T(&c_delta, 2);
  emxInit_real_T(&d_D, 2);
  b_emxInit_real_T(&b_deltaone, 1);
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (i < 500)) {
    /*  compute gradient, Hessian and search direction (note it is actually */
    /*  1/4 of the gradient and Hessian, but the step size is just the ratio */
    /*  of the gradient and the diagonal of the Hessian so it doesn't matter). */
    i0 = delta->size[0] * delta->size[1];
    delta->size[0] = dinv->size[0];
    delta->size[1] = dinv->size[1];
    emxEnsureCapacity((emxArray__common *)delta, i0, (int32_T)sizeof(real_T));
    br = dinv->size[0] * dinv->size[1];
    for (i0 = 0; i0 < br; i0++) {
      delta->data[i0] = dinv->data[i0] - Dinv->data[i0];
    }

    guard2 = FALSE;
    if (delta->size[1] == 1) {
      guard2 = TRUE;
    } else {
      b_D = x->size[0];
      if (b_D == 1) {
        guard2 = TRUE;
      } else {
        unnamed_idx_0 = (uint32_T)delta->size[0];
        i0 = deltaone->size[0] * deltaone->size[1];
        deltaone->size[0] = (int32_T)unnamed_idx_0;
        deltaone->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)deltaone, i0, (int32_T)sizeof
                          (real_T));
        br = (int32_T)unnamed_idx_0 << 1;
        for (i0 = 0; i0 < br; i0++) {
          deltaone->data[i0] = 0.0;
        }

        if (delta->size[0] == 0) {
        } else {
          b_D = 0;
          while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
            i0 = b_D + delta->size[0];
            for (ic = b_D; ic + 1 <= i0; ic++) {
              deltaone->data[ic] = 0.0;
            }

            b_D += delta->size[0];
          }

          br = 0;
          b_D = 0;
          while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
            ar = 0;
            i0 = br + delta->size[1];
            for (ib = br + 1; ib <= i0; ib++) {
              ia = ar;
              i1 = b_D + delta->size[0];
              for (ic = b_D; ic + 1 <= i1; ic++) {
                ia++;
                deltaone->data[ic] += delta->data[ia - 1];
              }

              ar += delta->size[0];
            }

            br += delta->size[1];
            b_D += delta->size[0];
          }
        }
      }
    }

    if (guard2 == TRUE) {
      i0 = deltaone->size[0] * deltaone->size[1];
      deltaone->size[0] = delta->size[0];
      deltaone->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)deltaone, i0, (int32_T)sizeof(real_T));
      br = delta->size[0];
      for (i0 = 0; i0 < br; i0++) {
        for (i1 = 0; i1 < 2; i1++) {
          deltaone->data[i0 + deltaone->size[0] * i1] = 0.0;
          ar = delta->size[1];
          for (b_D = 0; b_D < ar; b_D++) {
            deltaone->data[i0 + deltaone->size[0] * i1] += delta->data[i0 +
              delta->size[0] * b_D];
          }
        }
      }
    }

    if ((delta->size[1] == 1) || (y->size[0] == 1)) {
      i0 = g->size[0] * g->size[1];
      g->size[0] = delta->size[0];
      g->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)g, i0, (int32_T)sizeof(real_T));
      br = delta->size[0];
      for (i0 = 0; i0 < br; i0++) {
        for (i1 = 0; i1 < 2; i1++) {
          g->data[i0 + g->size[0] * i1] = 0.0;
          ar = delta->size[1];
          for (b_D = 0; b_D < ar; b_D++) {
            g->data[i0 + g->size[0] * i1] += delta->data[i0 + delta->size[0] *
              b_D] * y->data[b_D + y->size[0] * i1];
          }
        }
      }
    } else {
      unnamed_idx_0 = (uint32_T)delta->size[0];
      i0 = g->size[0] * g->size[1];
      g->size[0] = (int32_T)unnamed_idx_0;
      g->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)g, i0, (int32_T)sizeof(real_T));
      br = (int32_T)unnamed_idx_0 << 1;
      for (i0 = 0; i0 < br; i0++) {
        g->data[i0] = 0.0;
      }

      if (delta->size[0] == 0) {
      } else {
        b_D = 0;
        while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
          i0 = b_D + delta->size[0];
          for (ic = b_D; ic + 1 <= i0; ic++) {
            g->data[ic] = 0.0;
          }

          b_D += delta->size[0];
        }

        br = 0;
        b_D = 0;
        while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
          ar = 0;
          i0 = br + delta->size[1];
          for (ib = br; ib + 1 <= i0; ib++) {
            if (y->data[ib] != 0.0) {
              ia = ar;
              i1 = b_D + delta->size[0];
              for (ic = b_D; ic + 1 <= i1; ic++) {
                ia++;
                g->data[ic] += y->data[ib] * delta->data[ia - 1];
              }
            }

            ar += delta->size[0];
          }

          br += delta->size[1];
          b_D += delta->size[0];
        }
      }
    }

    i0 = g->size[0] * g->size[1];
    g->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)g, i0, (int32_T)sizeof(real_T));
    b_D = g->size[0];
    br = g->size[1];
    br *= b_D;
    for (i0 = 0; i0 < br; i0++) {
      g->data[i0] -= y->data[i0] * deltaone->data[i0];
    }

    c_power(dinv, delta);
    b_power(y, y2);
    if ((delta->size[1] == 1) || (y2->size[0] == 1)) {
      i0 = H->size[0] * H->size[1];
      H->size[0] = delta->size[0];
      H->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)H, i0, (int32_T)sizeof(real_T));
      br = delta->size[0];
      for (i0 = 0; i0 < br; i0++) {
        for (i1 = 0; i1 < 2; i1++) {
          H->data[i0 + H->size[0] * i1] = 0.0;
          ar = delta->size[1];
          for (b_D = 0; b_D < ar; b_D++) {
            H->data[i0 + H->size[0] * i1] += delta->data[i0 + delta->size[0] *
              b_D] * y2->data[b_D + y2->size[0] * i1];
          }
        }
      }
    } else {
      unnamed_idx_0 = (uint32_T)delta->size[0];
      i0 = H->size[0] * H->size[1];
      H->size[0] = (int32_T)unnamed_idx_0;
      H->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)H, i0, (int32_T)sizeof(real_T));
      br = (int32_T)unnamed_idx_0 << 1;
      for (i0 = 0; i0 < br; i0++) {
        H->data[i0] = 0.0;
      }

      if (delta->size[0] == 0) {
      } else {
        b_D = 0;
        while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
          i0 = b_D + delta->size[0];
          for (ic = b_D; ic + 1 <= i0; ic++) {
            H->data[ic] = 0.0;
          }

          b_D += delta->size[0];
        }

        br = 0;
        b_D = 0;
        while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
          ar = 0;
          i0 = br + delta->size[1];
          for (ib = br; ib + 1 <= i0; ib++) {
            if (y2->data[ib] != 0.0) {
              ia = ar;
              i1 = b_D + delta->size[0];
              for (ic = b_D; ic + 1 <= i1; ic++) {
                ia++;
                H->data[ic] += y2->data[ib] * delta->data[ia - 1];
              }
            }

            ar += delta->size[0];
          }

          br += delta->size[1];
          b_D += delta->size[0];
        }
      }
    }

    if ((delta->size[1] == 1) || (y->size[0] == 1)) {
      i0 = C->size[0] * C->size[1];
      C->size[0] = delta->size[0];
      C->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)C, i0, (int32_T)sizeof(real_T));
      br = delta->size[0];
      for (i0 = 0; i0 < br; i0++) {
        for (i1 = 0; i1 < 2; i1++) {
          C->data[i0 + C->size[0] * i1] = 0.0;
          ar = delta->size[1];
          for (b_D = 0; b_D < ar; b_D++) {
            C->data[i0 + C->size[0] * i1] += delta->data[i0 + delta->size[0] *
              b_D] * y->data[b_D + y->size[0] * i1];
          }
        }
      }
    } else {
      unnamed_idx_0 = (uint32_T)delta->size[0];
      i0 = C->size[0] * C->size[1];
      C->size[0] = (int32_T)unnamed_idx_0;
      C->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)C, i0, (int32_T)sizeof(real_T));
      br = (int32_T)unnamed_idx_0 << 1;
      for (i0 = 0; i0 < br; i0++) {
        C->data[i0] = 0.0;
      }

      if (delta->size[0] == 0) {
      } else {
        b_D = 0;
        while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
          i0 = b_D + delta->size[0];
          for (ic = b_D; ic + 1 <= i0; ic++) {
            C->data[ic] = 0.0;
          }

          b_D += delta->size[0];
        }

        br = 0;
        b_D = 0;
        while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
          ar = 0;
          i0 = br + delta->size[1];
          for (ib = br; ib + 1 <= i0; ib++) {
            if (y->data[ib] != 0.0) {
              ia = ar;
              i1 = b_D + delta->size[0];
              for (ic = b_D; ic + 1 <= i1; ic++) {
                ia++;
                C->data[ic] += y->data[ib] * delta->data[ia - 1];
              }
            }

            ar += delta->size[0];
          }

          br += delta->size[1];
          b_D += delta->size[0];
        }
      }
    }

    guard1 = FALSE;
    if (delta->size[1] == 1) {
      guard1 = TRUE;
    } else {
      b_D = x->size[0];
      if (b_D == 1) {
        guard1 = TRUE;
      } else {
        unnamed_idx_0 = (uint32_T)delta->size[0];
        i0 = b_C->size[0] * b_C->size[1];
        b_C->size[0] = (int32_T)unnamed_idx_0;
        b_C->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)b_C, i0, (int32_T)sizeof(real_T));
        br = (int32_T)unnamed_idx_0 << 1;
        for (i0 = 0; i0 < br; i0++) {
          b_C->data[i0] = 0.0;
        }

        if (delta->size[0] == 0) {
        } else {
          b_D = 0;
          while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
            i0 = b_D + delta->size[0];
            for (ic = b_D; ic + 1 <= i0; ic++) {
              b_C->data[ic] = 0.0;
            }

            b_D += delta->size[0];
          }

          br = 0;
          b_D = 0;
          while ((delta->size[0] > 0) && (b_D <= delta->size[0])) {
            ar = 0;
            i0 = br + delta->size[1];
            for (ib = br + 1; ib <= i0; ib++) {
              ia = ar;
              i1 = b_D + delta->size[0];
              for (ic = b_D; ic + 1 <= i1; ic++) {
                ia++;
                b_C->data[ic] += delta->data[ia - 1];
              }

              ar += delta->size[0];
            }

            br += delta->size[1];
            b_D += delta->size[0];
          }
        }
      }
    }

    if (guard1 == TRUE) {
      i0 = b_C->size[0] * b_C->size[1];
      b_C->size[0] = delta->size[0];
      b_C->size[1] = 2;
      emxEnsureCapacity((emxArray__common *)b_C, i0, (int32_T)sizeof(real_T));
      br = delta->size[0];
      for (i0 = 0; i0 < br; i0++) {
        for (i1 = 0; i1 < 2; i1++) {
          b_C->data[i0 + b_C->size[0] * i1] = 0.0;
          ar = delta->size[1];
          for (b_D = 0; b_D < ar; b_D++) {
            b_C->data[i0 + b_C->size[0] * i1] += delta->data[i0 + delta->size[0]
              * b_D];
          }
        }
      }
    }

    i0 = H->size[0] * H->size[1];
    H->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)H, i0, (int32_T)sizeof(real_T));
    b_D = H->size[0];
    br = H->size[1];
    br *= b_D;
    for (i0 = 0; i0 < br; i0++) {
      H->data[i0] = ((H->data[i0] - deltaone->data[i0]) - 2.0 * y->data[i0] *
                     C->data[i0]) + y2->data[i0] * b_C->data[i0];
    }

    b_D = H->size[0] << 1;
    i0 = s->size[0];
    s->size[0] = b_D;
    emxEnsureCapacity((emxArray__common *)s, i0, (int32_T)sizeof(real_T));
    br = 0;
    do {
      exitg3 = 0;
      b_D = H->size[0] << 1;
      if (br <= b_D - 1) {
        s->data[br] = fabs(H->data[br]);
        br++;
      } else {
        exitg3 = 1;
      }
    } while (exitg3 == 0);

    i0 = s->size[0];
    s->size[0] = g->size[0] << 1;
    emxEnsureCapacity((emxArray__common *)s, i0, (int32_T)sizeof(real_T));
    br = g->size[0] << 1;
    for (i0 = 0; i0 < br; i0++) {
      s->data[i0] = -g->data[i0] / s->data[i0];
    }

    i0 = deltaone->size[0] * deltaone->size[1];
    deltaone->size[0] = y->size[0];
    deltaone->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)deltaone, i0, (int32_T)sizeof(real_T));
    br = y->size[0] * y->size[1];
    for (i0 = 0; i0 < br; i0++) {
      deltaone->data[i0] = y->data[i0];
    }

    /*  use step-halving procedure to ensure progress is made */
    ib = 1;
    ia = 0;
    exitg2 = FALSE;
    while ((exitg2 == FALSE) && (ia < 20)) {
      ib = ia + 1;
      b_D = deltaone->size[0] << 1;
      i0 = b_deltaone->size[0];
      b_deltaone->size[0] = b_D;
      emxEnsureCapacity((emxArray__common *)b_deltaone, i0, (int32_T)sizeof
                        (real_T));
      for (i0 = 0; i0 < b_D; i0++) {
        b_deltaone->data[i0] = deltaone->data[i0] + s->data[i0];
      }

      for (i0 = 0; i0 < 2; i0++) {
        b_y[i0] = y->size[i0];
      }

      i0 = y->size[0] * y->size[1];
      y->size[0] = b_y[0];
      y->size[1] = b_y[1];
      emxEnsureCapacity((emxArray__common *)y, i0, (int32_T)sizeof(real_T));
      br = b_y[1];
      for (i0 = 0; i0 < br; i0++) {
        ar = b_y[0];
        for (i1 = 0; i1 < ar; i1++) {
          y->data[i1 + y->size[0] * i0] = b_deltaone->data[i1 + b_y[0] * i0];
        }
      }

      b_euclid(y, y, d);
      b_D = x->size[0];
      i0 = delta->size[0] * delta->size[1];
      delta->size[0] = b_D;
      emxEnsureCapacity((emxArray__common *)delta, i0, (int32_T)sizeof(real_T));
      b_D = x->size[0];
      i0 = delta->size[0] * delta->size[1];
      delta->size[1] = b_D;
      emxEnsureCapacity((emxArray__common *)delta, i0, (int32_T)sizeof(real_T));
      br = x->size[0] * x->size[0];
      for (i0 = 0; i0 < br; i0++) {
        delta->data[i0] = 0.0;
      }

      E_new = x->size[0];
      u1 = x->size[0];
      if (E_new <= u1) {
      } else {
        E_new = u1;
      }

      b_D = (int32_T)E_new;
      if (b_D > 0) {
        for (br = 0; br + 1 <= b_D; br++) {
          delta->data[br + delta->size[0] * br] = 1.0;
        }
      }

      i0 = d->size[0] * d->size[1];
      emxEnsureCapacity((emxArray__common *)d, i0, (int32_T)sizeof(real_T));
      b_D = d->size[0];
      br = d->size[1];
      br *= b_D;
      for (i0 = 0; i0 < br; i0++) {
        d->data[i0] += delta->data[i0];
      }

      rdivide(d, dinv);
      i0 = d_D->size[0] * d_D->size[1];
      d_D->size[0] = D->size[0];
      d_D->size[1] = D->size[1];
      emxEnsureCapacity((emxArray__common *)d_D, i0, (int32_T)sizeof(real_T));
      br = D->size[0] * D->size[1];
      for (i0 = 0; i0 < br; i0++) {
        d_D->data[i0] = D->data[i0] - d->data[i0];
      }

      power(d_D, delta);
      i0 = c_delta->size[0] * c_delta->size[1];
      c_delta->size[0] = delta->size[0];
      c_delta->size[1] = delta->size[1];
      emxEnsureCapacity((emxArray__common *)c_delta, i0, (int32_T)sizeof(real_T));
      br = delta->size[0] * delta->size[1];
      for (i0 = 0; i0 < br; i0++) {
        c_delta->data[i0] = delta->data[i0] * Dinv->data[i0];
      }

      c_sum(c_delta, b_x);
      if (b_x->size[1] == 0) {
        E_new = 0.0;
      } else {
        E_new = b_x->data[0];
        for (br = 2; br <= b_x->size[1]; br++) {
          E_new += b_x->data[br - 1];
        }
      }

      if (E_new < E) {
        exitg2 = TRUE;
      } else {
        i0 = s->size[0];
        emxEnsureCapacity((emxArray__common *)s, i0, (int32_T)sizeof(real_T));
        br = s->size[0];
        for (i0 = 0; i0 < br; i0++) {
          s->data[i0] *= 0.5;
        }

        ia++;
      }
    }

    /*  bomb out if too many halving steps are required */
    if ((ib == 20) || (fabs((E - E_new) / E) < 1.0E-9)) {
      exitg1 = TRUE;
    } else {
      /*  evaluate termination criterion */
      /*  report progress */
      E = E_new;
      i++;
    }
  }

  emxFree_real_T(&b_deltaone);
  emxFree_real_T(&d_D);
  emxFree_real_T(&c_delta);
  emxFree_real_T(&b_x);
  emxFree_real_T(&b_C);
  emxFree_real_T(&C);
  emxFree_real_T(&s);
  emxFree_real_T(&H);
  emxFree_real_T(&y2);
  emxFree_real_T(&g);
  emxFree_real_T(&deltaone);
  emxFree_real_T(&delta);
  emxFree_real_T(&dinv);
  emxFree_real_T(&d);
  emxFree_real_T(&Dinv);
  emxFree_real_T(&D);

  /*  fiddle stress to match the original Sammon paper */
}

/* End of code generation (sammon.c) */
