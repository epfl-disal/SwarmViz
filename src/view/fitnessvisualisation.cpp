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
 * @file fitnessvisualisation.cpp
 * @short Implementation of class FitnessVisualisation
 */

#include "fitnessvisualisation.h"
#include <QtGui/QPainter>
#include <QtCore/QDebug>
#include "visualisationhelper.h"
#include "../pso/swarm.h"
#include "qcustomplot/qcustomplot.h"

FitnessVisualisation::FitnessVisualisation(QWidget *parent):
    AbstractVisualisation(parent)
{
    setDisplayStyle(StyleBestAndAverage);

    m_title = new QCPPlotTitle(this, "Fitness (All)");
    plotLayout()->addElement(0, 0, m_title);
    xAxis->setLabel("Iteration");
    yAxis->setLabel("Fitness");
    m_titlePlot = "fitness";
}

void FitnessVisualisation::setDisplayStyle(bool displayStyle)
{
    if (displayStyle) {
        m_displayStyle = FitnessVisualisation::StyleAll;
    } else {
        m_displayStyle = FitnessVisualisation::StyleBestAndAverage;
    }
    replot();
}

void FitnessVisualisation::performStepComputation()
{
    FitnessMap fitnessMap = fitnessList().last();
    if (fitnessMap.isEmpty()) {
        return;
    }

    // do not perform painting if not visible
    if(!isVisible())
        return;

   // Paint the graph
    switch (m_displayStyle) {
    case StyleBestAndAverage:
        m_title->setText("Fitness (Best and average)");
        paintBestAndAverage(fitnessMap);
        break;
    case StyleAll:
        m_title->setText("Fitness (All)");
        paintAll(fitnessMap);
        break;
    }
    rescaleAxes(true);
}
void FitnessVisualisation::paintBestAndAverage(const FitnessMap &fitnessMap)
{
    clearGraphs();
    QList<int> keys = fitnessMap.keys();
    QVector<double> x(0), y(0);

    // Paint the best
    for (int i = 1; i < keys.size(); i++) {
        int key = keys.at(i);
        // Find the best fitness
        double bestFitness = fitnessMap.value(key).at(0);

        for (int j = 1; j < swarm()->size(); j++) {
            bestFitness = qMin(fitnessMap.value(key).at(j), bestFitness);
        }
        x.append(key-1);
        y.append(bestFitness);
    }
    addGraph();
    graph(0)->setData(x, y);
    graph(0)->setPen(QPen(Qt::darkRed));

    y.clear();

    double averageFitness = 0;
    for (int i = 1; i < keys.size(); i++) {
        int key = keys.at(i);
        // Compute the average fitness
        averageFitness = 0;

        for (int j = 0; j < swarm()->size(); j++) {
            averageFitness += fitnessMap.value(key).at(j);
        }
        averageFitness /= swarm()->size();
        y.append(averageFitness);
    }

    addGraph();
    graph(1)->setData(x, y);
    graph(1)->setPen(QPen(Qt::darkBlue));

    setInteraction(QCP::iRangeDrag, true);
    setInteraction(QCP::iRangeZoom, true);
    replot();
}

void FitnessVisualisation::paintAll(const FitnessMap &fitnessMap)
{
    clearGraphs();
    QList<int> keys = fitnessMap.keys();
    QVector<double> x(0), y(0);


    // Iterate over swarm
    for (int j = 0; j < swarm()->size(); j++) {

        addGraph();

        x.clear();
        y.clear();
        // Draw the fitness
        for (int i = 0; i < keys.size(); i++) {
            int key = keys.at(i);
            // Get the coordinate of the fitness
            x.append(key-1);
            y.append(fitnessMap.value(key).at(j));
        }

        graph(j)->setData(x, y);
        graph(j)->setPen(QPen(VisualisationHelper::rainbowCoding(j, swarm()->size())));

        setInteraction(QCP::iRangeDrag, true);
        setInteraction(QCP::iRangeZoom, true);
        replot();

    }
  }
