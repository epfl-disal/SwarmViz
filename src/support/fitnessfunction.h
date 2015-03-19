/****************************************************************************************
 * Copyright (C) 2013 Guillaume Jornod <guillaume.jornod@gmail.com>                     *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#ifndef FITNESSFUNCTION_H
#define FITNESSFUNCTION_H
#include "pso/psohelper.h"
#include <QVector>

/**
 * @brief PI
 */
const double PI = 3.1415926;

/**
 * @brief Implementations of the benchmark functions
 *
 * This class provides the implementation of the
 * benchmark functions.
 */
class FitnessFunction
{
public:
    FitnessFunction();
    typedef double (*function)(const QVector<double>, double sigma);
    /**
 * @brief Sphere benchmark function
 * Also known as De Jong's first function\cite de1975analysis ,
 * the sphere function is implemented as following:
 * \f{align}{
 * f(x) &= \sum\limits_{j=1}^d x_j ^2\\
 * \min(f) &= f(\vec{0}) = 0
 * \f}
 * @param vector Position vector.
 * @param sigma Standard deviation of the noise
 * @return value.
 */
    double sphere(const QVector<double> vector, double sigma);

    /**
 * @brief Generalized Rosenbrock benchmark function
 *
 * The generalized Rosenbrock's function is:
\f{align}{
f(x) &= \sum\limits_{j=1}^{d-1} \left[100 \cdot (x_{j+1} - x_j^2) ^2+(1-x_j )^2 \right]\\
\min(f)&= 0
\f}
 * @param vector Position vector.
 * @param sigma Standard deviation of the noise
 * @return value.
 */
    double rosenbrock(const QVector<double> vector, double sigma);
    /**
 * @brief Rastrigin benchmark function
 *
 *The generalized Rastrigin's function \cite muhlenbein1991parallel is:
\f{align}{
f(x) &= 10\cdot d + \sum\limits_{j=1}^d\left[ x_j ^2- 10\cdot \cos{(2\cdot \pi \cdot x_j)}\right]\\
\min(f) &= f(\vec{0}) = 0
\f}
 * @param vector Position vector.
 * @param sigma Standard deviation of the noise
 * @return value.
 */
    double rastrigin(const QVector<double> vector, double sigma);

    /**
 * @brief Grienwank benchmark function
 *
 *Griewank's function \cite griewank1981generalized is implemented as:
\f{align}{
f(x) &= 1 + \sum\limits _{j=1}^d\frac{x_j^2}{4000} -\prod\limits_{j=1}^s\cos{\left(\frac{x_j}{\sqrt{j}}\right)}\\
\min(f) &= f(\vec{0}) = 0
\f}
 * @param vector Position vector.
 * @param sigma Standard deviation of the noise
 * @return value.
 */
    double grienwank(const QVector<double> vector, double sigma);
    /**
 * @brief Twinpeaks benchmark function in two dimensions.
 *
 *The twin peaks function is only available in two dimensions. It is implemented as:
 *\f{align}{
 *f(x_1, x_2) &= -5\cdot x_1^2 + x_2^2 + x_1^4\\
 *\min(f) &=  f(\pm 1.5811, 0) = -6.25
 *\f}
 * taking inspiration from the function described by \cite banchoffinteractive.
 * This function has been implemented essentially in order
 * to assess the visualization tools, since the particles
 * should separate and fall in one of the two holes.
 * @param vector Position vector.
 * @param sigma Standard deviation of the noise
 * @return
 */
    double twinpeak(const QVector<double> vector, double sigma);
    /**
 * @brief Crater lake benchmark function in two dimensions.
 *
 * Inspired by the function described by \cite banchoffinteractive,
 * the crater lake function is defined in \f$\mathbb{R}^ 2\f$
 * and has no global optimum. It has a local optimum at \f$(0, 0)\f$
 * in which the particles fall when the initial bounding square
 * is defined with \f$x_\text{max} = -x_\text{min} = 5\f$.
 *
 * This function is useful to observe the influence of the
 * maximum velocity as well as of the inertia parameters.
 * It is defined as:
 * \f{equation}{
 * f(x_1, x_2 ) = -\left( x_1^2+x_2^2\right)^2 + 100 \cdot \left( x_1^2+x_2^2\right)
 * \f}
 * @param vector Position vector.
 * @param sigma Standard deviation of the noise
 * @return
 */
    double craterlake(const QVector<double> vector, double sigma);
    /**
 * @brief Schwefel benchmark function
 *
 * Schwefel's function is implemented as following:
 * \f{align}{
 * f(x) &= \sum \limits_{j=1}^d \left[ -x_j \cdot \sin{\left(\sqrt{\lvert x_j\rvert}\right)}\right]\\
 * \min(f)&= f(420.9687,\dots ,420.9687) = -418.9829\cdot d
 * \f}
 * The bounding hypercube should be defined with
 * \f$x_\text{max} = -x_\text{min} = 500\f$.
 * @param vector Position vector
 * @param sigma Standard deviation of the noise
 * @return
 */
    double schwefel(const QVector<double> vector, double sigma);

