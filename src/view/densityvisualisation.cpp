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
 * @file densityvisualisation.cpp
 * @short Implementation of class DensityVisualisation
 */

#include "densityvisualisation.h"
#include "../pso/swarm.h"
#include "visualisationhelper.h"

DensityVisualisation::DensityVisualisation(QWidget *parent) :
    AbstractVisualisation(parent)
{
    m_title = new QCPPlotTitle(this, "Density Plot");
    plotLayout()->addElement(0, 0, m_title);
    xAxis->setLabel("Dimension");
    yAxis->setLabel("Particle");
    m_titlePlot = "density_plot";
    m_type = INITIAL;
    m_pen = new QPen();
    m_pen->setWidth(0);
    m_pen->setColor(Qt::white);
}

void DensityVisualisation:: performStepComputation()
{
    double color;
    int colorInt;

    // do not perform painting if not visible
    if(!isVisible())
        return;

    QCPItemRect* parentRect;
    parentRect = new QCPItemRect(this);
    parentRect->bottomRight->setCoords(swarm()->dimension()+1, -1);
    parentRect->topLeft->setCoords(-1, swarm()->size()+1);
    parentRect->setVisible(false);
    parentRect->setPen(*m_pen);
    if((!m_heatMap.size() || !m_heatMap[0].size()) || (m_heatMap.size() != swarm()->size() || m_heatMap[0].size() != swarm()->dimension() ) )
    {
        clearItems();
        m_heatMap.clear();
        // Iterate over swarm
        for(int i = 0; i < swarm()->size(); i++)
        {
            QList<QCPItemRect* > row;
            // Iterate over dimension
            for(int j = 0; j < swarm()->dimension(); j++)
            {
                QCPItemRect* rect;
                rect = new QCPItemRect(this);
                rect->setParentLayerable(parentRect);
                rect->bottomRight->setCoords(j+1.5, i+0.5);
                rect->topLeft->setCoords(j+0.5, i+1.5);
                //rect->setPen(*pen);
                row.append(rect);
            }
            m_heatMap.append(row);
        }
    }
    {
        double min;
        double max;
        getMinMax(&min, &max);

        for(int i = 0; i < swarm()->size(); i++)
        {
            const Particle *particle = (*swarm())[i];
            // Iterate over dimension
            for(int j = 0; j < swarm()->dimension(); j++)
            {
                color = (particle->position[j] - min) / (max - min);
                colorInt = qBound(0, (int) (255 * color), 255);
                m_heatMap[i][j]->setBrush(QBrush(QColor(colorInt, colorInt, colorInt)));
            }
        }
    }

    parentRect->setVisible(true);
    xAxis->setRange(0.5, swarm()->dimension()+0.5);
    if (swarm()->dimension() < 20)
    {
        xAxis->setAutoTickStep(false);
        xAxis->setTickStep(1);
    }
    yAxis->setRange(0.5, swarm()->size() + 0.5);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    replot();
}

void DensityVisualisation::reset(){
    clearItems();
    clearGraphs();
    m_heatMap.clear();
    replot();
}

void DensityVisualisation::setScalingType(int type)
{
    m_type = type;
}

void DensityVisualisation::getMinMax(double *min, double *max)
{
    switch(m_type)
    {
    case INITIAL:
        *min = swarm()->minimum();
        *max = swarm()->maximum();
        break;
    case GLOBAL:
        *min = m_screenshot->m_globalRange[0];
        *max = m_screenshot->m_globalRange[1];
        break;
    case INSTANT:
        swarm()->getMinMaxPos(min, max);
    }

}
