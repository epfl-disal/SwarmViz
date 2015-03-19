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
 * @file trajectoryvisualisation.cpp
 * @short Implementation of class TrajectoryVisualisation
 */

#include "trajectoryvisualisation.h"


#include <QtCore/QDebug>
#include "../pso/swarm.h"
#include "visualisationhelper.h"
#include "qcustomplot/qcustomplot.h"


/**
 * @brief LIMIT
 *
 * Number of points in the trajectory.
 */
static const int LIMIT = 10;
static const int DIM1_DEFAULT= 0;
static const int DIM2_DEFAULT= 1;

TrajectoryVisualisation::TrajectoryVisualisation(QWidget *parent):
    AbstractVisualisation(parent)
{
    m_abscissa = DIM1_DEFAULT;
    m_ordinate = DIM2_DEFAULT;
    m_previousPosition = LIMIT;
    m_valueRange[0] = 0;
    m_valueRange[1] = 1;

    // Set title
    QString title;
    title =  "Trajectory Visualization";
    m_titlePlot = "trajectories";
    plotLayout()->addElement(0, 0, new QCPPlotTitle(this, title ));
    m_type = TRAJECTORY;

    // Set axis label
    xAxis->setLabel("Dimension " + QString::number(m_abscissa + 1));
    yAxis->setLabel("Dimension " + QString::number(m_ordinate + 1));
}

void TrajectoryVisualisation::reset()
{
    // Clear all trajectories
    m_trajectories.clear();
    for (int i = 0; i < swarm()->size(); i++) {
        m_trajectories.append(QList<QList<double> >());
    }
    clearGraphs();
}

void TrajectoryVisualisation::performStepComputation()
{
    double min;
    double max;

    if(swarm()->iteration() == -1)
        reset();

    if (m_type == FITNESS_LANDSCAPE)
        getMinMaxFitness(&min, &max);

    // Fill trajectories list if needed
    if (m_trajectories.size() != swarm()->size()) {
        m_trajectories.clear();
        for (int i = 0; i < swarm()->size(); i++) {
            m_trajectories.append(QList<QList<double> >());
        }
    }
    clearGraphs();

    // Iterate over swarm
    QList<double> coords;
    for (int i = 0; i < swarm()->size(); i++) {
        QVector<double> x(m_previousPosition), y(m_previousPosition);
        addGraph();
        const Particle *particle = (*swarm())[i];
        coords.clear();
        for(int z = 0; z < swarm()->dimension(); z ++)
            coords.append(particle->position[z]);
        //                                int avoidZeroPosition = LIMIT - swarm()->i
        m_trajectories[i].append(coords);
        while (m_trajectories[i].size() > m_previousPosition) {
            m_trajectories[i].removeFirst();
        }
        // Avoid line to 0 at the beginning
        while(m_trajectories[i].size() <m_previousPosition)
            m_trajectories[i].append(coords);

        // do not perform painting if not visible
        if(!isVisible())
            continue;

        for (int j = 0; j < m_trajectories[i].size(); j++)
        {
            x[j] = m_trajectories[i][j][m_abscissa];
            y[j] = m_trajectories[i][j][m_ordinate];
        }


        graph(i)->setData(x, y);
        if (m_type == TRAJECTORY)
            graph(i)->setPen(QPen(VisualisationHelper::rainbowCoding(i, swarm()->size())));
        else if (m_type == FITNESS_LANDSCAPE)
            graph(i)->setPen(QPen(VisualisationHelper::rainbowCoding(i, swarm()->size(), swarm()->performance(), min, max)));
        graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1));
    }
    rescaleAxes(true);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    replot();

}

void TrajectoryVisualisation::setAbscissa(int abscissa)
{
    m_abscissa = abscissa - 1;
    // Set axis label
    xAxis->setLabel("Dimension " + QString::number(abscissa));
    performStepComputation();
}

void TrajectoryVisualisation::setOrdinate(int ordinate)
{
    m_ordinate = ordinate - 1;
    // Set axis label
    yAxis->setLabel("Dimension " + QString::number(ordinate));
    performStepComputation();
}

void TrajectoryVisualisation::setPreviousPosition(int num)
{
    m_previousPosition = num;
}

void TrajectoryVisualisation::setColoration(bool col)
{
    if(col)
        m_type = FITNESS_LANDSCAPE;
    else
        m_type = TRAJECTORY;
}

void TrajectoryVisualisation::setScalingType(int colorationType)
{
    m_coloring = colorationType;
}

void TrajectoryVisualisation::getMinMaxFitness(double *min, double *max)
{
    switch(m_coloring)
    {
    case INITIAL:
        swarm()->getMinMaxInitialFitness(min, max);
        break;
    case GLOBAL:
        *min = m_screenshot->m_globalRangeFitness[0];
        *max = m_screenshot->m_globalRangeFitness[1];
        break;
    case RANGE:
        *min = m_valueRange[0];
        *max = m_valueRange[1];
        break;
    case INSTANT:
        const double *perf = swarm()->performance();
        *min = 100000;
        *max = -100000;
        for (int i = 0; i < swarm()->size(); i++)
        {
            if (*min > perf[i])
                *min = perf[i];
            if (*max < perf[i])
                *max = perf[i];
        }
    }
}

void TrajectoryVisualisation::setMax(int value)
{
    m_valueRange[1] = value;
}

void TrajectoryVisualisation::setMin(int value)
{
    m_valueRange[0] = value;
}
