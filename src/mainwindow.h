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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file mainwindow.h
 * @short Definition of class MainWindow
 */

#include <QMainWindow>
#include <QAbstractButton>
#include "view/abstractvisualisation.h"

namespace Ui {
class MainWindow;
}

class SwarmManager;
class AbstractVisualisation;
class Screenshots;
/**
 * @brief The main window.
 *
 * The MainWindow is an heir class of QMainWindow. The constructor of this class initializes the GUI defined in the form file, creates instances for all visualization widgets and then connect signals and slots to create the interactions between the swarm manager, the GUI and the visualizations.
 *
 * Most of the members of this class are used to avoid redundancy in the operations. Some methods are also used to pre-process the actions performed with the GUI, ensuring range consistency for minimum and maximum definition for example.
 *
 * To summarize, MainWindow is the layer between the user on the one hand, and the simulation and visualizations on the other hand.
 * \author Lucien XU
 * \author Guillaume Jornod
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * The constructor of the MainWindow class instantiates the visualizations widgets
     * it then connects these instances to the buttons of the GUI.
     *
     * \author Lucien XU
     * \author Guillaume Jornod
     * @param parent Parent widget.
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~MainWindow();
private:
    /**
     * @brief Common slots connexion
     *
     * This function establishes the common connexions between the GUI and the visualizations. These connexions are the reset and step actions, as well as the save process.
     *
     * The SwarmManager and the Screenshots instances are also set.
     * @param visualisation AbstractVisualisation heir to be connected.
     *
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void connectVisualisation(AbstractVisualisation *visualisation);
    /**
     * @internal
     * @brief UI
     */
    Ui::MainWindow *ui;
    /**
     * @internal
     * @brief SwarmManager instance
     *
     * A pointer to the SwarmManager instance is stored as a member to be used as an interface between this class and the visualizations.
     */
    SwarmManager *m_swarmManager;
    /**
     * @brief Screenshots instance
     * A pointer to the Screenshots instance is stored as a member to be used as an interface between the visualizations and the OS file system.
     */
    Screenshots *m_screenshot;
    /**
     * @brief Gets the parameter of the GUI and load them in the SwarmManager
     *
     * Resets the swarmManager parameters with the ui values.
     * This method ensure the consistence of the parameters
     * of the swarm. It is especially useful when the program
     * is launched and the default values have been changed
     * either in the classes or in the GUI definition.
     * It is also called at the transition between reading
     * and simulation modes.
     * \author Guillaume Jornod
     */
    void reloadSimulationParameterFromUi();
