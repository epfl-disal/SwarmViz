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

#ifndef SCREENSHOTS_H
#define SCREENSHOTS_H
#include <QtCore/QDebug>
#include <QWidget>
#include "mainwindow.h"

#define PDF 0
#define BMP 1
#define PNG 2
#define JPG 3
/**
 * @file screenshots.h
 * @short Implementation of the class Screenshots
 */
class AbstractVisualisation;
class MainWindow;
class SwarmManager;
class Swarm;
/**
 * @brief A file manager for the visualizations and the swarm states
 *
 * The class ScreenShots provides an interface between
 * the other classes and the OS file system. In addition to the selection
 * of input files and output directory, this class has tree purposes:
 * parsing data from input state files, writing the state of the algorithm and
 * save the current state of the visualizations.
 *
 * The reading and writing of files are ordered by the user, which can select
 * the input files used to feed the particles states or chose to save the state
 * of the running simulation.
 * The writing of the states allows the user to rerun the exact same simulation in a further analysis.
 *
 * Regarding the snapshots of the plots, ScreenShots uses the save
 * functions provided by QCustomPlot. The available formats are PDF, JPG,
 * PNG and BMP, which come with specific properties: size, quality and scale.
 *
 * The name of the class originates from the original purpose of this class, that is to output screen shots of the visualizations.
 *  \author Guillaume Jornod
 */
class Screenshots: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Screenshots' constructor
     * @param parent Parent widget
     */
    explicit Screenshots(QObject *parent);
    /**
     * @brief Sets the output directory
     *
     * Sets the output directory to
     * path to the directory where the snapshots and state files should be saved.
     * The subdirectory contains the current timestamp in its name.
     * @param subdir Specified output directory
     *  \author Guillaume Jornod
     */
    void getSubdir(char subdir[]) const;
    /**
     * @brief Saves visualization
     *
     * This function triggers the saving of the specified plot in the subdirectory.
     * @param subdir Directory where the snapshot will be saved.
     * @param visualisation Visualization to save.
     *  \author Guillaume Jornod
     */
    void saveScreenshots(const char subdir[20], AbstractVisualisation *visualisation) const;
    /**
     * @brief Writes parameter file
     *
     * This method creates the pso_params file containing the number of iterations
     * that will be performed and the swarm size.
     * @param maxIter Number of iterations
     * @param size Swarm size
     */
    void writePsoParam(const int maxIter, const int size) const;
    /**
     * @brief Sets the parameters in the input files in the swarmmanager.
     * @param swarmmanager SwarmManager instance.
     * \author Guillaume Jornod
     */
    void getReadParam(SwarmManager * swarmmanager) const;
    /**
     * @brief Checks if the conditions to permit the reading are met.
     * @return True if the conditions are met, false otherwise.
     * \author Guillaume Jornod
     */
    bool isReadingReady() const;
    /**
     * @brief Reading files?
     * @return True if files are read, false otherwise.
     * \author Guillaume Jornod
     */
    bool isRead() const;
    /**
     * @brief Triggers the writing of the algorithm state
     * @param best Best particle positions
     * @param  swarm Swarm instance
     * @param iteration Current iteration.
     */
    void writeState(const QVector<double> best, Swarm * swarm, int iteration) const;
    /**
     * @brief Reads the state from input file.
     * @param swarm Swarm instance that will be fed with.
     * @param iteration Iteration to read.
     * @param firstIt triggers the counting of dimension if set to true.
     * @return Best position.
     * \author Guillaume Jornod
     */
    const QVector<double> readState(Swarm *swarm, int iteration, const bool firstIt = false) const;
    /**
     * @brief Two elements array that contains the global range of the positions.
     */
    double m_globalRange[2];
    /**
     * @brief Two elements array that contains the global range of performances.
     */
    double m_globalRangeFitness[2];
