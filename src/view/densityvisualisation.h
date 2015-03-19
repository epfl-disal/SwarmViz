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



#ifndef DENSITYVISUALISATION_H
#define DENSITYVISUALISATION_H

/**
 * @file densityvisualisation.h
 * @short Definition of class DensityVisualisation
 */


#include "abstractvisualisation.h"
#include "qcustomplot/qcustomplot.h"

/**
 * @brief Visualization using the density graph
 *
 * The density plot is a two dimensions graphical tool
 * used originally to visualize data contained in a matrix.
 * It is widely used in the field of System Biology to visualize
 * DNA microarray data. This plot is also known under
 * the previously trademarked name of Heatmap.
 *
 * Here, the density plot is used to visualize all the dimensions
 * of the PSO problem at a specific iteration.
 * A rectangle represents the position of a particle
 * in a dimension. For instance, the rectangle at (1, 10)
 * denotes the position of the first particle in the tenth
 * dimension. In addition to give an overview of the values
 * of the particle, this plot aims to detect the convergence
 *of the algorithm, depicted by vertical lines.
 *
 * The scale for the coloring is here again an issue.
 *The rendering is computed as following: the color black
 * denotes the minimum value, the white the higher, and the
 * rest of the values are denoted by a grey scale between
 * these two values. The issue is on the choice of the minimum
 * and maximum values. Indeed, since the purpose of this plot
 * is to detect the convergence of the algorithm, with an instant
 * value color scaling and a parameter dramatically higher than
 * the other, the convergence in these other dimensions is difficult
 * to detect. Similarly, with an initial value color scaling and
 * a bad initial bounding hypercube setting, the evolution of
 * the algorithm is impossible to be visualized if the particles
 * flow out of the initial hypercube.
 *
 * \author Guillaume Jornod
 * \author Lucien XU
 */
class DensityVisualisation : public AbstractVisualisation
{
    Q_OBJECT
public:
    /**
     * @brief The SCALING_TYPE enum
     *
     * Defines the type of value range used
     */
    enum SCALING_TYPE {
     /**
      * @short Initial range. Minimum and maximum at the first iteration
      */
       INITIAL,
     /**
      * @short Global range, only available in reading mode. All input files will be read to find the global minimum and maximum values.
      */
      GLOBAL,
      /**
       * @short Instant range. Minimum and maximum of the current iteration
       */
      INSTANT};

    /**
     * @brief Constructor
     *
     * Sets the graph title and axis names. The constructor also sets the name
     * that will be used when the save method is triggered.
     * @param parent parent widget.
     * \author Guillaume Jornod
     */
    explicit DensityVisualisation(QWidget *parent = 0);
    /**
     * @brief Performs the computations for the step
     *
     * This method is called at each step of the algorithm. First, a parent for all
     * rectangles is created and set to invisible in order to create or modify all the
     * rectangle without refreshing.
     *
     * Then, if there is any inconsistency in the size of the objects, all rectangles are
     * re-created. An offset of 0.5 is added in order to obtain the tick inside the rectangle.
     *
     * The color is then changed depending on the value of the position, using black for the minimum,
     * white for the maximum. Grey correspond to the mean of the two values.
     *
     *  Finally, the parent rectangle is set to visible and all rectangles are displayed.
     * Depending on the number of dimension, an attempt is done to avoid the overlapping of the marks.
     *
     * \author Guillaume Jornod
     * \author Lucien XU (original implementation)
     */
    void performStepComputation();
    /**
     * @brief Resets the visualization
     *
     * All items, graphs are cleared. Additionally, the m_heatMap array is also cleared.
     * \author Guillaume Jornod
     */
    void reset();
    /**
     * @brief Changes the scaling type.
     *
     * This methods is triggered by the user through the GUI. The integer
     * type corresponds to one of the possible options for the ranges.
     * @param type Corresponds to the enum INITIAL, GLOBAL and INSTANT
     *
     * \author Guillaume Jornod
     */
    void setScalingType(int type);

    /**
     * @brief Gets the minimum and maximum for the color scaling
     *
     * The returned values depend on the scaling type set by setScalingType.
     * @param min Pointer to the minimum value corresponding to black
     * @param max Pointer to the maximum value corresponding to white
     */
    void getMinMax(double *min, double *max);
    /**
     * @brief Pen for the parent rectangle
     *
     * Stores the color and the width of the parent rectangle
     */
    QPen *m_pen;
private:
    /**
     * @brief Title of the plot
     */
    QCPPlotTitle* m_title;
    /**
     * @brief Map of the rectangle
     *
     * The rectangle objects are stored in this map in order to avoid useless computations,
     * that is, the creation of the rectangles at each iteration. With this storage, the update of the
     * color is sufficient if the sizes are consistent.
     *
     * \author Guillaume Jornod
     */
    QList<QList<QCPItemRect*> > m_heatMap;
    /**
     * @brief Range type of the coloring
     *
     */
    int m_type;

};

#endif // DENSITYVISUALISATION_H
