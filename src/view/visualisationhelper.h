

#ifndef VISUALISATIONHELPER_H
#define VISUALISATIONHELPER_H

/**
 * @file visualisationhelper.h
 * @short Definition of class VisualisationHelper
 */

#include <QColor>


/**
 * @brief Visualization helper class
 *
 * This class contains functions that are used for
 * writing visualizations.
 * It provides different methods to get color scales. Not
 * all are currently used.
 * \author Lucien XU
 * \author Guillaume Jornod
 */
class VisualisationHelper
{
public:
    /**
     * @brief Rainbow coding for particle
     *
     * This function return a color to be used in an
     * index-based coloring with count elements.
     * @param index index of the particle.
     * @param count particle count.
     * @return color corresponding to that particle.
     * \author Lucien XU
     */
    static QColor rainbowCoding(int index, int count);
    /**
     * @brief Rainbow coding for particle
     *
     * This function return a color to be used in a
     * performance-based coloring with performances
     * between min and max.
     * @param index index of the particle.
     * @param count particle count.
     * @param performance array of the performances.
     * @param min minimum value for color scale.
     * @param max minimum value for color scale.
     * @return color
     * \author Guillaume Jornod
     */
    static QColor rainbowCoding(int index, int count, const double *performance, const double min, const double max);
    /**
     * @brief Rainbow coding for particle
     *
     * This function return a color to be used in a
     * performance-based coloring with performances
     * between min and max.
     * @param index index of the particle.
     * @param count particle count.
     * @param performance array of the performances.
     * @param min minimum value for color scale.
     * @param max minimum value for color scale.
     * @return color
     * \author Guillaume Jornod
     */
    static QColor rainbowCoding(int index, int count, const QVector<double> performance, const double min, const double max);
    /**
     * @brief Function returning color from a gradient
     *
     * Implementation of the trigonometry based
     * technique to compute color gradient
     * @param index
     * @param size
     * @return color
     * \author Guillaume Jornod
     */
    static QColor gradient(const int index, const int size);
};

#endif // VISUALISATIONHELPER_H
