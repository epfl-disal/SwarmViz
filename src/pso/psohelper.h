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

#ifndef PSOHELPER_H
#define PSOHELPER_H

/**
 * @file psohelper.h
 * @short Definition of class PsoHelper
 */

/**
 * @brief PSO helper class
 *
 * This class contains functions that are used in PSO.
 * It provides two methods that are used to manage
 * random numbers and a third to generate gaussian noise.
 *
 * \author Lucien XU
 * \author Guillaume Jornod
 */
class PsoHelper
{
public:
    /**
     * @brief Initializes the random number generator
     * @param seed seed.
     * \author Lucien XU
     */
    static void initRandom(unsigned int seed);
    /**
     * @brief Generates a random number between 0 and 1
     * @return a random number.
     * \author Lucien XU
     */
    static double random();
    /**
     * @brief Generates noise with mean 0 and variance sigma^2
     * @param sigma Standard deviation
     * @return noise
     * \author Guillaume Jornod
     */
    static double gaussianNoise(double sigma);
};

#endif // PSOHELPER_H
