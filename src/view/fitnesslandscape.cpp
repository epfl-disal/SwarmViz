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
#include "fitnesslandscape.h"

#include <QtCore/QDebug>
#include "../pso/swarm.h"
#include "visualisationhelper.h"
#include "qcustomplot/qcustomplot.h"
/**
 * @file fitnesslandscape.cpp
 * @short Implementation of class FitnessLandscape
 */




static const int DIM1_DEFAULT= 0;
static const int DIM2_DEFAULT= 1;
static const int GRAPH_NUM = 100;

struct QPairFirstComparer
{
    template<typename T1, typename T2>
    bool operator()(const QPair<T1,T2> & a, const QPair<T1,T2> & b) const
    {
        return a.first < b.first;
    }
};


FitnessLandscape::FitnessLandscape(QWidget *parent) :
    AbstractVisualisation(parent)
{
    m_abscissa = DIM1_DEFAULT;
    m_previousAbscissa = DIM1_DEFAULT;
    m_ordinate = DIM2_DEFAULT;
    m_previousOrdinate = DIM2_DEFAULT;

    // Set title
    m_titlePlot = "fitness_landscape";
    plotLayout()->addElement(0, 0, new QCPPlotTitle(this, "Fitness Lanscape"));

  //  setInteraction(QCP::iRangeDrag, true);
   // setInteraction(QCP::iRangeZoom, true);
    yAxis->setLabel("Dimension " + QString::number(m_ordinate + 1));
    xAxis->setLabel("Dimension " + QString::number(m_abscissa + 1));

    m_valueRange[0] = 0;
    m_valueRange[1] = 1000;
    recomputeScale();

}

void FitnessLandscape::performStepComputation()
{

    if(swarm()->iteration() == -1)
        reset();
    // Fill trajectories list if needed
    if (m_trajectories.size() != GRAPH_NUM) {
        m_trajectories.clear();
        for (int i = 0; i < GRAPH_NUM; i++)
            m_trajectories.append(QList<QList<QVector<double> > >());
    }


    // Initialize iteration in trajectories
    for (int i = 0; i < GRAPH_NUM; i++)
    {
       m_trajectories[i].append(QList<QVector<double> >());
       // Initialize dimension
       for (int j = 0; j < swarm()->dimension(); j++)
       {
           m_trajectories[i][swarm()->iteration()+1].append(QVector<double>());
       }
    }


    // If dimensions changed, clear the graph
    if (m_previousOrdinate != m_ordinate || m_previousAbscissa != m_abscissa)
        clearGraphs();

/*
    // Sort the performances
    QList<QPair<double, int> > sortedPeformances;
    sortedPeformances = sortPerformances(swarm()->performance());
*/
    // Check if there is one graph per particle (actually, one graph per performance rank)
    if(graphCount() != GRAPH_NUM)
    {
        clearGraphs();
        for (int i = 0; i < GRAPH_NUM; i++)
        {
            addGraph();
            graph()->setPen(QPen(VisualisationHelper::rainbowCoding(i, GRAPH_NUM, m_scale, m_valueRange[0], m_valueRange[1])));
            graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
            graph()->setLineStyle(QCPGraph::lsNone);
        }
    }


    // Iterate over swar and append all trajectories
    for (int i = 0; i < swarm()->size(); i++) {
        // Data will not be added by particle, but one performance rank per graph
        for(int j=0; j < GRAPH_NUM; j++)
        {
            if ((swarm()->getPerformance(i) >= m_scale[j] && swarm()->getPerformance(i) < m_scale[j+1]) || (j == 0 && swarm()->getPerformance(i) < m_scale[j]) || (j == GRAPH_NUM-1 && swarm()->getPerformance(i) > m_scale[GRAPH_NUM]))
                for (int k = 0; k < swarm()->dimension(); k++)
                    m_trajectories[j][swarm()->iteration()+1][k].append((*swarm())[i]->position[k]);
         }

    }


    // Insert data in the graph
    QVector<double> x;
    QVector<double> y;
    int it = swarm()->iteration() + 1;
    for (int i = 0; i < GRAPH_NUM; i++)
    {
        x.clear();
        y.clear();
        // Dimension did not change: just add the current iteration
        if (m_previousOrdinate == m_ordinate && m_previousAbscissa == m_abscissa)
        {
                x << m_trajectories[i][it][m_abscissa];
                y << m_trajectories[i][it][m_ordinate];
        }
        else// Recreate all the iteration
        {
            for (int j = 0; j <= it; j++)
            {
                /*
                if (m_trajectories[i][j].size() != 0)
                    continue;
                    */
                x << m_trajectories[i][j][m_abscissa];
                y << m_trajectories[i][j][m_ordinate];
            }
        }
        graph(i)->addData(x, y);
    }

    // do not perform painting if not visible
    if(!isVisible())
        return;

    rescaleAxes(false);
    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);


    replot();

    // Store the previous axis to detect dimension change
    m_previousOrdinate = m_ordinate;
    m_previousAbscissa = m_abscissa;
}

void FitnessLandscape::setAbscissa(int abscissa)
{
    m_abscissa = abscissa - 1;
    // Set axis label
    xAxis->setLabel("Dimension " + QString::number(abscissa));
    clearGraphs();
    performStepComputation();
}

void FitnessLandscape::setOrdinate(int ordinate)
{
    m_ordinate = ordinate - 1 ;
    // Set axis label
    yAxis->setLabel("Dimension " + QString::number(ordinate));
    clearGraphs();
    performStepComputation();
}

void FitnessLandscape::reset()
{
    m_trajectories.clear();
    clearGraphs();
    rescaleAxes(true);
}

void FitnessLandscape::setMin(double value)
{
    m_valueRange[0] = value;
    recomputeScale();
}

void FitnessLandscape::setMax(double value)
{
    m_valueRange[1] = value;
    recomputeScale();
}

void FitnessLandscape::recomputeScale()
{
    double increment = (m_valueRange[1] - m_valueRange[0])/GRAPH_NUM;
    m_scale.clear();
    for (int i = 0; i <= GRAPH_NUM; i++)
        m_scale << m_valueRange[0]+(double)i*increment;
}
