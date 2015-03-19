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

#ifndef SWARMMANAGER_H
#define SWARMMANAGER_H

/**
 * @file swarmmanager.h
 * @short Definition of class SwarmManager
 */

#include <QtCore/QObject>
#include <QtCore/QMap>
#include "support/screenshots.h"
#include "support/fitnessfunction.h"

class Swarm;
class QTimer;
class Screenshots;
class FitnessFunction;

/**
 * @brief A map mapping a step to the fitness for each particle
 */
typedef QMap<int, QList<double> > FitnessMap;

/**
 * @brief Interface between the swarm and visualization
 *
 * The class Swarmmanager is the interface between the Swarm and the GUI.
 * This class contains all the PSO parameters to initiate and step the algorithm through Swarm.
 * All signals emitted by MainWindow or by the visualization instances regarding the
 * PSO are centralized in this class.
 * A modification of a PSO parameter leads to the reinitialization of the Swarm ordered by the Swarmmanager.
 *
 * \author Lucien XU
 * \author Guillaume Jornod
 *
 */
class SwarmManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     *
     * Sets the default values for the attribute members.
     *  Additionally, an empty Screenshots instance
     *  is created, which will be overwritten in the MainWindow.
     * The default parameters should be consistent with the default parameter in the GUI.
     * To ensure this, the parameters are again reset add the end of the loading of the GUI.
     * @param parent Parent object.
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    explicit SwarmManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~SwarmManager();
    /**
     * @brief Maximum iterations
     *
     * Getter of the number of iterations.
     * @return Maximum iterations
     * \author Lucien XU
     */
    int maxIterations() const;
    /**
     * @brief Swarm instance
     *
     * Getter of the Swarm instance. As interface between the swarm, the GUI and the visualizations, the SwarmManager provides access to the Swarm.
     * @return Swarm.
     * \author Lucien XU
     */
    const Swarm * swarm() const;
    /**
     * @brief List of fitness
     *
     * This map is fed with the fitnesses in order
     *  to be accessed by the FitnessVisualisation.
     * @return List of fitness.
     * \author Lucien XU
     */
    QList<FitnessMap> fitnessList() const;
    /**
     * @brief Best position of the iteration
     *
     * Getter of the best position of the iteration.
     *  This method provides acces to the position
     *  of the particle having the best performance
     *  of the iteration for the BestVisualisation graph.
     * @return Best position of the iteration.
     * \author Guillaume Jornod
     */
    QVector<double> bestPosition() const{
        return m_bestPosition;
    }
signals:
    /**
     * @brief Current iteration changed.
     *
     * At the end of the step performance, this signal
     *  is emitted with the current run,
     *  the current iteration and the best fitness
     * to be displayed in the GUI.
     * @param run Current run
     * @param iteration Current iteration
     * @param fitness_value Best fitness of the iteration
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void currentIterationChanged(int run, int iteration, double fitness_value);
    /**
     * @brief Reset requested.
     *
     *  The reset impacts all AbstractVisualisation's children.
     * These reset their graph and variables.
     * \author Lucien XU
     */
    void resetRequested();
    /**
     * @brief Update requested.
     *
     * The step performed, the visualizations should be updated with the new swarm data.
     * \author Lucien XU
     */
    void stepped();
    /**
     * @brief A new effective range is set
     *
     * This signal is emitted when the user set a sub-interval
     * of iterations.
     * @param min First iteration
     * @param max Last iteration
     * \author Guillaume Jornod
     */
    void newRange(int min, int max);
    /**
     * @brief Maximum of the maximum range iteration
     *
     * @param max New maximum number of iterations
     * \author Guillaume Jornod
     */
    void newRealMax(int max);
    /**
     * @brief Stop of the simulation
     *
     * This signal is emitted when the simulation stopped
     * before the last iteration due to a
     * problem in the file reading.
     *
     * This triggers the unpush of the simulation button.
     * \author Guillaume Jornod
     */
    void emergencyStop();
