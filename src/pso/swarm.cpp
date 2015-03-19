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
 * @file swarm.cpp
 * @short Implementation of class Swarm
 */

#include "swarm.h"
#include <cstdlib>
#include <QtCore/QDebug>
#include <sys/stat.h>
#include "psohelper.h"

#define EVOLVE 0
#define EVOLVE_AVG 1

Swarm::Swarm()
{
    m_particles = 0;
    m_performance = 0;
    m_minimum = 0.;
    m_maximum = 0.;
    m_maximumVelocity = 0.;

    m_fitness = new FitnessFunction();
    m_neighbours = 0;
    m_localWeight = 0;
    m_neighbourWeight = 0;
    m_inertia = 0;
    m_screenshots = 0;
    m_sigma = 0;
    m_noiseResistance = false;
}

Swarm::~Swarm()
{
    if (m_particles) {
        for (int i = 0; i < m_size; i++) {
            cleanParticle((m_particles + i));
        }
        delete [] m_particles;
        m_particles = 0;
    }
    if (m_performance) {
        delete [] m_performance;
    }
}

void Swarm::init(int dimension, int size, FitnessFunction * fitness, double minimum, double maximum,
                 double maximumVelocity, int neighbours, double localWeight, double neighbourWeight,
                 double inertia, double sigma, bool noiseResistance)
{
    if (dimension < 0 || size < 0 || neighbours < 0) {
        abort();
    }

    // Allocate memory
    if (m_particles) {
        for (int i = 0; i < m_size; i++) {
            cleanParticle((m_particles + i));
        }
        delete[] m_particles;
        m_particles = 0;
    }
    if (m_performance) {
        delete [] m_performance;
    }

    m_particles = new Particle[size];
    for (int i = 0; i < size; i++) {
        initializeParticle((m_particles + i), dimension);
    }

    m_performance = new double[size];

    // Set attributes
    m_dimension = dimension;
    m_size = size;

    m_fitness = fitness;
    m_minimum = minimum;
    m_maximum = maximum;
    m_maximumVelocity = maximumVelocity;
    m_neighbours = neighbours;
    m_localWeight = localWeight;
    m_neighbourWeight = neighbourWeight;
    m_inertia = inertia;
    m_sigma = sigma;
    m_noiseResistance = noiseResistance;

    m_initFitnessRange[0] = 100000;
    m_initFitnessRange[1] = -100000;

    // Init particles at random position, and random velocity
    for (int i = 0; i < m_size; i++) {
        Particle *particle = (m_particles + i);

        for (int j = 0; j < m_dimension; j++) {
            // Random position
            particle->position[j] = (m_maximum - m_minimum) * PsoHelper::random() + m_minimum;

            // Best position are the current one
            particle->localBest[j] = particle->position[j];
            particle->neighbourBest[j] = particle->position[j];

            // Random velocity
            particle->velocity[j] = 2 * m_maximumVelocity * PsoHelper::random()
                                          - m_maximumVelocity;
        }
    }

    // Perform performance initialization
    updatePerformance(EVOLVE, true);

    for (int i = 0; i < m_size; i++) {
        (m_particles + i)->localBestPerformance = m_performance[i];
        (m_particles + i)->neighbourBestPerformance = m_performance[i];
    }
    updateNeighbourPerformance();
    m_iteration = 0;

    if(m_screenshots == 0)// if the file manager is not set, do not write
        return;
    Particle *particle = (m_particles);
    m_screenshots->writeState(particle->position, this, m_iteration);
    m_errorWhileReading = false;
}

const QVector<double> Swarm::step(const int iteration, const bool firstIt)
{
    m_errorWhileReading = false;
    m_iteration = iteration;
    if (m_screenshots->isRead())
    {
        const QVector<double> best =  m_screenshots->readState(this, m_iteration);
        return best;
    }
    else
    {
        for (int i = 0; i < m_size; i++) {

            // Compute speed
            Particle *particle = (m_particles + i);

            for (int j = 0; j < m_dimension; j++) {
                double localCoefficient = (m_localWeight * PsoHelper::random());
                double neighbourCoefficient = (m_neighbourWeight * PsoHelper::random());
                particle->velocity[j] *= m_inertia;
                particle->velocity[j] += localCoefficient * (particle->localBest[j] - particle->position[j]);
                particle->velocity[j] += neighbourCoefficient * (particle->neighbourBest[j] - particle->position[j]);
            }

            // Be sure that velocities stays in bound
            for (int j = 0; j < m_dimension; j++) {
                if (particle->velocity[j] > m_maximumVelocity) {
                    particle->velocity[j] = m_maximumVelocity;
                }

                if (particle->velocity[j] < -m_maximumVelocity) {
                    particle->velocity[j] = -m_maximumVelocity;
                }
                particle->position[j] += particle->velocity[j];
            }

            // Update position
        }

        if (m_noiseResistance)
            updatePerformance(EVOLVE_AVG, firstIt);
        updatePerformance(EVOLVE, firstIt);

        updateLocalPerformance();
        updateNeighbourPerformance();

        // Find best
        QVector<double> best = m_particles->position;
        int bestIndex = 0;
        for (int i = 1; i < m_size; i++) {
            Particle *particle = (m_particles + i);
            if (m_performance[bestIndex] > m_performance[i]) {
                best = particle->position;
                m_best = (m_particles + i);
                bestIndex = i;
            }
        }

        m_bestPerformance = m_performance[bestIndex];

        m_screenshots->writeState(best, this, m_iteration);

        return best;
    }
}

