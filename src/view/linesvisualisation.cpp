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
 * @file linesvisualisation.cpp
 * @short Implementation of class LinesVisualisation
 */

#include "linesvisualisation.h"
#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include "../pso/swarm.h"
#include "visualisationhelper.h"
static const double MARGIN_X = 40.0;
static const double MARGIN_Y = 40.0;

LinesVisualisation::LinesVisualisation(QWidget *parent) :
    AbstractVisualisation(parent)
{

    plotLayout()->addElement(0, 0, new QCPPlotTitle(this, "Parallel coordinates"));
    xAxis->setLabel("Dimension");
    yAxis->setLabel("Position");
    m_titlePlot = "parallelCoordinates";

}
void LinesVisualisation::performStepComputation()
{

    // do not perform painting if not visible
    if(!isVisible())
        return;

    clearGraphs();
    QVector<double> x, y;

    // Paint the best
    for (int i = 0; i < swarm()->size(); i++) {
        const Particle *particle = (*swarm())[i];
        x.clear();
        y.clear();
        y = particle->position;
        for (int j = 0; j < swarm()->dimension(); j++) {
            x.append(j + 1);
        }
        addGraph();
        graph(i)->setData(x, y);
        graph(i)->setPen(VisualisationHelper::rainbowCoding(i, swarm()->size()));
    }
    xAxis->setRange(0, swarm()->dimension());
    if (swarm()->dimension() < 20)
    {
        xAxis->setAutoTickStep(false);
        xAxis->setTickStep(1);
    }
    rescaleAxes(true);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    replot();
}
