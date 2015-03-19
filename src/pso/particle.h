/****************************************************************************************
 * Copyright (C) 2013 Guillaume Jornod <guillaume.jornod@gmail.com>                     *
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr> Original structure            *
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

#ifndef PARTICLE_H
#define PARTICLE_H

/**
 * @file particle.h
 * @short Definition of structure Particle
 */

#include <QVector>

/**
 * @brief A particle
 *
 * This structure represents a particle. A particle contains
 * informations about it's current position, speed, and how
 * it, and it's neighbors are performing.
 *
 * It then stores a position and speed, as well as the
 * personal best and neighbor best, using vectors. It also
 * stores the fitness of the personal and neighbor best.
 */
struct Particle
{
    /**
     * @brief Position
     */
    QVector<double> position;
    /**
     * @brief Velocity
     */
    QVector<double> velocity;
    /**
     * @brief Local best
     */
    QVector<double> localBest;
    /**
     * @brief Local best performance
     */
    double localBestPerformance;
    /**
     * @brief Neighbor best
     */
    QVector<double> neighbourBest;
    /**
     * @brief Neighbor best performance
     */
    double neighbourBestPerformance;
    /**
     * @brief age
     */
    int age;
};

/**
 * @brief Initialize a particle
 *
 * This function initializes the attributes of a particle,
 * given a dimension for the vectors, and a pointer on
 * a particle.
 *
 * @param particle Particle to initialize.
 * @param dimension Dimension of the vector.
 */
void initializeParticle(Particle *particle, int dimension);
/**
 * @brief Clean a particle
 *
 * This function cleans all the attributes of
 * a particle. It do not delete the particle.
 *
 * @param particle Particle to clean.
 */
void cleanParticle(Particle *particle);

#endif // PARTICLE_H
