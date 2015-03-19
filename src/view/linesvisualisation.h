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

#ifndef LINESVISUALISATION_H
#define LINESVISUALISATION_H

/**
 * @file linesvisualisation.h
 * @short Definition of class LinesVisualisation
 */

#include "abstractvisualisation.h"
#include "qcustomplot/qcustomplot.h"

/**
 * @brief Visualisation using the parallel lines graph
 *
 * The parallel coordinates plot is an old multi-dimensional
 * visualization tool introduced by \cite ocagne1885coordonnee.
 * This plot is largely used in environmental geo-visualization
 * to visualize temperature time series for instance.
 *
 * While ordinate denotes particles in the density plot,
 * it represents values in the parallel coordinates plot.
 * The particles are represented by poly-lines which vertices
 * are values in the corresponding dimension.
 *
 * In addition to its original purpose, the overview
 * of the particles positions in all dimension, parallel
 * coordinates plot is also useful to detect convergence:
 * overlapping vertices represent equal values in the
 * corresponding dimension and overlapping poly-lines
 * convergence of the algorithm.
 *
 * \author Guillaume Jornod
 * \author Lucien XU
 */
class LinesVisualisation : public AbstractVisualisation
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     *
     * Sets the plot title, the axis names and the ouput file name
     * @param parent Parent widget.
     * \author Guillaume Jornod
     */
    explicit LinesVisualisation(QWidget *parent = 0);
    /**
     * @brief Performs the computations of the step
     *
     * The function is aborted if the widget is not visible.
     *
     * The plot is first cleared. Then, each particle is denoted by a graph
     * and for each dimension, a point is added in the graph at (dimension, position).
     *
     * \author Guillaume Jornod
     * \author Lucien XU
     */
    void performStepComputation();
};

#endif // LINESVISUALISATION_H
