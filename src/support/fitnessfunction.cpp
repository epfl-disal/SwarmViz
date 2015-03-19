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

#include "fitnessfunction.h"
#include "../pso/psohelper.h"
#include <cmath>

typedef double (*function);

FitnessFunction::FitnessFunction()
{
}
double FitnessFunction::sphere(const QVector<double> vector, double sigma) {
    double value = 0;
    for (int i = 0; i < vector.size(); i++) {
        value +=  pow(vector[i], 2);
    }

    value +=  PsoHelper::gaussianNoise(sigma);
    return value;
}
double FitnessFunction::rosenbrock(const QVector<double> vector, double sigma) {
    double value = 0;
    for (int i = 0; i < vector.size()- 1; i++) { // sum from 1 to n-1
        value += pow((1 - vector[i]), 2); // (1 - x(i))^2
        value += 100 * pow(vector[i+1] - pow(vector[i], 2.0), 2.0); // 100 * (x(i+1) - x(i)^ 2) ^ 2
    }
    value += PsoHelper::gaussianNoise(sigma);
    return value;
}
double FitnessFunction::rastrigin(const QVector<double> vector, double sigma) {
    double value = 0;
    for (int i = 0; i < vector.size(); i++) {
        value += pow(vector[i], 2);
        value -= 10 * cos(2 * PI * vector[i]);
        value += 10;
    }
    value += PsoHelper::gaussianNoise(sigma);
    return value;
}
double FitnessFunction::grienwank(const QVector<double> vector, double sigma) {
    double value = 1;

    for (int i = 0; i < vector.size(); i++) {
        value += pow(vector[i], 2) / 4000;
    }

    double temporaryValue = 1;
    for (int i = 0; i < vector.size(); i++) {
        temporaryValue *= cos(vector[i] / sqrt(i + 1));
    }

    value -= temporaryValue;

    value += PsoHelper::gaussianNoise(sigma);
    return value;
}
double FitnessFunction::twinpeak(const QVector<double> vector, double sigma)
{
    double x = vector[0];
    double y = vector[1];
    double value = -5*pow(x, 2) + pow(y, 2) + pow(x, 4);
    return value + PsoHelper::gaussianNoise(sigma);
}
double FitnessFunction::craterlake(const QVector<double> vector, double sigma)
{
    double x = vector[0];
    double y = vector[1];
    double value =  -pow(pow(x, 2.0) + pow(y, 2.0), 2.0) + 100*(pow(x, 2.0) + pow(y, 2.0));
    return value + PsoHelper::gaussianNoise(sigma);
}
double FitnessFunction::schwefel(const QVector<double> vector, double sigma)
{
    double value = 0;
    for (int i = 0; i < vector.size(); i++)
        value += -vector[i]*sin(sqrt(abs(vector[i])));
    return value + PsoHelper::gaussianNoise(sigma);
}

double FitnessFunction::ackley(const QVector<double> vector, double sigma)
{
    double value;
    double tmp1 = 0;
    for (int i = 0; i < vector.size(); i++)
        tmp1 += pow(vector[i], 2.0);
    tmp1 = -20*exp(-0.2*sqrt(tmp1/vector.size()));
    double tmp2 = 0;
    for (int i = 0; i < vector.size(); i++)
        tmp2 += cos(2*PI*vector[i]);
    tmp2 = exp(tmp2/vector.size());
    value = tmp1 - tmp2 + 20 + exp(1);
    return value + PsoHelper::gaussianNoise(sigma);
}
double FitnessFunction::michalewicz(const QVector<double> vector, double sigma)
{
    double value = 0;
    for (int i = 0; i < vector.size(); i++)
        value -= sin(vector[i])*pow(sin(i*pow(vector[i], 2.0)/PI), 20.0);
    return value + PsoHelper::gaussianNoise(sigma);

}
double FitnessFunction::easom(const QVector<double> vector, double sigma)
{
    double value = 0;
    double x = vector[0];
    double y = vector[1];
    value = -cos(x)*cos(y)*exp(-pow(x - PI, 2.0) - pow(y - PI, 2.0));
    return value + PsoHelper::gaussianNoise(sigma);
}
double FitnessFunction::dropwave(const QVector<double> vector, double sigma)
{
    double x = vector[0];
    double y = vector[1];
    double value = -(1 + cos(12*sqrt(pow(x, 2.0) + pow(y, 2.0)))) / (0.5 * (pow(x, 2.0) + pow(y, 2.0)) + 2);
    return value + PsoHelper::gaussianNoise(sigma);
}
double FitnessFunction::value(QVector<double> vector, double sigma)
{
    switch(m_function) {
    case 0:
        return sphere(vector, sigma);
    case 1:
        return rosenbrock(vector, sigma);
    case 2:
        return rastrigin(vector, sigma);
    case 3:
        return grienwank(vector, sigma);
    case 4:
        return twinpeak(vector, sigma);
    case 5:
        return craterlake(vector, sigma);
    case 6:
        return schwefel(vector, sigma);
    case 7:
        return ackley(vector, sigma);
    case 8:
        return michalewicz(vector, sigma);
    case 9:
        return easom(vector, sigma);
    case 10:
        return dropwave(vector, sigma);
    default:
        return 0;
    }
}
void FitnessFunction::setFitnessFunction(int index)
{
    m_function = index;
}



