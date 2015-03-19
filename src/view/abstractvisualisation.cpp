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
 * @file abstractvisualisation.cpp
 * @short Implementation of class AbstractVisualisation
 */

#include "abstractvisualisation.h"
#include "qcustomplot/qcustomplot.h"
#include <QtGui/QPainter>
#include <sys/stat.h>
#include "ui_mainwindow.h"
#include <QAbstractButton>


AbstractVisualisation::AbstractVisualisation(QWidget *parent) :
    QCustomPlot(parent)
{
    m_swarmManager = 0;
    setMinimumSize(400, 400);
    setMaximumSize(400, 400);
    setMinimumWidth(width());
    setMinimumHeight(height());
    plotLayout()->insertRow(0); // inserts an empty row above the default axis rect for the title
}

void AbstractVisualisation::setSwarmManager(const SwarmManager *swarmManager)
{
    m_swarmManager = swarmManager;
    reset();
}

void AbstractVisualisation::setScreenshot(const Screenshots *screenshot)
{
    m_screenshot = screenshot;
}

void AbstractVisualisation::performStepComputation()
{
    update();
}

void AbstractVisualisation::reset()
{
    clearGraphs();
    clearItems();
    update();
}

int AbstractVisualisation::maxIterations() const
{
    return m_swarmManager->maxIterations();
}

const Swarm * AbstractVisualisation::swarm() const
{
    return m_swarmManager->swarm();
}

QList<FitnessMap> AbstractVisualisation::fitnessList() const
{
    return m_swarmManager->fitnessList();
}

void AbstractVisualisation::setAbscissa(int abs)
{
    Q_UNUSED(abs);
    update();
}

void AbstractVisualisation::setOrdinate(int ord)
{
    Q_UNUSED(ord);
    update();
}

void AbstractVisualisation::setPreviousPosition(int num)
{
    Q_UNUSED(num);
    update();
}

void AbstractVisualisation::save()
{
    qDebug() << isVisible();
    if(!isVisible())
        return;
    char subdir[20];
    m_screenshot->getSubdir(subdir);
    m_screenshot->saveScreenshots(subdir, this);
}

void AbstractVisualisation::setColoration(bool col)
{
    Q_UNUSED(col);
}

void AbstractVisualisation::setScalingType(int type)
{
    Q_UNUSED(type);
    return;
}

void AbstractVisualisation::setMax(int value)
{
    Q_UNUSED(value);
    return;
}


void AbstractVisualisation::setMin(int value)
{
    Q_UNUSED(value);
    return;
}

void AbstractVisualisation::setMax(double value)
{
    Q_UNUSED(value);
    return;
}


void AbstractVisualisation::setMin(double value)
{
    Q_UNUSED(value);
    return;
}



void AbstractVisualisation::toggleVisibility(bool disp)
{
    disp?show():hide();
}

void AbstractVisualisation::setDisplayStyle(bool displayStyle){
    Q_UNUSED(displayStyle);
}
