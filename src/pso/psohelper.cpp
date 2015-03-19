/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
 * Copyright (C) 2013 Guillaume Jornod <guillaume.jornod@gmail.com> gaussianNoise       *
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

/**
 * @file psohelper.cpp
 * @short Implementation of class PsoHelper
 */

#include "psohelper.h"
#include <cstdlib>
#include <math.h>
#include <QtCore/QDebug>

void PsoHelper::initRandom(unsigned int seed)
{
    srand(seed);
}

double PsoHelper::random() {
    return ((double) rand()) / ((double) RAND_MAX);
}

/*
 * Inspired from gsl_ran_gaussian (http://www.gnu.org/software/gsl/manual/html_node/The-Gaussian-Distribution.html)
 */
double PsoHelper::gaussianNoise(double sigma)
{
    if(sigma == 0)
        return 0.0;
    double x, y, r2;
    do
    {
        /* choose x,y in uniform square (-1,-1) to (+1,+1) */
        x = -1 + 2 * random();
        y = -1 + 2 * random();

        /* see if it is in the unit circle */
        r2 = x * x + y * y;
    }
    while (r2 > 1.0 || r2 == 0);

    /* Box-Muller transform */
    return sigma * y * sqrt (-2.0 * log (r2) / r2);

}
