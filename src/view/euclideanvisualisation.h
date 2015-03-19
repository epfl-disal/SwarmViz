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
#ifndef EuclideanVISUALISATION_H
#define EuclideanVISUALISATION_H

/**
 * @file euclideanvisualisation.h
 * @short Definition of class EuclideanVisualisation
 */

#include "abstractvisualisation.h"
#include "qcustomplot/qcustomplot.h"
#include "../pso/particle.h"

/**
 * @brief Visualization of the Euclidean distance
 *
 * This class provides the methods to compute and
 * display the euclidean distance bewteen the particles at
 * each iteration.
 */
class EuclideanVisualisation : public AbstractVisualisation
{
    //Q_OBJECT
public:
    /**
     * @brief Constructor
     *
     * The title is set, as well as the axis names and the output snapshat file name.
     * @param parent Parent widget.
     */
    explicit EuclideanVisualisation(QWidget *parent = 0);
    /**
     * @brief Performs the compuutations step
     *
     * This method first cleans the graph and computes the euclidean distances between each particles.
     *
     * The average distance is then computed and stored. If the graph is visible, all the mean euclidean distances
     * are reported on the graph against the iterations.
     */
    void performStepComputation();
    /**
     * @brief Resets the visualization
     *
     * The distances stored are cleared.
     */
    void reset();

private:
    /**
     * @brief Title of the plot
     */
    QCPPlotTitle* m_title;
    /**
     * @brief Abscissa data (iterations)
     */
    QVector<double> m_x;
    /**
     * @brief Ordinate data (euclidean distance)
     */
    QVector<double> m_y;
    /**
     * @brief Computes the euclidean distance between two particles
     *
     * The distance is computed as \f$
     * \sqrt { \sum\limits _{j=1} ^d (x_{1i} - x_{2j})^2 }
     * \f$
     * @param p1 First particle
     * @param p2 Second particle
     * @return Distance between the two particles
     */
    double partDist(const Particle *p1, const Particle *p2);

};

#endif // EuclideanVISUALISATION_H
