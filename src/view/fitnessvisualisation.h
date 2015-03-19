/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef FITNESSVISUALISATION_H
#define FITNESSVISUALISATION_H

/**
 * @file fitnessvisualisation.h
 * @short Definition of class FitnessVisualisation
 */

#include "abstractvisualisation.h"
#include "qcustomplot/qcustomplot.h"

class QPainter;

/**
 * @brief Visualization based on fitness
 *
 * The learning process is the minimization or the
 * maximization of a fitness function.
 * This fitness function is used to evaluate the
 * performance of the particles of the swarm.
 * The fitness visualization is a plot of either
 * the mean performance and the best particle's
 * performance or all particles' performance
 * against the iteration.
 *
 * \author Lucien XU
 * \author Guillaume Jornod
 */
class FitnessVisualisation : public AbstractVisualisation
{
public:
    /**
     * @brief Display style
     */
    enum DisplayStyle {
        /**
         * @short Display only the best and average fitness
         */
        StyleBestAndAverage,
        /**
         * @short Display all the fitness
         */
        StyleAll
    };
    /**
     * @brief Default constructor
     *
     * The constructor sets the default mode, best and average, as well as
     * the plot title, the axis names and the output file name.
     * @param parent parent widget.
     *
     * \author Guillaume Jornod
     */
    explicit FitnessVisualisation(QWidget *parent = 0);
    /**
     * @brief Performs the computations of the step
     *
     * This method calls either paintBestAndAverage() or paintAll() depending
     * on the mode.
     *
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void performStepComputation();

public slots: 
    /**
     * @brief Sets display style
     * @param displayStyle All / Best and average
     */
    void setDisplayStyle(bool displayStyle);
private:
    /**
     * @brief Paints the best and average fitness graph
     *
     * This method simply computes the average fitness of the iteration
     * and plots it with the best one. The average is drawn in blue and the
     * best in red.
     *
     * A possible improvement should be not to compute the average
     * and best at each iteration but to store them.
     * @param fitnessMap Fitness map to use.
     *
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void paintBestAndAverage(const FitnessMap &fitnessMap);
    /**
     * @brief Paints all fitness graph
     *
     * This method simply paints all the performances against the iterations.
     * @param fitnessMap Fitness map to use.
     */
    void paintAll(const FitnessMap &fitnessMap);
    /**
     * @brief Display style
     */
    DisplayStyle m_displayStyle;
    /**
     * @brief Title of the plot
     */
    QCPPlotTitle* m_title;

};

#endif // FITNESSVISUALISATION_H
