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


#ifndef ABSTRACTVISUALISATION_H
#define ABSTRACTVISUALISATION_H

/**
 * @file abstractvisualisation.h
 * @short Definition of class AbstractVisualisation
 */


#include <QWidget>
#include "swarmmanager.h"
#include "qcustomplot/qcustomplot.h"
#include "support/screenshots.h"

class Swarm;
class Screenshots;
class SwarmManager;
typedef QMap<int, QList<double> > FitnessMap;

/**
 * @brief A base class for visualiation widgets
 *
 * This abstract class is itself based on the class provided by the library QCustomPlot \cite qcustomplot.
 *
 * QCustomPlot is a plotting library allowing to draw curves, scatter plot or rectangles that are used for the different visualizations.
 * It provides features such as automatic rescaling and mouse interactions like zooming and panning.
 *
 * The classes TrajectoryVisualisation, FitnessLandscapeVisualisation, FitnessVisualisation, LinesVisualisation,
 * EuclideanVisualisation, DensityVisualisation, SammonVisualisation, BestVisualisation implement the specialized
 * methods performing the required computation to provide the plot for the Trajectories visualization, the Fitness Landscape visualization,
 * the Fitness Plot, the Parallel Coordinates Plot, the Euclidean Plot, the Density Plot, the Sammon's mapping and the Best Graph
 * respectively. The difference in naming arises from the previous project nomenclature and from a desire for consistency in the code.
 *
 * \author Lucien XU
 * \author Guillaume Jornod
 */
class AbstractVisualisation : public QCustomPlot
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     *
     * Sets an empty SwarmManager pointer, a QCustomPlot widget with default width and height as well as a row for the title.
     *
     * \author Guillaume Jornod
     * @param parent Parent widget.
     */
    explicit AbstractVisualisation(QWidget *parent = 0);
    /**
     * @brief Sets SwarmManager instance
     * @param swarmManager SwarmManager to set.
     * \author Lucien XU
     */
    void setSwarmManager(const SwarmManager *swarmManager);
    /**
     * @brief Sets Screenshots instance
     *
     * This instance of file manager will be used to save the plots.
     * @param screenshot Screenshots instance
     *
     * \author Guillaume Jornod
     */
    void setScreenshot(const Screenshots * screenshot);
    /**
     * @brief Title of the plot
     */
    QString m_titlePlot;
public slots:
    /**
     * @brief Performs computations after stepping
     *
     * \author Lucien XU
     */
    virtual void performStepComputation();
    /**
     * @brief Sets dimension on abscissa
     * @param abs Dimension displayed as abscissa
     * \author Guillaume Jornod
     */
    virtual void setAbscissa(int abs);
    /**
     * @brief Sets dimension on ordinate
     * @param ord Dimension displayed as ordinate
     * \author Guillaume Jornod
     */
    virtual void setOrdinate(int ord);
    /**
     * @brief Changes the number of position visualized
     *
     * This number is used by TrajectoryVisualisation. Each point will be displayed by its
     * positionNumber last positions. This parameter is useful to clarify the visualization of the trajectories
     * when the movement is fast.
     * @param positionNumber
     *
     * \author Guillaume Jornod
     */
    virtual void setPreviousPosition(int positionNumber);
    /**
     * @brief Reset
     * \author Lucien XU
     */
    virtual void reset();
    /**
     * @brief Saves the plot
     *
     * This method triggers the saving of the graphs with the chosen format, quality and size.
     * \author Guillaume Jornod
     */
    void save();
    /**
     * @brief Toogles the coloration mode for TrajectoryVisualisation
     * @param col Index/Fitness-based coloring
     * \author Guillaume Jornod
     */
    virtual void setColoration(bool col);
    /**
     * @brief Toogles the scaling mode.
     *
     * This virtual method typically receives data from a combo box in the GUI to change the range used
     * to scale the colors.
     * @param type Integer corresponding to the chosen type
     * \author Guillaume Jornod
     */
    virtual void setScalingType(int type);
    /**
     * @brief Sets maximum integer value for a range
     * @param value Maximum integer value
     * \author Guillaume Jornod
     */
    virtual void setMax(int value);
    /**
     * @brief Sets minimum integer value for a range
     * @param value Minimum integer value
     * \author Guillaume Jornod
     */
    virtual void setMin(double value);
    /**
     * @brief Sets maximum double value for a range
     * @param value Maximum double value
     * \author Guillaume Jornod
     */
    virtual void setMax(double value);
    /**
     * @brief Sets minimum double value for a range
     * @param value Minimum double value
     * \author Guillaume Jornod
     */
    virtual void setMin(int value);

    /**
     * @brief toggleVisibility show/hide
     * @param disp Show or Hide
     * \author Guillaume Jornod
     */
    void toggleVisibility(bool disp);
    /**
     * @brief Changes the display style of the FitnessVisualisation
     *
     * This virtual slot could be merged with the setColoration in this abstract class.
     * @param displayStyle All performances or Best and average;
     * \author Lucien XU
     */
    virtual void setDisplayStyle(bool displayStyle);
protected:
    /**
     * @brief Maximum of iterations
     * @return maximum of iterations.
     * \author Lucien XU
     */
    int maxIterations() const;
    /**
     * @brief Swarm
     *
     * This method provides access to the Swarm
     * @return swarm.
     * \author Lucien XU
     */
    const Swarm * swarm() const;
    /**
     * @brief Fitness list
     * @return list of fitness.
     * \author Lucien XU
     */
    QList<FitnessMap> fitnessList() const;
    /**
     * @brief Screenshots instance
     *
     * File management class.
     * \author Guillaume Jornod
     */
    const Screenshots * m_screenshot;
    /**
     * @brief Custom minimum and maximum for the scaling
     * \author Guillaume Jornod
     */
    double m_valueRange[2];
    /**
     * @brief SwarmManager
     * \author Lucien XU
     */
    const SwarmManager *m_swarmManager;
};

#endif // ABSTRACTVISUALISATION_H
