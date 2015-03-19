/*
 * sammon.c
 *
 * Code generation for function 'sammon'
 *
 * C source code generated on: Mon Dec 30 20:00:37 2013
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "sammon.h"
#include "sqrt.h"
#include "sum.h"
#include "power.h"
#include "rdivide.h"
#include "eye.h"
#include "abs.h"
#include "randn.h"
#include "sammon_data.h"

/* Variable Definitions */
static emlrtRSInfo emlrtRSI = { 93, "sammon",
  "/home/jornod/visualpso/project/swarmvisualiser/sammon/sammon.m" };

static emlrtRSInfo b_emlrtRSI = { 107, "sammon",
  "/home/jornod/visualpso/project/swarmvisualiser/sammon/sammon.m" };

static emlrtRSInfo c_emlrtRSI = { 111, "sammon",
  "/home/jornod/visualpso/project/swarmvisualiser/sammon/sammon.m" };

static emlrtRSInfo d_emlrtRSI = { 125, "sammon",
  "/home/jornod/visualpso/project/swarmvisualiser/sammon/sammon.m" };

static emlrtRSInfo e_emlrtRSI = { 126, "sammon",
  "/home/jornod/visualpso/project/swarmvisualiser/sammon/sammon.m" };

static emlrtRSInfo f_emlrtRSI = { 129, "sammon",
  "/home/jornod/visualpso/project/swarmvisualiser/sammon/sammon.m" };

static emlrtRSInfo g_emlrtRSI = { 139, "sammon",
  "/home/jornod/visualpso/project/swarmvisualiser/sammon/sammon.m" };

static emlrtRSInfo h_emlrtRSI = { 181, "sammon",
  "/home/jornod/visualpso/project/swarmvisualiser/sammon/sammon.m" };

