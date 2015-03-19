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


/**
 * @file particle.cpp
 * @short Implementation of class Particle
 */

#include "particle.h"

void initializeParticle(Particle *particle, int dimension)
{
    particle->position = QVector<double>(dimension);
    particle->velocity = QVector<double>(dimension);
    particle->localBest = QVector<double>(dimension);
    particle->localBestPerformance = 0;
    particle->neighbourBest = QVector<double>(dimension);
    particle->neighbourBestPerformance = 0;
    particle->age = 1;
}

void cleanParticle(Particle *particle)
{
    particle->position.clear();
    particle->velocity.clear();
    particle->localBest.clear();
    particle->neighbourBest.clear();
    particle->age = 1;
}
