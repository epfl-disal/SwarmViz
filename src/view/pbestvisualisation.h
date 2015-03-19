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

#ifndef PBESTVISUALISATION_H
#define PBESTVISUALISATION_H

#include "abstractvisualisation.h"

/**
 * @brief Visualization of the best particle's position
 *
 * This graph reports the position of the best particle
 * of all iterations. This visualization is an
 * adaptation of the Best individual presented
 * by \cite pohlheim1999visualization for the GA.
 *
 * A variable, which is a dimension, is represented
 * by a line, whose vertices denote a value.
 * It is notable that the best particle is the particle
 * with the best felt performance, which is the
 * performance with noise. In a non-noisy fitness
 * case, the fitness of this particle is reported
 * as the best fitness in the fitness plot.
 *
 * This visualization is useful to observe the
 * convergence of the algorithm. The best particle
 * is also a good indicator of the state of the
 * algorithm, the best particle being a kind
 * of guide for the other particles, especially
 * in a global neighborhood case with a large
 * neighbor weight.
 *
 * \author Guillaume Jornod
 */
class BestVisualisation : public AbstractVisualisation
{
    Q_OBJECT
public:
    BestVisualisation(QWidget *parent = 0);
public slots:
    /**
     * @brief Performs computations of the step
     *
     * Inserts iteration bes position in the array and then plots the values.
     * \author Guillaume Jornod
     */
    virtual void performStepComputation();
    /**
     * @brief Resets
     *
     * Clears the graphs and empties the array.
     * \author Guillaume Jornod
     */
    void reset();
private:
    /**
     * @brief Title of the plot
     */
    QCPPlotTitle* m_title;
    /**
     * @brief Array containing all best positions for each iteration.
     */
    QList<QVector<double> > m_Best;

};

#endif // PBESTVISUALISATION_H
