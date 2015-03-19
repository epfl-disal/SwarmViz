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


#ifndef TRAJECTORYVISUALISATION_H
#define TRAJECTORYVISUALISATION_H

/**
 * @file trajectoryvisualisation.h
 * @short Definition of class TrajectoryVisualisation
 */

#include "abstractvisualisation.h"
#include "qcustomplot/qcustomplot.h"

/**
 * @brief Visualisation using a 2D projection for the trajectory.
 *
 * The trajectories visualization is a projection of the particles
 * positions from the search space to a plan defined
 * by two dimensions set by the user. Plotting the position of
 * successive iterations lets obtain the projection of the
 * trajectories in two dimensions.
 *
 * Two coloring schemes are proposed, the first one is index-based
 * whereas the second one is based on the performance of the
 * particles at the current iteration.
 *
 * \author Guillaume Jornod
 * \author Lucien XU
 */
class TrajectoryVisualisation: public AbstractVisualisation
{
public:
    /**
     * @brief The TRAJEC_TYPE enum
     *
     * Color rendering for the particle trajectory.
     */
    enum TRAJEC_TYPE {
        /**
          @short Index-based.
          */
        TRAJECTORY,
        /**
          @short Performance-based
          */
        FITNESS_LANDSCAPE};
    /**
     * @brief The SCALING_TYPE enum
     *
     * Defines the type of performance range used
     */
    enum SCALING_TYPE {
     /**
      * @short Initial range. Minimum and maximum performance at the first iteration
      */
        INITIAL,
     /**
      * @short Global range, only available in reading mode. All input files will
      * be read to find the global minimum and maximum performances.
      */
        GLOBAL,
      /**
       * @short Instant range. Minimum and maximum performances of the current iteration
       */
        INSTANT,
        /**
          @short Custom range.
          */
        RANGE};
    /**
     * @brief Default constructor
     *
     * This method sets the default dimension for abscissa and ordinate, 0 and 1 (displayed 1 and 2),
     * as well as the title of the plot, the default coloring mode (index-based), the axis names and the output filename.
     *
     * @param parent Parent widget.
     * \author Guillaume Jornod
     */
    explicit TrajectoryVisualisation(QWidget *parent = 0);
public slots:
    /**
     * @brief Resets the plot.
     *
     * The graphs and m_trajectories are cleared.
     * \author Guillaume Jornod
     */
    void reset();
    /**
     * @brief Performs the computations for the step
     *
     * First, it ensures that the size of m_trajectories and the swarm size are consistent. Then, m_trajectories is
     * filled with the positions of the particles. A specific number of positions are stored in this
     * array, this number is by default 10 and can be set by the user.
     *
     * Each particle is denoted by a graph, which color depends on the coloring mode, index-based or performance-based.
     *
     * \author Guillaume Jornod
     * \author Lucien XU
     */
    void performStepComputation();
    /**
     * @brief Sets dimension on abscissa
     * \author Guillaume Jornod
     */
    void setAbscissa(int);
    /**
     * @brief Sets dimension on ordinate
     * \author Guillaume Jornod
     */
    void setOrdinate(int);
    /**
     * @brief Sets the number of position to display
     * \author Guillaume Jornod
     */
    void setPreviousPosition(int);
    /**
     * @brief Toggles color rendering
     *
     * @param col Performance-based / Index-based
     * \author Guillaume Jornod
     */
    void setColoration(bool col);
    /**
     * @brief Changes scaling type for performance-based fitness.
     * @param colorationType See SCALING_TYPE.
     * \author Guillaume Jornod
     */
    void setScalingType(int colorationType);
    /**
     * @brief Sets custom maximum
     *
     * This value will be used in the performance-based coloring.
     * @param value Maximum value
     * \author Guillaume Jornod
     */
    void setMax(int value);
    /**
     * @brief Sets custom minimum
     *
     * This value will be used in the performance-based coloring.
     * @param value Minimum value
     * \author Guillaume Jornod
     */
    void setMin(int value);
    /**
     * @brief Gets fitness range
     * @param min Pointer to the maximum to be set
     * @param max Pointer to the minimum to be set
     * \author Guillaume Jornod
     */
    void getMinMaxFitness(double *min, double *max);
private:
    /**
     * @brief Trajectories
     *
     * This map is organized as following:[particle][time][dimension]
     */
    QList<QList<QList<double> > > m_trajectories;
    /**
     * @brief Dimension on abscissa
     */
    int m_abscissa;
    /**
     * @brief Dimension on ordinate
     */
    int m_ordinate;
    /**
     * @brief Number of previous positions to display
     */
    int m_previousPosition;
    /**
     * @brief Type of coloring. See TRAJEC_TYPE
     */
    int m_type;
    /**
     * @brief Scaling type. See SCALING_TYPE
     */
    int m_coloring;
};

#endif // TRAJECTORYVISUALISATION_H
