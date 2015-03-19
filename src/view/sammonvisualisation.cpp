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

#include "sammonvisualisation.h"
#include "../pso/swarm.h"
#include "../pso/psohelper.h"
#include "../sammon/codegen/dll/sammon/sammon.h"
#include "../sammon/codegen/dll/sammon/sammon_emxAPI.h"
#include "visualisationhelper.h"
#include <cmath>
#include <QtGui/QPainter>
#include <QtCore/QDebug>

/**
  * @file sammonvisualisation.cpp
  * @short Implementation of the class SammonVisualisation
  **/

SammonVisualisation::SammonVisualisation(QWidget *parent):
    AbstractVisualisation(parent)
{
    m_title = new QCPPlotTitle(this, "Sammon's Mapping");
    plotLayout()->addElement(0, 0, m_title);
    m_titlePlot = "sammon";

}

SammonVisualisation::~SammonVisualisation()
{

}

void SammonVisualisation::performStepComputation()
{
    // do not perform painting if not visible
    if(!isVisible())
        return;
    clearGraphs();

    emxArray_real_T *lSpacePositions;
    emxArray_real_T *dSpacePositions;
    lSpacePositions = emxCreate_real_T(swarm()->size(), swarm()->dimension());
    dSpacePositions = emxCreate_real_T(swarm()->size(), 2);

    for (int i = 0; i < swarm()->size(); i++)
        for (int j = 0; j < swarm()->dimension(); j++)
        {
            double tmp = ((*swarm())[i]->position[j]);
            lSpacePositions->data[i*swarm()->dimension()+j] = tmp;
        }

    sammon(lSpacePositions,dSpacePositions);

    QVector<double> x, y;
    for (int i = 0; i < swarm()->size(); i++)
    {
        x << dSpacePositions->data[i*2];
        y << dSpacePositions->data[i*2 + 1];
    }
    addGraph();
    graph()->setData(x, y);

    rescaleAxes(true);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    graph()->setLineStyle(QCPGraph::lsNone);
    replot();


}