static emlrtRSInfo i_emlrtRSI = { 55, "mtimes",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/ops/mtimes.m" };

static emlrtRSInfo j_emlrtRSI = { 54, "eml_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m" };

static emlrtRSInfo k_emlrtRSI = { 32, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo l_emlrtRSI = { 110, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo m_emlrtRSI = { 111, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo n_emlrtRSI = { 112, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo o_emlrtRSI = { 113, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo p_emlrtRSI = { 114, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo q_emlrtRSI = { 115, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo r_emlrtRSI = { 119, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo s_emlrtRSI = { 122, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo t_emlrtRSI = { 125, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo u_emlrtRSI = { 128, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo v_emlrtRSI = { 131, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo w_emlrtRSI = { 134, "eml_blas_xgemm",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m"
};

static emlrtRSInfo x_emlrtRSI = { 14, "eml_c_cast",
  "/enacit1/opt/matlab/R2013a/toolbox/eml/lib/matlab/eml/blas/external/eml_c_cast.m"
};

/* Function Declarations */
static void b_euclid(sammonStackData *SD, const real_T x[2000], const real_T y
                     [2000], real_T d[1000000]);
static void euclid(sammonStackData *SD, const real_T x[1000000], const real_T y
                   [1000000], real_T d[1000000]);

/* Function Definitions */
static void b_euclid(sammonStackData *SD, const real_T x[2000], const real_T y
                     [2000], real_T d[1000000])
{
  real_T b_y[2000];
  real_T c_y[2000];
  int32_T k;
  real_T b[2000];
  int32_T i2;
  real_T alpha1;
  real_T beta1;
  char_T TRANSB;
  char_T TRANSA;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  double * alpha1_t;
  double * Aia0_t;
  double * Bib0_t;
  double * beta1_t;
  double * Cic0_t;
  real_T dv4[1000];
  real_T dv5[1000];

  /*  all done */
  emlrtPushRtStackR2012b(&h_emlrtRSI, emlrtRootTLSGlobal);
  for (k = 0; k < 2000; k++) {
    b_y[k] = x[k] * x[k];
    c_y[k] = y[k] * y[k];
  }

  for (k = 0; k < 1000; k++) {
    for (i2 = 0; i2 < 2; i2++) {
      b[i2 + (k << 1)] = y[k + 1000 * i2];
    }
  }

  emlrtPushRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
  alpha1 = 1.0;
  beta1 = 0.0;
  TRANSB = 'N';
  TRANSA = 'N';
  memset(&SD->u1.f0.y[0], 0, 1000000U * sizeof(real_T));
  emlrtPushRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  m_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  n_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  k_t = (ptrdiff_t)(2);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  lda_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  ldb_t = (ptrdiff_t)(2);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  ldc_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
  alpha1_t = (double *)(&alpha1);
  emlrtPopRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
  Aia0_t = (double *)(&x[0]);
  emlrtPopRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
  Bib0_t = (double *)(&b[0]);
  emlrtPopRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
  beta1_t = (double *)(&beta1);
  emlrtPopRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
  Cic0_t = (double *)(&SD->u1.f0.y[0]);
  emlrtPopRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
  dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, alpha1_t, Aia0_t, &lda_t, Bib0_t,
        &ldb_t, beta1_t, Cic0_t, &ldc_t);
  emlrtPopRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
  c_sum(b_y, dv4);
  c_sum(c_y, dv5);
  for (k = 0; k < 1000; k++) {
    for (i2 = 0; i2 < 1000; i2++) {
      SD->u1.f0.dv6[k + 1000 * i2] = dv4[k];
      SD->u1.f0.dv7[k + 1000 * i2] = dv5[i2];
    }
  }

  for (k = 0; k < 1000; k++) {
    for (i2 = 0; i2 < 1000; i2++) {
      d[i2 + 1000 * k] = (SD->u1.f0.dv6[i2 + 1000 * k] + SD->u1.f0.dv7[i2 + 1000
                          * k]) - 2.0 * SD->u1.f0.y[i2 + 1000 * k];
    }
  }

  b_sqrt(d);
  emlrtPopRtStackR2012b(&h_emlrtRSI, emlrtRootTLSGlobal);
}

static void euclid(sammonStackData *SD, const real_T x[1000000], const real_T y
                   [1000000], real_T d[1000000])
{
  int32_T k;
  int32_T i0;
  real_T alpha1;
  real_T beta1;
  char_T TRANSB;
  char_T TRANSA;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  double * alpha1_t;
  double * Aia0_t;
  double * Bib0_t;
  double * beta1_t;
  double * Cic0_t;
  real_T dv2[1000];
  real_T dv3[1000];

  /*  all done */
  emlrtPushRtStackR2012b(&h_emlrtRSI, emlrtRootTLSGlobal);
  for (k = 0; k < 1000000; k++) {
    SD->u1.f1.y[k] = x[k] * x[k];
    SD->u1.f1.b_y[k] = y[k] * y[k];
  }

  for (k = 0; k < 1000; k++) {
    for (i0 = 0; i0 < 1000; i0++) {
      SD->u1.f1.b[i0 + 1000 * k] = y[k + 1000 * i0];
    }
  }

  emlrtPushRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
  alpha1 = 1.0;
  beta1 = 0.0;
  TRANSB = 'N';
  TRANSA = 'N';
  memset(&SD->u1.f1.c_y[0], 0, 1000000U * sizeof(real_T));
  emlrtPushRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  m_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  n_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  k_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  lda_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  ldb_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  ldc_t = (ptrdiff_t)(1000);
  emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
  alpha1_t = (double *)(&alpha1);
  emlrtPopRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
  Aia0_t = (double *)(&x[0]);
  emlrtPopRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
  Bib0_t = (double *)(&SD->u1.f1.b[0]);
  emlrtPopRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
  beta1_t = (double *)(&beta1);
  emlrtPopRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
  Cic0_t = (double *)(&SD->u1.f1.c_y[0]);
  emlrtPopRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
  dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, alpha1_t, Aia0_t, &lda_t, Bib0_t,
        &ldb_t, beta1_t, Cic0_t, &ldc_t);
  emlrtPopRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPopRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
  sum(SD->u1.f1.y, dv2);
  sum(SD->u1.f1.b_y, dv3);
  for (k = 0; k < 1000; k++) {
    for (i0 = 0; i0 < 1000; i0++) {
      SD->u1.f1.y[k + 1000 * i0] = dv2[k];
      SD->u1.f1.b_y[k + 1000 * i0] = dv3[i0];
    }
  }

  for (k = 0; k < 1000; k++) {
    for (i0 = 0; i0 < 1000; i0++) {
      d[i0 + 1000 * k] = (SD->u1.f1.y[i0 + 1000 * k] + SD->u1.f1.b_y[i0 + 1000 *
                          k]) - 2.0 * SD->u1.f1.c_y[i0 + 1000 * k];
    }
  }

  b_sqrt(d);
  emlrtPopRtStackR2012b(&h_emlrtRSI, emlrtRootTLSGlobal);
}

void sammon(sammonStackData *SD, const real_T x[1000000], real_T y[2000], real_T
            *E)
{
  real_T B;
  int32_T i;
  real_T dv0[1000];
  int32_T b_i;
  boolean_T exitg1;
  real_T alpha1;
  real_T beta1;
  char_T TRANSB;
  char_T TRANSA;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  double * alpha1_t;
  double * Aia0_t;
  double * Bib0_t;
  double * beta1_t;
  double * Cic0_t;
  real_T g[2000];
  real_T y2[2000];
  real_T b_y[2000];
  real_T c_y[2000];
  real_T d_y[2000];
  real_T e_y[2000];
  real_T b_g[2000];
  int32_T j;
  int32_T b_j;
  boolean_T exitg2;
  real_T dv1[1000];
  real_T E_new;

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
  emlrtPushRtStackR2012b(&emlrtRSI, emlrtRootTLSGlobal);
  euclid(SD, x, x, SD->f2.D);
  emlrtPopRtStackR2012b(&emlrtRSI, emlrtRootTLSGlobal);

  /*  remaining initialisation */
  B = b_sum(SD->f2.D);
  eye(SD->f2.delta);
  for (i = 0; i < 1000000; i++) {
    SD->f2.D[i] += SD->f2.delta[i];
  }

  rdivide(1.0, SD->f2.D, SD->f2.Dinv);
  emlrtPushRtStackR2012b(&b_emlrtRSI, emlrtRootTLSGlobal);
  randn(y);
  emlrtPopRtStackR2012b(&b_emlrtRSI, emlrtRootTLSGlobal);
  emlrtPushRtStackR2012b(&c_emlrtRSI, emlrtRootTLSGlobal);
  b_euclid(SD, y, y, SD->f2.d);
  eye(SD->f2.delta);
  for (i = 0; i < 1000000; i++) {
    SD->f2.d[i] += SD->f2.delta[i];
  }

  emlrtPopRtStackR2012b(&c_emlrtRSI, emlrtRootTLSGlobal);
  rdivide(1.0, SD->f2.d, SD->f2.dinv);
  for (i = 0; i < 1000000; i++) {
    SD->f2.b_D[i] = SD->f2.D[i] - SD->f2.d[i];
  }

  power(SD->f2.b_D, SD->f2.delta);
  for (i = 0; i < 1000000; i++) {
    SD->f2.d[i] = SD->f2.delta[i] * SD->f2.Dinv[i];
  }

  d_sum(SD->f2.d, dv0);
  *E = e_sum(dv0);

  /*  get on with it */
  b_i = 0;
  exitg1 = FALSE;
  while ((exitg1 == FALSE) && (b_i < 500)) {
    /*  compute gradient, Hessian and search direction (note it is actually */
    /*  1/4 of the gradient and Hessian, but the step size is just the ratio */
    /*  of the gradient and the diagonal of the Hessian so it doesn't matter). */
    for (i = 0; i < 1000000; i++) {
      SD->f2.delta[i] = SD->f2.dinv[i] - SD->f2.Dinv[i];
    }

    emlrtPushRtStackR2012b(&d_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    alpha1 = 1.0;
    beta1 = 0.0;
    TRANSB = 'N';
    TRANSA = 'N';
    for (i = 0; i < 2000; i++) {
      SD->f2.y_old[i] = 1.0;
      SD->f2.deltaone[i] = 0.0;
    }

    emlrtPushRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    m_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    n_t = (ptrdiff_t)(2);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    k_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    lda_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldb_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldc_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    alpha1_t = (double *)(&alpha1);
    emlrtPopRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    Aia0_t = (double *)(&SD->f2.delta[0]);
    emlrtPopRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    Bib0_t = (double *)(&SD->f2.y_old[0]);
    emlrtPopRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    beta1_t = (double *)(&beta1);
    emlrtPopRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    Cic0_t = (double *)(&SD->f2.deltaone[0]);
    emlrtPopRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, alpha1_t, Aia0_t, &lda_t, Bib0_t,
          &ldb_t, beta1_t, Cic0_t, &ldc_t);
    emlrtPopRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&d_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&e_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    alpha1 = 1.0;
    beta1 = 0.0;
    TRANSB = 'N';
    TRANSA = 'N';
    memset(&g[0], 0, 2000U * sizeof(real_T));
    emlrtPushRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    m_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    n_t = (ptrdiff_t)(2);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    k_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    lda_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldb_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldc_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    alpha1_t = (double *)(&alpha1);
    emlrtPopRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    Aia0_t = (double *)(&SD->f2.delta[0]);
    emlrtPopRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    Bib0_t = (double *)(&y[0]);
    emlrtPopRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    beta1_t = (double *)(&beta1);
    emlrtPopRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    Cic0_t = (double *)(&g[0]);
    emlrtPopRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, alpha1_t, Aia0_t, &lda_t, Bib0_t,
          &ldb_t, beta1_t, Cic0_t, &ldc_t);
    emlrtPopRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    for (i = 0; i < 2000; i++) {
      g[i] -= y[i] * SD->f2.deltaone[i];
    }

    emlrtPopRtStackR2012b(&e_emlrtRSI, emlrtRootTLSGlobal);
    c_power(SD->f2.dinv, SD->f2.delta);
    b_power(y, y2);
    emlrtPushRtStackR2012b(&f_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    alpha1 = 1.0;
    beta1 = 0.0;
    TRANSB = 'N';
    TRANSA = 'N';
    memset(&b_y[0], 0, 2000U * sizeof(real_T));
    emlrtPushRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    m_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    n_t = (ptrdiff_t)(2);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    k_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    lda_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldb_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldc_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    alpha1_t = (double *)(&alpha1);
    emlrtPopRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    Aia0_t = (double *)(&SD->f2.delta[0]);
    emlrtPopRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    Bib0_t = (double *)(&y2[0]);
    emlrtPopRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    beta1_t = (double *)(&beta1);
    emlrtPopRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    Cic0_t = (double *)(&b_y[0]);
    emlrtPopRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, alpha1_t, Aia0_t, &lda_t, Bib0_t,
          &ldb_t, beta1_t, Cic0_t, &ldc_t);
    emlrtPopRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    for (i = 0; i < 2000; i++) {
      c_y[i] = 2.0 * y[i];
    }

    emlrtPushRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    alpha1 = 1.0;
    beta1 = 0.0;
    TRANSB = 'N';
    TRANSA = 'N';
    memset(&d_y[0], 0, 2000U * sizeof(real_T));
    emlrtPushRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    m_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    n_t = (ptrdiff_t)(2);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    k_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    lda_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldb_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldc_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    alpha1_t = (double *)(&alpha1);
    emlrtPopRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    Aia0_t = (double *)(&SD->f2.delta[0]);
    emlrtPopRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    Bib0_t = (double *)(&y[0]);
    emlrtPopRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    beta1_t = (double *)(&beta1);
    emlrtPopRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    Cic0_t = (double *)(&d_y[0]);
    emlrtPopRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, alpha1_t, Aia0_t, &lda_t, Bib0_t,
          &ldb_t, beta1_t, Cic0_t, &ldc_t);
    emlrtPopRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    alpha1 = 1.0;
    beta1 = 0.0;
    TRANSB = 'N';
    TRANSA = 'N';
    for (i = 0; i < 2000; i++) {
      SD->f2.y_old[i] = 1.0;
      e_y[i] = 0.0;
    }

    emlrtPushRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    m_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&l_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    n_t = (ptrdiff_t)(2);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&m_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    k_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&n_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    lda_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&o_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldb_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&p_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    ldc_t = (ptrdiff_t)(1000);
    emlrtPopRtStackR2012b(&x_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&q_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    alpha1_t = (double *)(&alpha1);
    emlrtPopRtStackR2012b(&r_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    Aia0_t = (double *)(&SD->f2.delta[0]);
    emlrtPopRtStackR2012b(&s_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    Bib0_t = (double *)(&SD->f2.y_old[0]);
    emlrtPopRtStackR2012b(&t_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    beta1_t = (double *)(&beta1);
    emlrtPopRtStackR2012b(&u_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    Cic0_t = (double *)(&e_y[0]);
    emlrtPopRtStackR2012b(&v_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPushRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, alpha1_t, Aia0_t, &lda_t, Bib0_t,
          &ldb_t, beta1_t, Cic0_t, &ldc_t);
    emlrtPopRtStackR2012b(&w_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&k_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&j_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&i_emlrtRSI, emlrtRootTLSGlobal);
    emlrtPopRtStackR2012b(&f_emlrtRSI, emlrtRootTLSGlobal);
    for (i = 0; i < 2000; i++) {
      SD->f2.y_old[i] = ((b_y[i] - SD->f2.deltaone[i]) - c_y[i] * d_y[i]) + y2[i]
        * e_y[i];
      b_g[i] = -g[i];
    }

    b_abs(SD->f2.y_old, y2);
    for (i = 0; i < 2000; i++) {
      SD->f2.deltaone[i] = y2[i];
      SD->f2.y_old[i] = y[i];
    }

    b_rdivide(b_g, SD->f2.deltaone, y2);

    /*  use step-halving procedure to ensure progress is made */
    j = 1;
    b_j = 0;
    exitg2 = FALSE;
    while ((exitg2 == FALSE) && (b_j < 20)) {
      j = b_j + 1;
      for (i = 0; i < 2000; i++) {
        y[i] = SD->f2.y_old[i] + y2[i];
      }

      emlrtPushRtStackR2012b(&g_emlrtRSI, emlrtRootTLSGlobal);
      b_euclid(SD, y, y, SD->f2.d);
      eye(SD->f2.delta);
      for (i = 0; i < 1000000; i++) {
        SD->f2.d[i] += SD->f2.delta[i];
      }

      emlrtPopRtStackR2012b(&g_emlrtRSI, emlrtRootTLSGlobal);
      rdivide(1.0, SD->f2.d, SD->f2.dinv);
      for (i = 0; i < 1000000; i++) {
        SD->f2.b_D[i] = SD->f2.D[i] - SD->f2.d[i];
      }

      power(SD->f2.b_D, SD->f2.delta);
      for (i = 0; i < 1000000; i++) {
        SD->f2.d[i] = SD->f2.delta[i] * SD->f2.Dinv[i];
      }

      d_sum(SD->f2.d, dv1);
      E_new = e_sum(dv1);
      if (E_new < *E) {
        exitg2 = TRUE;
      } else {
        for (i = 0; i < 2000; i++) {
          y2[i] *= 0.5;
        }

        b_j++;
        emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar,
          emlrtRootTLSGlobal);
      }
    }

    /*  bomb out if too many halving steps are required */
    if ((j == 20) || (muDoubleScalarAbs((*E - E_new) / *E) < 1.0E-9)) {
      exitg1 = TRUE;
    } else {
      /*  evaluate termination criterion */
      /*  report progress */
      *E = E_new;
      b_i++;
      emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, emlrtRootTLSGlobal);
    }
  }

  /*  fiddle stress to match the original Sammon paper */
  *E *= 0.5 / B;
}

/* End of code generation (sammon.c) */
