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

#ifndef SAMMONVISUALISATION_H
#define SAMMONVISUALISATION_H
/**
  * @file sammonvisualisation.h
  * @short Definition of the class SammonVisualisation
  */

#include "abstractvisualisation.h"
/**
 * @brief Visualization of the Sammon's mapping
 *
 * Sammon's mapping is an algorithm that maps a high dimensional
 * space to a lower dimensional space attempting to preserve
 * the topology of the points \cite sammon1969nonlinear.
 * This preservation is done by minimizing a metric, called Sammon's stress:
 * \f[
 * E = \frac{1}{\sum\limits_{i<j} \delta_{ij}}\sum\limits_{i<j}\frac{(\delta_{ij}-d_{ij})^2}{\delta_{ij}}
 * \f]
 * Where \f$\delta_{ij}\f$ and \f$d_{ij}\f$ denote the distance in the d-dimensional space and in the resulting 2-dimensional space respectively.
 *
 * The implementation uses the Matlab method for the Sammon's mapping in the Toolbox
 * for dimensionality reduction \cite van2007matlab, adapted to the project
 * using Coder, a feature of \cite MATLAB2013.
 *
 * \author Guillaume Jornod
 */
class SammonVisualisation : public AbstractVisualisation
{
    Q_OBJECT
public:
    /**
 * @brief Constructor of the class SamonVisualisation.
 *
 * The constructor sets the title of the plot and the output filename.
 * @param parent
 */
    explicit SammonVisualisation(QWidget *parent = 0);
    virtual ~SammonVisualisation();
public slots:
    /**
     * @brief Performs the computation for the step
     *
     * If the widget is not visible, this method does nothing. Else, it
     * formats the data of the swarm into the Matlab coder format
     * to use the created library.
     *
     * \author Guillaume Jornod
     */
    virtual void performStepComputation();
private:
    /**
     * @brief Title of the plot.
     */
    QCPPlotTitle* m_title;




};

#endif // SAMMONVISUALISATION_H
