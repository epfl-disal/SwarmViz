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


#include "pbestvisualisation.h"
#include "../pso/swarm.h"
#include "visualisationhelper.h"

BestVisualisation::BestVisualisation(QWidget *parent):
    AbstractVisualisation(parent)
{
    m_title = new QCPPlotTitle(this, "Best Graph");
    plotLayout()->addElement(0, 0, m_title);
    m_titlePlot = "bestgraph";

}

void BestVisualisation::performStepComputation()
{
    if (graphCount() != swarm()->dimension() || swarm()->iteration() == -1)
        reset();

    m_Best << m_swarmManager->bestPosition();
    for (int j = 0; j <  swarm()->dimension() ; j++)
    {
        graph(j)->addData(swarm()->iteration(),m_Best[swarm()->iteration()+1][j]);
    }
    if(!isVisible())
        return;

    rescaleAxes(true);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    replot();
}

void BestVisualisation::reset(){
    clearGraphs();
    m_Best.clear();

    for (int j = 0; j < swarm()->dimension(); j++)
    {
        addGraph();
        graph()->setPen(QPen(VisualisationHelper::rainbowCoding(j, swarm()->dimension())));
        graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
        //graph()->setLineStyle(QCPGraph::lsNone);
    }
}
