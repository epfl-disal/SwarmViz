/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

/**
 * @file swarmmanager.cpp
 * @short Implementation of class SwarmManager
 */

#include "swarmmanager.h"
#include "../pso/swarm.h"

#include <cmath>
#include <sys/stat.h>

#include <QtCore/QDebug>
#include <QtCore/QTimer>
#include <time.h>

/**
 * @brief MAX_ITERATIONS
 *
 * Default maximum iterations.
 */
static const int MAX_ITERATIONS = 1500;
/**
 * @brief first iteration
 */
static const int MIN_ITERATION = -1;
/**
 * @brief DIMENSION
 *
 * Default dimension of the problem.
 */
static const int DIMENSION = 100;
/**
 * @brief SWARM_SIZE
 *
 * Default size of the swarm.
 */
static const int SWARM_SIZE = 20;
/**
 * @brief NEIGHBOURS
 *
 * Default neighbours count.
 */
static const int NEIGHBOURS = 10;
/**
 * @brief LOCAL_WEIGHT
 *
 * Default weight for local best.
 */
static const double LOCAL_WEIGHT = 0.01;
/**
 * @brief NEIGHBOUR_WEIGHT
 *
 * Default weight for neighbour best.
 */
static const double NEIGHBOUR_WEIGHT = 0.01;
/**
 * @brief MINIMUM
 *
 * Default minimum.
 */
static const double MINIMUM = -5.12;
/**
 * @brief MAXIMUM
 *
 * Default maximum.
 */
static const double MAXIMUM = 5.11;
/**
 * @brief MAXIMUM_VELOCITY
 *
 * Default maximum velocity.
 */
static const double MAXIMUM_VELOCITY = 4.0;
/**
 * @brief INERTIA
 *
 * Default intertia.
 */
static const double INERTIA = 0.01;

/**
 * @brief STEP_TICK
 *
 * Number of steps before sending a tick.
 */
static const int STEP_TICK = 2;


SwarmManager::SwarmManager(QObject *parent) :
    QObject(parent)
{
    m_maxIterations = MAX_ITERATIONS;
    m_effectiveMaxIterations = MAX_ITERATIONS;
    m_dimension = DIMENSION;
    m_size = SWARM_SIZE;
    m_minimum = MINIMUM;
    m_maximum = MAXIMUM;
    m_maximumVelocity = MAXIMUM_VELOCITY;
    m_localWeight = LOCAL_WEIGHT;
    m_neighbourWeight = NEIGHBOUR_WEIGHT;
    m_inertia = INERTIA;
    m_fitnessFunctionIndex = 0;
    m_neighbours = NEIGHBOURS;

    m_swarm = new Swarm();
    m_minIteration = MIN_ITERATION;
    m_iterations = MIN_ITERATION;
    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(step()));
    m_simulationDirection = true;

    // create empty screen shot before real one allocation
    m_screenshot = new Screenshots(parent);
    m_noise = 0.0;
    m_noiseResistance = false;

    reset();
}

SwarmManager::~SwarmManager()
{
    delete m_swarm;
}

int SwarmManager::maxIterations() const
{
    return m_maxIterations;
}

const Swarm * SwarmManager::swarm() const
{
    return m_swarm;
}

QList<FitnessMap> SwarmManager::fitnessList() const
{
    return m_fitnessList;
}

void SwarmManager::setMaxIterations(int maxIterations, bool doReset)
{
    m_maxIterations = maxIterations;
    m_effectiveMaxIterations = maxIterations;
    if (doReset)
        reset();
    else
        emit newRealMax(m_maxIterations);
}

void SwarmManager::setEffectiveMaxIterations(int maxIterations)
{
    m_effectiveMaxIterations = maxIterations;
    emit newRange(m_minIteration, maxIterations);
}


void SwarmManager::setMinIterations(int minIteration)
{
    m_minIteration = minIteration;
    emit newRange(m_minIteration, m_maxIterations);
    reset();
}

void SwarmManager::setDimension(int dimension, bool doReset)
{
    m_dimension = dimension;
    if (doReset)
        reset();
}

void SwarmManager::setSize(int size, bool doReset)
{
    m_size = size;
    if (doReset)
        reset();
}