    /**
 * @brief Ackley benchmark function
 *
 * The multimodal Ackley's function \cite molga2005test
 *  is defined as:
 * \f{align}{
 * f(x) &= -20\cdot \exp{\left[-0.2\cdot \sqrt{\frac{1}{n}\sum\limits_{j=1}^dx_j^2} - \exp{\left(\frac{1}{n}\sum\limits_{j=1}^d\cos{2\cdot\pi\cdot x_j}\right)}\right]} +20 +\exp{(1)}\\
 * \min(f) &= f(\vec{0}) = 0
 * \f}
 * @param vector Position vector
 * @param sigma Standard deviation of the noise
 * @return
 */
    double ackley(const QVector<double> vector, double sigma);
    /**
 * @brief Michalewicz benchmark function
 *
 * This function is defined as:
 * \f{equation}{
 * f(x)= -\sum\limits_{j=1}^m\sin{(x_j)}\cdot \left[\sin\left(\frac{j\cdot x_j^2}{\pi}\right)\right] ^{20}\\
 * \f}
 * The minimum depends on the number of dimensions.
 * @param vector Position vector
 * @param sigma Standard deviation of the noise
 * @return
 */
    double michalewicz(const QVector<double> vector, double sigma);
    /**
 * @brief Easom benchmark function
 *
 * Easom's function is defined \f$\mathbb{R}^2\f$ as:
 * \f{align}{
 * f(x_1, x_2) &= - \cos{(x_1)}\cdot \cos{(x_2)}\cdot \exp{\left(-(x_1 - \pi)^2-(x_1 - \pi)^2\right)}\\
 * \min(f) &= f(\pi, \pi) = -1
 * \f}
 * The fact that the function is flat outside the area
 * \f$[-4, 4]\times [-4,4]\f$ lets visualize the
 * influence of the algorithm parameters
 * on the particles interactions.
 *
 * @param vector Position vector
 * @param sigma Standard deviation of the noise
 * @return
 */
    double easom(const QVector<double> vector, double sigma);
    /**
 * @brief Dropwave benchmark function
 *
 * Defined on \f$\mathbb{R}^ 2\f$, the Drop wave
 * function is implemented as:
 * \f{equation}{
 * f(x_1, x_2) = - \frac{1+\cos{\left(12\cdot\sqrt{x_1^2+x_2^2}\right)}}{0.5\cdot (x_1^2+x_2^2) + 2 }
 * \f}
 *
 * @param vector Position vector
 * @param sigma Standard deviation of the noise
 * @return
 */
    double dropwave(const QVector<double> vector, double sigma);

  /**
   * @brief setFitnessFunction
   *
   * Set the fitness funtion to be used.
   * @param index
   */
  void setFitnessFunction(int index);

  /**
   * @brief value
   *
   * Get evaluation of the function.
 * @param vector Position vector
 * @param sigma Standard deviation of the noise
   * @return Evaluation
   */
  double value(const QVector<double> vector, double sigma);
private:
  /**
   * @brief m_function Current fitness function
   */
  int m_function;
};

#endif // FITNESSFUNCTION_H