public slots:
    /**
     * @brief Gets the value entered in the GUI.
     * @param outputdir Directory where the working directory will be created.
     * \author Guillaume Jornod
     */
    void setOutputDir(QString outputdir);
    /**
     * @brief Gets the value entered in the GUI.
     * @param inputdir Directory where the state files will be read.
     * \author Guillaume Jornod
     */
    void setInputDir(QString inputdir);
    /**
     * @brief Gets the parameter file entered in the GUI.
     * @param inparamname is the name of the input parameters file.
     * \author Guillaume Jornod
     */
    void setInParamName(QString inparamname);
    /**
     * @brief Changes the format
     *
     * Fired from the GUI when the user changes the output format.
     * @param format 0 for PDF, 1 for BMP, 2 for PNG and 3 for JPG.
     * \author Guillaume Jornod
     */
    void formatChange(int format);
    /**
     * @brief Sets the quality
     *
     * Fired from the GUI. It sets the quality of the snapshots of the plots.
     * @param quality is an integer between 0 and 100. -1 corresponds to undefined and will be interpreted as 100.
     * \author Guillaume Jornod
     */
    void setQuality(int quality);
    /**
     * @brief Sets the size
     *
     * ired from the GUI. It sets the size of the snapshots of the plots.
     * @param size is the desired size for the snapshots.
     * \author Guillaume Jornod
     */
    void setSize(int size);
    /**
     * @brief  Sets the scale.
     *
     * Fired from the GUI. It sets the scale of the snapshots of the plots.
     * @param scale is the desired scale for the snapshots.
     * \author Guillaume Jornod
     */
    void setScale(double scale);
    /**
     * @brief Switch the mode of the class.
     * @param isRead True when the swarm is fed by input files and false otherwise.
     * \author Guillaume Jornod
     */
    void setReadOrSimulate(bool isRead);
private:
    /**
     * @brief Quality of the snapshots of the plots.
     */
    int m_quality;
    /**
     * @brief Size of the snapshots of the plots.
     */
    int m_size;
    /**
     * @brief Scale of the snapshots of the plots.
     */
    double m_scale;
    /**
     * @brief Sormat in which the snapshots will be stored.
     */
    int m_format;
    /**
     * @brief Instance of MainWindow.
     */
    MainWindow * m_ui;
    /**
     * @brief Contains the path to the output directory.
     */
    QString m_outputdir;
    /**
     * @brief Contains the path to the input directory
     */
    QString m_inputdir;
    /**
     * @brief True when the states have to be written and false otherwise.
     */
    bool m_writeStates;
    /**
     * @brief Parameter file name.
     */
    QString m_inParamName;
    /**
     * @brief Dimensionality read from the files.
     */
    int m_dimension;
    /**
     * @brief Size of the swarm read from the parameters file.
     */
    int m_swarmsize;
    /**
     * @brief Number of iteration read from the files.
     */
    int m_maxiteration;
    /**
     * @brief Reads the parameters file and fills m_swarmsize and m_maxiteration.
     * \author Guillaume Jornod
     */
    void readPsoParam();
    /**
     * @brief Reads a state file and fills m_dimension
     * \author Guillaume Jornod
     */
    void readDimension();
    /**
     * @brief True when the state files are read.
     */
    bool m_isRead;
    /**
     * @brief Reads all the files to get the minimum and maximum positions and performances.
     * \author Guillaume Jornod
     */
    void setGlobalMinMax();
signals:
    /**
     * @brief Signal that resets the swarm manager to take the new parameters into account.
     * \author Guillaume Jornod
     */
    void resetSwarmManager();
    /**
     * @brief Emitted when a dimension is read from the files.
     * \author Guillaume Jornod
     */
    void readDimChanged(int) const;
    /**
     * @brief Emitted when a swarm size is extracted from the files.
     * \author Guillaume Jornod
     */
    void readPartNum(int, int);
    /**
     * @brief Emitted when a parameters file is found in the input directory.
     * \author Guillaume Jornod
     */
    void inputParamFound(QString);
};

#endif // SCREENSHOTS_H