private slots:
    /**
     * @brief Slot used to respond to reset
     *
     * This method cleans the information displayed in the GUI concerning the steps, runs and fitness.
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void slotReset();
    /**
     * @brief Slot to respond to step change
     *
     * This method feeds the data to display information in the GUI concerning the steps, runs and fitness.
     * @param run Current run
     * @param step Current step
     * @param fitness_value Best fitness of the current iteration
     *
     * \author Lucien XU
     * \author Guillaume Jornod
     */
    void slotCurrentIterationChanged(int run, int step, double fitness_value);
    /**
     * @brief Sets simulation speed
     *
     * Sets the delay between the iteration of the algorithm. The delay is computed as: \f[ v = (v_\text{max}-\text{speed})\cdot 20\f]
     * @param speed Speed index.
     *
     * \author Lucien XU
     * \author Guillaume Jornod (full reimplementation)
     */
    void setSimulationSpeed(int speed);
    /**
     * @brief Uses the number of particles as maximum for the number of neighbors
     * Sets the neighborhood maximum from the swarmsize in order to ensure the consistency.
     * @param particulesNumber
     *
     * \author Guillaume Jornod
     */
    void setMaximumNeighboursNumber(int particulesNumber);
    /**
     * @brief Manages the files browsing widgets
     *
     * Adds files browsing widgets. The behavior of this function depends on the sender of the signal. It will display a file browsing window with the choice of either directory or files.
     *
     * \author Guillaume Jornod
     */
    void filesBrowsing();
    /**
     * @brief Resets the input fields
     *
     * This is a workaround to avoid crash of the program when a new input directory is set with a remaining parameter file.
     * \author Guillaume Jornod
     */
    void resetInput(QAbstractButton *button);
    /**
     * @brief OK button callback
     *
     * Checks the presence of input state files and parameter file. If everything is ready for the reading, the program passes in read mode and the tab is switched to simulation control tab.
     * @param button Sender of the signal
     * \author Guillaume Jornod
     */
    void launchReadSimulation(QAbstractButton * button);
    /**
     * @brief Displays the dimensionality of the loaded learning
     *
     * Once the dimension is got from the reading of one input state file, the dimension is displayed over the confirmation button.
     * @param dimension Number of dimensions
     * \author Guillaume Jornod
     *
     */
    void dispInputDim(int dimension);
    /**
     * @brief Display the swarm size and the number of iterations of the loaded learning
     *
     * Once the parameter file is read, the particle number and the iteration number are displayed over the confirmation button.
     * @param particles Number of particles
     * @param iterations Number of iterations
     * \author Guillaume Jornod
     */
    void dispPartnumAndMaxiter(int particles, int iterations);
    /**
     * @brief Enables and disables options at the mode changing
     *
     * Triggers all operations in GUI to ensure consistency of the options regarding the simulation and the reading mode. The suitable options are enabled or disabled.
     * @param isRead Reading or simulation mode
     * \author Guillaume Jornod
     */
    void toggleSimulationMode(bool isRead);
    /**
     * @brief Changes the iteration range
     *
     * This method simply updates the maximum of the iteration range when the iteration minimum or maximum changes.
     * @param min First iteration
     * @param max Last iteration
     * \author Guillaume Jornod
     */
    void setNewRange(int min, int max);
    /**
     * @brief New number of iterations
     *
     * This functions triggers the update of the real maximum iteration (to be differentiated with the effective maximum, which is set in the iteration range).
     * @param max Last iteration
     * \author Guillaume Jornod
     */
    void newRealMax(int max);
    /**
     * @brief Sets the TrajectoryVisualisation color mode
     *
     * Changes the color rendering of the TrajectoryVisualisation instance. True for fitness-based, false for index-based.
     * @param enable Fitness-based / Index-based coloring
     *
     * \author Guillaume Jornod
     */
    void enableFitnessTrajectoryColoring(bool enable);
    /**
     * @brief Sets the minimum of the maxspinbox for the fitness coloring range
     *
     * Ensures consistency in the spinboxes. The minimum should not be greater than the maximum.
     * @param newMin New minimum to be used
     * \author Guillaume Jornod
     */
    void setMinFitnessRange(int newMin);
    /**
     * @brief Sets the maximum of the minspinbox for the fitness coloring range
     *
     * Ensures consistency in the spinboxes. The minimum should not be greater than the maximum.
     * @param newMax New maximum to be used
     * \author Guillaume Jornod
     */
    void setMaxFitnessRange(int newMax);
    /**
     * @brief Sets the minimum of the maxspinbox for the fitness coloring range in fitness landscape
     * @param newMin New minimum
     * \author Guillaume Jornod
     */
    void setMinFitnessColor(double newMin);
    /**
     * @brief Sets the maximum of the minspinbox for the fitness coloring range in fitness landscape
     *
     * Ensures consistency in the spinboxes. The minimum should not be greater than the maximum.
     * @param newMax New maximum
     * \author Guillaume Jornod
     */
    void setMaxFitnessColor(double newMax);
    /**
     * @brief  Changes the maximum dimensions to display
     *
     * Ensure the consistency between the dimensionality of the problem and displayable dimensions. The maximum of the dimensions spinboxes are set to the number of dimensions of the problem.
     * @param value New number of dimensions
     *
     * \author Guillaume Jornod
     */
    void setMaxDimensionTrajectory(int value);
signals:
    /**
     * @brief Signal for empty file choice
     *
     * Resets the input fields.
     * @param path Null string
     * \author Guillaume Jornod
     */
    void fileToTextEdit(QString path);
};

#endif // MAINWINDOW_H
