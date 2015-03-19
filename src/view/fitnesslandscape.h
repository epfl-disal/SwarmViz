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
#ifndef FITNESSLANDSCAPE_H
#define FITNESSLANDSCAPE_H

/**
 * @file fitnesslandscape.h
 * @short Definition of class FitnessLandscape
 */
#include "abstractvisualisation.h"
#include "qcustomplot/qcustomplot.h"

/**
 * @brief Visualization in 2-D of the fitness of each position evaluation
 *
 * This class provides the methods to visualize
 * a two dimensional projection of the particle position
 * with a color rendering depending on the performance.
 *
 * The notion fitness landscape denotes the visualization of the
 * performance values with the tested candidate solutions in a
 * two dimensions space. This lets visualize a projection of the
 * landscape with the drawback that a position in two dimensions
 * can have different value for the values in the other
 * dimensions is not the same.
 *
 * \author Guillaume Jornod
 */
class FitnessLandscape : public AbstractVisualisation
{
    Q_OBJECT
public:
    /**
     * @brief FitnessLandscape's constructor
     * @param parent Parent widget
     *
     * The constructor sets the default values for abscissa and ordinate. Then, the graph title,
     * the axis names and the default value range are set.
     */
    explicit FitnessLandscape(QWidget *parent = 0);

private:
    /**
     * @brief Dimension on abscissa
     */
    int m_abscissa;
    /**
     * @brief Dimension on ordinate
     */
    int m_ordinate;
    /**
     * @brief Trajectories
     *
     * This maps the positions in the suitable graph (depending of the performance
     * of the particle), for each iteration and each dimension. The map is organized as
     *  [graph][iteration][dim][value]
     * \author Guillaume Jornod
     */
    QList<QList<QList<QVector<double> > > >m_trajectories;
    /**
     * @brief Previous dimension drawn on ordinate
     *
     * This value is stored in order to detect a change in the
     * dimensions plotted. This change triggers the replotting of the graph.
     */
    int m_previousOrdinate;
    /**
     * @brief Previous dimension drawn on abscissa
     *
     * This value is stored in order to detect a change in the
     * dimensions plotted. This change triggers the replotting of the graph.
     */
    int m_previousAbscissa;
    /**
     * @brief Performance intervals
     *
     * This vector stores the boundaries of the performance intervals in which
     * the particles will be classified.
     *
     * \author Guillaume Jornod
     */
    QVector<double> m_scale;
    /**
     * @brief  Recomputes the performance intervals.
     *
     * This method should be called when the global scale changes or when
     * a new simulation is set. It simply divides the global range of
     * performances into GRAPH_NUM sub-intervals. GRAPH_NUM is a constant currently set
     * to 100.
     *
     * \author Guillaume Jornod
     */
    void recomputeScale();
public slots:
    /**
     * @brief  Performs the computations of the step
     *
     * This method checks the consistency of the m_trajectories member and then ensures that
     * all the graphs which will contain the points are created.
     *
     * Then, the trajectory are classified in the suitable performance sub-intervals and
     * stored in te m_trajectories multi-dimensional matrix. The points are added in the suitable
     * graphs.
     *
     * If the plot is visible, it is refreshed.
     *
     * \author Guillaume Jornod
     */
    void performStepComputation();
    /**
     * @brief Sets dimension on abscissa
     *
     * \author Guillaume Jornod
     */
    void setAbscissa(int);
    /**
     * @brief Set dimension on ordinate
     * \author Guillaume Jornod
     */
    void setOrdinate(int);
    /**
     * @brief Resets the visualization
     *
     * m_trajectories and the graphs are cleared.
     *
     * \author Guillaume Jornod
     */
    void reset();
    /**
     * @brief Sets the minimum of the value range
     *
     * This function uses the value set in the GUI as custom range
     * @param value Minimum of the performance interval
     * \author Guillaume Jornod
     */
    void setMin(double value);
    /**
     * @brief Sets the maximum of the value range
     *
     * This function uses the value set in the GUI as custom range
     * @param value Maximum of the performance interval
     * \author Guillaume Jornod
     */
    void setMax(double value);

};

#endif // FITNESSLANDSCAPE_H