Particle * Swarm::operator [](int index)
{
    if (index >= m_size) {
        abort();
    }

    return (m_particles + index);
}

const Particle * Swarm::operator [](int index) const
{
    if (index >= m_size) {
        abort();
    }
    return (m_particles + index);
}


int Swarm::dimension() const
{
    return m_dimension;
}

int Swarm::size() const
{
    return m_size;
}

double Swarm::minimum() const
{
    return m_minimum;
}

double Swarm::maximum() const
{
    return m_maximum;
}

int Swarm::indexInRange(int index) const
{
    while (index < 0) {
        index += m_size;
    }
    while (index >= m_size) {
        index -= m_size;
    }
    return index;
}

void Swarm::updatePerformance(int type, const bool firstIt)
{
    switch(type)
    {
    case EVOLVE:
        for (int i = 0; i < m_size; i++) {
            m_performance[i] = m_fitness->value((m_particles + i)->position, m_sigma);
            if(firstIt && m_initFitnessRange[1] < m_performance[i])
                m_initFitnessRange[1] = m_performance[i];
            if (firstIt)
                m_initFitnessRange[0] = 0;
        }
        break;
    case EVOLVE_AVG:
        for (int i = 0; i < m_size; i++) {
            Particle *particle = m_particles + i;
            particle->localBestPerformance = ((particle->age - 1)*particle->localBestPerformance + m_fitness->value(particle->localBest, m_sigma))/particle->age;
            particle->age ++;
        }
    }
}

void Swarm::updateLocalPerformance()
{
    for (int i = 0; i < m_size; i++) {
        Particle *particle = (m_particles + i);
        if (m_performance[i] < particle->localBestPerformance) {
            particle->localBest = particle->position;
            particle->localBestPerformance = m_performance[i];
            particle->age = 2;
        }
    }
}

void Swarm::updateNeighbourPerformance()
{
    for (int i = 0; i < m_size; i++) {
        Particle *particle = (m_particles + i);

        for (int j = -1 * m_neighbours; j <= m_neighbours; j++) {
            int index = indexInRange(i + j);
            Particle *neighbourParticle = (m_particles + index);

            if (neighbourParticle->localBestPerformance < particle->neighbourBestPerformance) {
                particle->neighbourBest = neighbourParticle->localBest;
                particle->neighbourBestPerformance = neighbourParticle->localBestPerformance;
            }
        }
    }
}


void Swarm::setScreenshots(const Screenshots *screenshots)
{
    m_screenshots = screenshots;
}

double Swarm::bestPerformance() const
{
    return m_bestPerformance;
}

double Swarm::getPerformance(const int i) const
{
    if (m_screenshots->isRead())
        return m_performance[i];
    return m_fitness->value((m_particles + i)->position, 0);
}

double Swarm::getActualBestPerformance() const
{
    if (m_screenshots->isRead())
        return m_bestPerformance;
    qDebug() << m_best->position;
    return m_fitness->value(m_best->position, 0);
}

const double * Swarm::performance() const
{
    return m_performance;
}

int Swarm::iteration() const
{
    return m_iteration;
}
void Swarm::getMinMaxPos(double *min, double *max) const
{
    double mmin = 1000;
    double mmax = -1000;
    for (int i = 0; i < m_size; i++)
    {
        Particle * particle = m_particles + i;
        for (int j = 0; j< m_dimension; j++)
        {
            if (particle->position[j] < mmin)
                mmin = particle->position[j];
            if (particle->position[j] > mmax)
                mmax = particle->position[j];

        }
    }
    *min = mmin;
    *max = mmax;
}

void Swarm::getMinMaxInitialFitness(double *min, double *max) const
{
    *min = m_initFitnessRange[0];
    *max = m_initFitnessRange[1];
    qDebug() << *min;
}
