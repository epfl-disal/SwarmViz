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

#ifndef SWARM_H
#define SWARM_H

/**
 * @file swarm.h
 * @short Definition of class Swarm
 */

#include "particle.h"
#include "support/screenshots.h"

class Screenshots;
/**
 * @brief A swarm performing PSO
 *
 * The class Swarm performs the steps of the PSO. Depending on the user choices, it has two behaviors.
 *
 * The first one is the usual PSO performing. It takes care of a swarm of particles, and
 * performs the PSO steps. Each step first computes the directions for which the particles should move,
 *  and then moves them, finally it recomputes the local and neighbor best positions.
 *
 * The second one is the reading of input files, which are either robots data or previous experiment output.
 * The class triggers the update of the particles' data with the one read from the input file corresponding to the iteration.
 * For the swarm manager and the visualization classes, the particles are the same as if the PSO was actually running.
 *
 * \author Luxien XU
 * \author Guillaume Jornod
 */
class Swarm
{
public:
    /**
     * @brief Default constructor
     *
     * This constructor creates an empty swarm. All swarms
     * should be initialized with init().
     */
    Swarm();
    /**
     * @brief Destructor
     */
    ~Swarm();
    /**
     * @brief Initialize a problem to be solved by the swarm
     *
     * This method is used to initialize a problem to be solved
     * by PSO, providing the dimension of the problem, the
     * swarm size, a fitness function, the range for the
     * position coordinates, the maximum velocity, the number
     * of neighbors on each side, following the ring topology,
     * weights to give to the local and neighbor best and the
     * inertia.
     *
     * @param dimension Dimension of the problem.
     * @param size Size of the swarm.
     * @param fitness Fitness function.
     * @param minimum Minimum value of the position.
     * @param maximum Maximum value of the position.
     * @param maximumVelocity Maximum velocity.
     * @param neighbors Number of neighbors.
     * @param localWeight Weight for the local best.
     * @param neighbourWeight Weight for the neighbor best.
     * @param inertia Inertia coefficient.
     * @param sigma Standard deviation of the noise
     * @param noiseResistance Noise resistance algorithm?
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void init(int dimension, int size, FitnessFunction *fitness, double minimum, double maximum,
              double maximumVelocity, int neighbours, double localWeight, double neighbourWeight,
              double inertia, double sigma, bool noiseResistance);
    /**
     * @brief Performs a step
     *
     * This method has two different behavior depending on the
     * mode of the program.
     *
     * The first one is to trigger the reading of the file.
     *
     * The second one is the normal step of the PSO algorithm.
     * The velocities and the positions of the particle are updated.
     * Then, the performances are updated, for the particle, the local best and the neighbor best.
     * The best particle is then found, stored and returned.
     *
     * @return The best position found in that step.
     * @param iteration Current iteration number
     * @param firstIt First iteration?
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    const QVector<double> step(const int iteration, const bool firstIt = false);
    /**
     * @brief Gets a particle
     * @param index Index of the particle.
     * @return The particle at the given index.
     * \author Lucien XU
     */
    Particle * operator[](int index);
    /**
     * @brief Gets a particle
     * @param index Index of the particle.
     * @return The particle at the given index.
     * \author Lucien XU
     */
    const Particle * operator[](int index) const;
    /**
     * @brief Dimensionality of the problem
     * @return Dimensionality of the problem.
     * \author Lucien XU
     */
    int dimension() const;
    /**
     * @brief Size of the swarm.
     * @return size of the swarm.
     * \author Lucien XU
     */
    int size() const;
    /**
     * @brief Minimum value of the position.
     * @return minimum value of the position.
     */
    double minimum() const;
    /**
     * @brief Maximum value of the position.
     * @return maximum value of the position.
     * \author Lucien XU
     */
    double maximum() const;
    /**
     * @brief An error occurred in the reading
     *
     * This boolean is set to true when a error occurred in the reading of the input files.
     */
    bool m_errorWhileReading;
    /**
     * @brief Sets the file manager instance.
     * @param screenshots File manager instance.
     * \author Guillaume Jornod
     */
    void setScreenshots(const Screenshots * screenshots);
    /**
     * @brief Gets position values range
     * @param min Pointer to the minimum value to set
     * @param max Pointer to the maximum value to set
     * \author Guillaume Jornod
     */
    void getMinMaxPos(double *min, double *max) const;
    /**
     * @brief Getter of the best performance
     * @return best performance
     * \author Guillaume Jornod
     */
    double bestPerformance() const;
    /**
     * @brief Getter of a particle performance
     * @param i Particle index
     * @return Performance of the particle i
     * \author Guillaume Jornod
     */
    double getPerformance(const int i) const;
    /**
     * @brief Performance of the particles.
     * @return Performance of the particles.
     * \author Lucien XU
     */
    const double * performance() const;
    /**
     * @brief  Getter of the current iteration.
     * @return Current iteration.
     * \author Guillaume Jornod
     */
    int iteration() const;
    /**
     * @brief Initial fitness range
     *
     * Gets initial fitness range for trajectory fitness coloring.
     * @param min Pointer to the minimum value to be set.
     * @param max Pointer to the maximum value to be set.
     * \author Guillaume Jornod
     */
    void getMinMaxInitialFitness(double *min, double *max) const;
    /**
     *@brief Gets noise free performance
     *
     * This function is used to display the actual
     * best fitness value of the iteration
     * in the GUI
     * @return Actual best performance
     * \author Guillaume Jornod
     */
    double getActualBestPerformance() const;
private:
    /**
     * @brief Transform a particle index
     *
     * This method is used to get the neighbors of a particle.
     * @param index Index of the particle
     * @return Index of an existing particle
     * \author Lucien XU
     */
    int indexInRange(int index) const;
    /**
     * @brief Updates performance
     *
     * This method updates the list of performance
     * associated to each particle.
     * @param type EVOLVE or EVOLVE_AVG for noise resistance
     * @param firstIt Populates or not the initial fitness range
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void updatePerformance(int type, const bool firstIt);
    /**
     * @internal
     * @brief Updates local performance
     *
     * This method updates the local performance
     * of each particle.
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void updateLocalPerformance();
    /**
     * @internal
     * @brief Updates neighbor performance
     *
     * This method updates the neighbor performance
     * of each particle.
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void updateNeighbourPerformance();
    /**
     * @brief Dimension of the problem
     */
    int m_dimension;
    /**
     * @brief Size of the swarm
     */
    int m_size;
    /**
     * @brief Fitness function instance
     */
    FitnessFunction * m_fitness;
    /**
     * @brief Minimum value of the position
     */
    double m_minimum;
    /**
     * @brief Maximum value of the position
     */
    double m_maximum;
    /**
     * @brief Maximum velocity
     */
    double m_maximumVelocity;
    /**
     * @brief Number of neighbors
     */
    int m_neighbours;
    /**
     * @brief Local weight
     */
    double m_localWeight;
    /**
     * @brief Neighbor weight
     */
    double m_neighbourWeight;
    /**
     * @brief Inertia coefficient
     */
    double m_inertia;
    /**
     * @brief Array of particles
     */
    Particle *m_particles;
    /**
     * @brief Current performance of each particle
     */
    double *m_performance;
    /**
     * @brief Current iteration
     */
    int m_iteration;
    /**
     * @brief File manager instance
     */
    const Screenshots * m_screenshots;
    /**
     * @brief Best performance of the iteration
     */
    double m_bestPerformance;
    /**
     * @brief Initial fitness range
     */
    double m_initFitnessRange[2];
    /**
     * @brief Noise standard deviation
     */
    double m_sigma;
    /**
     * @brief Noise resistance algorithm?
     */
    bool m_noiseResistance;
    /**
     * @brief Stores the best for noise resistance
     */
    Particle *m_best;
    /**
     * Let Screenshots access all members
     */
    friend class Screenshots;

};

#endif // SWARM_H