void SwarmManager::setMinimum(double minimum, bool doReset)
{
    m_minimum = minimum;
    if (doReset)
        reset();
}

void SwarmManager::setMaximum(double maximum, bool doReset)
{
    m_maximum = maximum;
    if (doReset)
        reset();
}

void SwarmManager::setMaximumVelocity(double maximumVelocity, bool doReset)
{
    m_maximumVelocity = maximumVelocity;
    if (doReset)
        reset();
}

void SwarmManager::setInertia(double inertia, bool doReset)
{
    m_inertia = inertia;
    if (doReset)
        reset();
}

void SwarmManager::setFitnessFunctionIndex(int index, bool doReset)
{
    m_fitnessFunctionIndex = index;
    if (doReset)
        reset();
}

void SwarmManager::setTimerInterval(int interval)
{
    m_timer->setInterval(interval);
}

void SwarmManager::setRunning(bool running)
{
    if (running) {
        m_timer->start();
    } else {
        m_timer->stop();
    }
}

void SwarmManager::step()
{
    m_bestPosition = m_swarm->step((int)m_iterations, m_iterations == m_maxIterations);
    if (m_iterations >= m_minIteration) {
        m_fitness_value = swarm()->getActualBestPerformance();
        qDebug() << "Step" << m_iterations << "best fitness so far"
                 << m_fitness_value;
        QList<double> fitnessList;
        for (int i = 0; i < m_size; i++) {
            fitnessList.append(swarm()->getPerformance(i));
        }


        m_fitnessList[m_runs - 1].insert(m_iterations, fitnessList);
    }
    // If unable to read file and iteration in the range
    if(m_swarm->m_errorWhileReading && m_iterations < m_effectiveMaxIterations)
    {
        restart(false);
        setRunning(false); // Maximum iteration reached stop
        emit emergencyStop();
        return;
    }

    emit stepped();
    emit currentIterationChanged(m_runs, m_iterations, m_fitness_value);

    if(m_iterations == m_effectiveMaxIterations)
    {
        restart(false);
        setRunning(false); // Maximum iteration reached stop
        emit emergencyStop();
        return;
    }

    if (m_simulationDirection)
        m_iterations ++;
    else if (m_iterations > m_minIteration)
        m_iterations --;
    else
        restart();

}

void SwarmManager::stepb(){
    m_simulationDirection = false;
    step();
    m_simulationDirection = true;
}

void SwarmManager::restart(bool refresh)
{
    m_runs ++;
    while (m_fitnessList.size() < m_runs) {
        m_fitnessList.append(FitnessMap());
    }

    m_iterations = m_minIteration;

    if(m_screenshot->isRead())
    {
        m_screenshot->getReadParam(this);
    }
    else
        m_screenshot->writePsoParam(m_maxIterations, m_size);
    FitnessFunction * function = new FitnessFunction();
    function->setFitnessFunction(m_fitnessFunctionIndex);
    m_swarm->init(m_dimension, m_size, function,
                  m_minimum, m_maximum, m_maximumVelocity, m_neighbours,
                  m_localWeight, m_neighbourWeight, m_inertia, m_noise, m_noiseResistance);

    if (refresh) // Let avoid the refreshing of the visualisations if the run is finish
        emit resetRequested();
}

void SwarmManager::reset()
{
    m_fitnessList.clear();
    m_runs = 0;
    restart();
}

void SwarmManager::setLocalBestWeight(double localWeight, bool doReset)
{
    m_localWeight = localWeight;
    if (doReset)
        reset();
}

void SwarmManager::setNeighbourBestWeight(double neighbourWeight, bool doReset)
{
    m_neighbourWeight = neighbourWeight;
    if (doReset)
        reset();
}


void SwarmManager::setNeighbourNumber(int neighbourNumber, bool doReset)
{
    m_neighbours = (int)(neighbourNumber/2);
    if (doReset)
        reset();
}
void SwarmManager::setScreenshot(const Screenshots *screenshot)
{
    m_screenshot = screenshot;
    m_swarm->setScreenshots(screenshot);
}

void SwarmManager::setNoise(const double sigma, bool doReset)
{
    m_noise = sigma;
    if (doReset)
        restart();
}

void SwarmManager::setNoiseResistance(bool noiseResistance)
{
    m_noiseResistance = noiseResistance;
    restart();
}