public slots:
    /**
     * @brief Sets the maximum iterations
     *
     * Set the maximum iteration of the simulations. Depending on the doReset argument,
     * the simulation is restarted or not.
     * @param maxIterations Maximum iterations to set.
     * @param doReset Reset after setting
     *
     * \author Lucien Xu
     * \author Guillaume Jornod
     */
    void setMaxIterations(int maxIterations, bool doReset = true);
    /**
     * @brief Sets the effective maximum iteration
     *
     * This slot receives the maximum iteration set by the user
     * in the iteration range.
     * @param maxIterations Maximum iteration
     * \author Guillaume Jornod
     */
    void setEffectiveMaxIterations(int maxIterations);
    /**
     * @brief Sets the first iteration
     *
     * This slot receives the first iteration set by the user
     * in the iteration range.
     * @param minIterations First iteration
     * \author Lucien XU
     */
    void setMinIterations(int minIterations);
    /**
     * @brief Sets the dimension of the problem
     *
     * This slot receives the number of dimensions
     * of the problem. Depending on the doReset argument
     * the simulation will be restarted.
     * @param dimension Dimension to set.
     * @param doReset Reset after setting
     * \author Lucien Xu
     * \author Guillaume Jornod
     */
    void setDimension(int dimension, bool doReset = true);
    /**
     * @brief Sets the size of the swarm
     *
     * This slot receives the size of the swarm. Depending on the doReset argument
     * the simulation will be restarted.
     * @param size Size to set.
     * @param doReset Reset after setting
     * \author Lucien Xu
     * \author Guillaume Jornod
     */
    void setSize(int size, bool doReset = true);
    /**
     * @brief Sets the minimum value of the position.
     *
     * This slot receives the minimum value defining
     * the initial hyper-cube. Depending on the doReset argument
     * the simulation will be restarted.
     * @param minimum Minimum value of the position.
     * @param doReset Reset after setting
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void setMinimum(double minimum, bool doReset = true);
    /**
     * @brief Sets the maximum value of the position.
     *
     * This slot receives the maximum value defining
     * the initial hyper-cube. Depending on the doReset argument
     * the simulation will be restarted.
     * @param maximum Maximum value of the position.
     * @param doReset Reset after setting
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void setMaximum(double maximum, bool doReset = true);
    /**
     * @brief Sets the maximum velocity
     *
     * Depending on the doReset argument, the simulation will be restarted.
     * @param maximumVelocity Maximum velocity.
     * @param doReset Reset after setting
     */
    void setMaximumVelocity(double maximumVelocity, bool doReset = true);
    /**
     * @brief Sets inertia
     *
     * Depending on the doReset argument, the simulation will be restarted.
     * @param inertia inertia.
     * @param doReset Reset after setting
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void setInertia(double inertia, bool doReset = true);
    /**
     * @brief Sets fitness function index
     *
     * Depending on the doReset argument, the simulation will be restarted.
     * @param index fitness function index.
     * @param doReset Reset after setting
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void setFitnessFunctionIndex(int index, bool doReset = true);
    /**
     * @brief Sets timer interval
     * @param interval Interval.
     * \author Lucien XU
     */
    void setTimerInterval(int interval);
    /**
     * @brief Run or stop the simulation
     * @param running If the simulation should be run or stopped
     * \author Lucien XU
     */
    void setRunning(bool running);
    /**
     * @brief Performs a step
     * \author Lucien Xu
     * \author Guillaume Jornod
     */
    void step();
     /**
     * @brief Perform a step back.
     *
     * This function decrements the iteration counter and step the simulation.
     * \author Guillaume Jornod
     */
    void stepb();

    /**
     * @brief Restart
     *
     * This method creates or reset a swarm.
     * It is used to restart a simulation.
     * The boolean argument is used to refresh or not the visualizations.
     *
     * @param refresh Refresh or not the visualizations
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void restart(bool refresh = true);
    /**
     * @brief Reset
     *
     * This method resets everything, including the
     * number of iterations.
     * \author Lucien Xu
     */
    void reset();
    /**
     * @brief Sets the local best coefficient.
     *
     * Depending on the doReset argument, the simulation will be restarted.
     * @param localWeight Local best coefficient
     * @param doReset Reset after setting
     * \author Guillaume Jornod
     */
    void setLocalBestWeight(double localWeight, bool doReset = true);
    /**
     * @brief Sets the neighbor best coefficient.
     *
     * Depending on the doReset argument, the simulation will be restarted.
     * @param neighbourWeight Neighbor best coefficient
     * @param doReset Reset after setting
     * \author Guillaume Jornod
     */
    void setNeighbourBestWeight(double neighbourWeight, bool doReset = true);
    /**
     * @brief Set the number of neighbors
     *
     * The number of neighbor is set in the GUI as the total number of neighbors. It is then converted
     * into the number of neighbors at each side of the particle.
     * Depending on the doReset argument, the simulation will be restarted.
     * @param neighbourNumber Number of neighbors
     * @param doReset Reset after setting
     * \author Guillaume Jornod
     */
    void setNeighbourNumber(int neighbourNumber, bool doReset = true);
    /**
     * @brief Sets the file manager.
     *
     * Sets the pointer to the Screenshots instance used to manage the files.
     * @param screenshot Screenshots instance
     * \author Guillaume Jornod
     */
    void setScreenshot(const Screenshots * screenshot);
    /**
     * @brief Sets the standard deviation of the noise.
     *
     * In the noise addition process, the standard deviation is used to quantify the amplitude of the noise added.
     * Depending on the doReset argument, the simulation will be restarted.
     * @param sigma Standard deviation of the noise.
     * @param doReset Reset after setting
     * \author Guillaume Jornod
     */
    void setNoise(const double sigma, bool doReset = true);
    /**
     * @brief Activates the noise resistance feature in the algorithm
     * @param noiseResistance Enable or disable the noise resistance feature.
     * \author Guillaume Jornod
     */
    void setNoiseResistance(bool noiseResistance);
   private:
    /**
     * @brief Last iteration
     *
     * This parameter defines the last iteration, which could be different from the maximum iteration parameter.
     * The simulation will stop at this iteration.
     * \author Guillaume Jornod
     */
    int m_effectiveMaxIterations;
    /**
     * @brief First iteration.
     *
     * This parameter is -1 by default, but can be changed by the iteration range option in the GUI.
     * \author Lucien XU
     */
    int m_minIteration;
    /**
     * @brief Maximum iteration
     *
     * This parameter is defined either in the simulation setup or in the pso_params file.
     * It is the theoric last iteration, but can be overwritten by the m_effectiveMaxIterations parameter.
     * \author Lucien XU
     */
    int m_maxIterations;
    /**
     * @brief Dimensionality of the problem.
     * \author Lucien XU
     */
    int m_dimension;
    /**
     * @brief Size of the swarm.
     * \author Lucien XU
     */
    int m_size;
    /**
     * @brief Minimum of the initial hyper-cube.
     * \author Lucien XU
     */
    double m_minimum;
    /**
     * @brief Maximum of the initial hyper-cube.
     * \author Lucien XU
     */
    double m_maximum;
    /**
     * @brief Maximum velocity.
     * \author Lucien XU
     */
    double m_maximumVelocity;
    /**
     * @brief Inertia.
     * \author Lucien XU
     */
    double m_inertia;
    /**
     * @brief Fitness function index.
     * \author Lucien XU
     */
    int m_fitnessFunctionIndex;
    /**
     * @brief Number of iterations already performed.
     * \author Lucien XU
     */
    int m_iterations;
    /**
     * @brief Number of runs.
     * \author Lucien XU
     */
    int m_runs;
    /**
     * @brief Fitness list.
     *
     * This list contains the fitness values for each iteration. It is used by the FitnessVisualisation graph.
     * \author Lucien XU
     */
    QList<FitnessMap> m_fitnessList;

    /**
     * @brief Swarm instance
     * \author Lucien XU
     */
    Swarm *m_swarm;
    /**
     * @internal
     * @brief Timer
     * \author Lucien XU
     */
    QTimer *m_timer;
    /**
     * @brief Local best weight.
     * \author Guillaume Jornod
     */
    double m_localWeight;
    /**
     * @brief Neighbor best weight.
     * \author Guillaume Jornod
     */
    double m_neighbourWeight;
    /**
     * @brief Number of neighbors used in to update best neighbor position.
     * \author Guillaume Jornod
     */
    int m_neighbours;
    /**
     * @brief Value to display in the control panel
     *
     * This value is different from the best fitness in the fitness map, since the fitness map contains the felt performance,
     * that is, in a noisy simulation, the fitness with noise. The fitness reported should be the real, non-noisy performance.
     * \author Guillaume Jornod
     */
    double m_fitness_value;
    /**
     * @brief Direction of the simulation forward / backward
     *
     * When the step back feature is used, the simulation is set to backward, and the iterations are decremented.
     * \author Guillaume Jornod
     */
    bool m_simulationDirection;
     /**
     * @brief File management instance.
     * \author Guillaume Jornod
     */
    const Screenshots *m_screenshot;
    /**
     * @brief Standard deviation of the gaussian noise.
     *
     * The noise is computed with this value and then added to the fitness value.
     * \author Guillaume Jornod
     */
    double m_noise;
    /**
     * @brief PSO with or without noise resistance.
     * \author Guillaume Jornod
     */
    bool m_noiseResistance;
    /**
     * @brief Bets position of the iteration.
     *
     * This vector contains the position of the particle having the best performance
     * of the iteration. This vector is then used by the BestVisualisation.
     */
    QVector<double> m_bestPosition;


};

#endif // SWARMMANAGER_H
