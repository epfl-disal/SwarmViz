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
#include "euclideanvisualisation.h"
#include "../pso/particle.h"
#include "../pso/swarm.h"
#include <QtGui/QPainter>

/**
 * @file euclideanvisualisation.cpp
 * @short Implementation of class EuclideanVisualisation
 */



EuclideanVisualisation::EuclideanVisualisation(QWidget *parent) :
    AbstractVisualisation(parent)
{

    m_title = new QCPPlotTitle(this, "Euclidean Distance");
    plotLayout()->addElement(0, 0, m_title);
    xAxis->setLabel("Iteration");
    yAxis->setLabel("Distance");
    m_titlePlot = "euclidean";

}



void EuclideanVisualisation::performStepComputation()
{
    clearGraphs();
    if(swarm()->iteration() == -1)
        reset();

    double avg_dist = 0.0;
    for (int i = 0; i < swarm()->size(); i++) {
        for (int j = i+1; j < swarm()->size(); j++){
            const Particle * p1 = (*swarm())[i];
            const Particle * p2 = (*swarm())[j];
            avg_dist += partDist(p1, p2);
        }
    }
    avg_dist/= swarm()->size()*(swarm()->size()-1)/2;
    m_x.append(swarm()->iteration());
    m_y.append(avg_dist);

    // do not perform painting if not visible
    if(!isVisible())
        return;

    addGraph(0);
    graph(0)->setData(m_x, m_y);
    /*
    xAxis->setRange(0, maxIterations());
    yAxis->setRange(0, m_y.first());
    */
    rescaleAxes(true);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    replot();

}

double EuclideanVisualisation::partDist(const Particle * p1, const Particle * p2)
{
    double dist = 0.0;
    int i;

    for (i = 0; i < swarm()->dimension() ; i++)
        dist += (p1->position[i]-p2->position[i])*(p1->position[i]-p2->position[i]);
    dist = sqrt(dist);

    return dist;
}

void EuclideanVisualisation::reset()
{
    m_x.clear();
    m_y.clear();
}
