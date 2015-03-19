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
 * @file mainwindow.cpp
 * @short Implementation of class MainWindow
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QCoreApplication>

#include <QtCore/QDebug>
#include "view/swarmmanager.h"
#include "view/trajectoryvisualisation.h"
#include "view/densityvisualisation.h"
#include "view/linesvisualisation.h"
#include "view/fitnessvisualisation.h"
#include "view/sammonvisualisation.h"
#include "view/euclideanvisualisation.h"
#include "view/fitnesslandscape.h"
#include "view/pbestvisualisation.h"
#include "string.h"
#include <QFileDialog>
#include <typeinfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Init
    ui->setupUi(this);

    m_screenshot = new Screenshots(this);
    m_swarmManager = new SwarmManager(this);
    m_swarmManager->setScreenshot(m_screenshot);

    // Widgets initialization
    TrajectoryVisualisation *trajectoryVisualisation = new TrajectoryVisualisation(this);
    ui->gridLayout->addWidget(trajectoryVisualisation, 0, 0, Qt::AlignCenter);
    connect(ui->trajectoryVisCheckBox, SIGNAL(clicked(bool)), trajectoryVisualisation, SLOT(toggleVisibility(bool)));

    DensityVisualisation *densityVisualisation = new DensityVisualisation(this);
    ui->gridLayout->addWidget(densityVisualisation, 0, 2, Qt::AlignCenter);
    connect(ui->heatMapCheckBox, SIGNAL(clicked(bool)), densityVisualisation, SLOT(toggleVisibility(bool)));

    LinesVisualisation *linesVisualisation = new LinesVisualisation(this);
    ui->gridLayout->addWidget(linesVisualisation, 1, 1, Qt::AlignCenter);
    connect(ui->parallelCoordinateCheckBox, SIGNAL(clicked(bool)), linesVisualisation, SLOT(toggleVisibility(bool)));

    EuclideanVisualisation *euclideanVisualisation = new EuclideanVisualisation(this);
    ui->gridLayout->addWidget(euclideanVisualisation, 1, 0, Qt::AlignCenter);
    connect(ui->euclidianCheckBox, SIGNAL(clicked(bool)), euclideanVisualisation, SLOT(toggleVisibility(bool)));

    FitnessVisualisation *fitnessVisualisation = new FitnessVisualisation(this);
    ui->gridLayout->addWidget(fitnessVisualisation, 1, 2, Qt::AlignCenter);
    connect(ui->fitnessCheckBox, SIGNAL(clicked(bool)), fitnessVisualisation, SLOT(toggleVisibility(bool)));

    FitnessLandscape *fitnessLandscape = new FitnessLandscape(this);
    ui->gridLayout->addWidget(fitnessLandscape, 0, 1, Qt::AlignCenter);
    connect(ui->FitnessLandscapeCheckBox, SIGNAL(clicked(bool)), fitnessLandscape, SLOT(toggleVisibility(bool)));

    SammonVisualisation *sammonVisualisation = new SammonVisualisation(this);
    ui->gridLayout->addWidget(sammonVisualisation, 2, 0, Qt::AlignCenter);
    connect(ui->sammonCheckBox, SIGNAL(clicked(bool)), sammonVisualisation, SLOT(toggleVisibility(bool)));

    BestVisualisation *bestVisualisation = new BestVisualisation(this);
    ui->gridLayout->addWidget(bestVisualisation, 2, 1, Qt::AlignCenter);
    connect(ui->bestCheckBox, SIGNAL(clicked(bool)), bestVisualisation, SLOT(toggleVisibility(bool)));


    /*
    ArbitraryVisualisation *arbitraryvisualisation = new ArbitraryVisualisation(this);
    arbitraryvisualisation->setSwarmManager(m_swarmManager);
    ui->gridLayout->addWidget(arbitraryvisualisation, 1, 2, Qt::AlignCenter);*/

  //  ui->gridLayout->setRowStretch(3, 1);
  //  ui->gridLayout->setColumnStretch(3, 1);

    // Connections

    // Mainwindow
    connect(ui->action_Quit, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()));

    // Simulation control
    connect(ui->simulatePushButton, SIGNAL(clicked(bool)), m_swarmManager, SLOT(setRunning(bool))); // Simulate button
    connect(m_swarmManager, SIGNAL(emergencyStop()), ui->simulatePushButton, SLOT(click())); // Click simulate button when the simulation has to stop
    connect(ui->StepPushButton, SIGNAL(clicked()), m_swarmManager, SLOT(step())); // Step forward
    connect(ui->StepbPushButton, SIGNAL(clicked()), m_swarmManager, SLOT(stepb())); // Step backward
    connect(ui->resetPushButton, SIGNAL(clicked()), m_swarmManager, SLOT(reset())); // Reset
    connect(ui->speedHorizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(setSimulationSpeed(int))); // Set delay
    connect(m_swarmManager, SIGNAL(currentIterationChanged(int,int, double)), this, SLOT(slotCurrentIterationChanged(int,int, double))); // Display iteration information
    connect(ui->isReadCheckBox, SIGNAL(clicked(bool)), m_screenshot, SLOT(setReadOrSimulate(bool))); // Change simualtion/read mode
    connect(ui->isReadCheckBox, SIGNAL(clicked(bool)), this, SLOT(toggleSimulationMode(bool))); // Change simulation/read mode
    // Iteration range
    connect(ui->minIterationSpinBox, SIGNAL(valueChanged(int)), m_swarmManager, SLOT(setMinIterations(int)));
    connect(ui->maxIterationSpinBox, SIGNAL(valueChanged(int)), m_swarmManager, SLOT(setEffectiveMaxIterations(int)));
    connect(m_swarmManager, SIGNAL(newRange(int,int)), this, SLOT(setNewRange(int, int)));
    connect(m_swarmManager, SIGNAL(newRealMax(int)), this, SLOT(newRealMax(int)));


    // Swarm control
    connect(ui->fitnessFunctionComboBox, SIGNAL(currentIndexChanged(int)), m_swarmManager, SLOT(setFitnessFunctionIndex(int))); // Fitness function
    connect(ui->dimensionSpinBox, SIGNAL(valueChanged(int)), m_swarmManager, SLOT(setDimension(int))); // Dimension
    connect(ui->particlesSpinBox, SIGNAL(valueChanged(int)), m_swarmManager, SLOT(setSize(int))); // Swarmsize
    connect(ui->minimumDoubleSpinBox, SIGNAL(valueChanged(double)), m_swarmManager, SLOT(setMinimum(double))); // Minimum
    connect(ui->maximumDoubleSpinBox, SIGNAL(valueChanged(double)), m_swarmManager, SLOT(setMaximum(double))); // Maximum
    connect(ui->maximumVelocityDoubleSpinBox, SIGNAL(valueChanged(double)), m_swarmManager, SLOT(setMaximumVelocity(double))); // Vmax
    connect(ui->inertiaDoubleSpinBox, SIGNAL(valueChanged(double)), m_swarmManager, SLOT(setInertia(double))); // Intertia
    connect(ui->maxIterationsSpinBox, SIGNAL(valueChanged(int)), m_swarmManager, SLOT(setMaxIterations(int))); // Iterations
    connect(ui->numberNeighborSpinBox, SIGNAL(valueChanged(int)), m_swarmManager, SLOT(setNeighbourNumber(int))); // Neighbor number
    connect(ui->localWeightDoubleSpinBox, SIGNAL(valueChanged(double)), m_swarmManager, SLOT(setLocalBestWeight(double))); // Local weight
    connect(ui->neighbourWeightDoubleSpinBox, SIGNAL(valueChanged(double)), m_swarmManager, SLOT(setNeighbourBestWeight(double))); // Neighbor weight
    connect(ui->particlesSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setMaximumNeighboursNumber(int))); // Constistency in neighbor number
    connect(ui->noiseDoubleSpinBox, SIGNAL(valueChanged(double)), m_swarmManager, SLOT(setNoise(double))); // Noise
    connect(ui->noiseResistanceCheckBox, SIGNAL(clicked(bool)), m_swarmManager, SLOT(setNoiseResistance(bool))); // Trigger noise resistance

    connect(m_swarmManager, SIGNAL(resetRequested()), this, SLOT(slotReset()));

    // Connect visualization slot via AbritraryVisualisation
    connectVisualisation(trajectoryVisualisation);
    connectVisualisation(densityVisualisation);
    connectVisualisation(linesVisualisation);
    connectVisualisation(fitnessVisualisation);
    connectVisualisation(euclideanVisualisation);
    connectVisualisation(fitnessLandscape);
    connectVisualisation(sammonVisualisation);
    connectVisualisation(bestVisualisation);

    // Files management
    connect(ui->outputDirPushButton, SIGNAL(clicked()), this, SLOT(filesBrowsing())); // Output dir field
    connect(ui->inputParamPushButton, SIGNAL(clicked()), this, SLOT(filesBrowsing())); // Input param field
    connect(ui->inputDirPushButton, SIGNAL(clicked()), this, SLOT(filesBrowsing())); // Input param field
    connect(ui->inputDirTextEdit, SIGNAL(textChanged(QString)), m_screenshot, SLOT(setInputDir(QString))); // Change input dir in file management
    connect(ui->outputDirTextEdit, SIGNAL(textChanged(QString)), m_screenshot, SLOT(setOutputDir(QString))); // Change ouputdir in file management
    connect(ui->formatComboBox, SIGNAL(currentIndexChanged(int)), m_screenshot, SLOT(formatChange(int))); // Format for screenshots
    connect(ui->scaleDoubleSpinBox, SIGNAL(valueChanged(double)), m_screenshot, SLOT(setScale(double))); // Scale for screenshots
    connect(ui->qualitySpinBox, SIGNAL(valueChanged(int)), m_screenshot, SLOT(setQuality(int))); // Quality for screenshots
    connect(ui->sizeSpinBox, SIGNAL(valueChanged(int)), m_screenshot, SLOT(setSize(int))); // Size for screenshots
    connect(m_screenshot, SIGNAL(resetSwarmManager()), m_swarmManager, SLOT(reset())); // Connection between screenshot and swarmmanager for reseting simulation
    connect(ui->inputParamTextEdit, SIGNAL(textChanged(QString)), m_screenshot, SLOT(setInParamName(QString))); // Input param field in file managament
    connect(m_screenshot, SIGNAL(inputParamFound(QString)), ui->inputParamTextEdit, SLOT(setText(QString))); // Automatic detection of param file

    // Parameters confirmation
    connect(m_screenshot, SIGNAL(readDimChanged(int)), this, SLOT(dispInputDim(int))); // Ouput dimension for confirmation
    connect(m_screenshot, SIGNAL(readPartNum(int,int)), this, SLOT(dispPartnumAndMaxiter(int, int))); // Output particule number and iterations for confirmation

    // Button box callback
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(launchReadSimulation(QAbstractButton*))); // Switch to read simulation if ok triggered
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(resetInput(QAbstractButton*))); // Reset

    // Unclick reading PSO (in order to disable the unused density scaling mode)
    ui->isReadCheckBox->click();
    ui->isReadCheckBox->setEnabled(false);


    // Fitness color modes trajectory visualisation
    connect(ui->trajectoryCheckBox, SIGNAL(clicked(bool)), this, SLOT(enableFitnessTrajectoryColoring(bool)));
    connect(ui->fitnessRangeMinSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setMinFitnessRange(int)));
    connect(ui->fitnessRangeMaxSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setMaxFitnessRange(int)));
    connect(ui->fitnessColorComboBox, SIGNAL(currentIndexChanged(int)), trajectoryVisualisation, SLOT(setScalingType(int)));
    connect(ui->fitnessRangeMaxSpinBox, SIGNAL(valueChanged(int)), trajectoryVisualisation, SLOT(setMax(int)));
    connect(ui->fitnessRangeMinSpinBox, SIGNAL(valueChanged(int)), trajectoryVisualisation, SLOT(setMin(int)));
    connect(ui->trajectoryCheckBox, SIGNAL(clicked(bool)), trajectoryVisualisation, SLOT(setColoration(bool)));

    // Dimension change control
    connect(ui->trajectoryDim1SpinBox , SIGNAL(valueChanged(int)), trajectoryVisualisation, SLOT(setAbscissa(int)));
    connect(ui->trajectoryDim2SpinBox , SIGNAL(valueChanged(int)), trajectoryVisualisation, SLOT(setOrdinate(int)));
    connect(ui->fitnessDim1SpinBox , SIGNAL(valueChanged(int)), fitnessLandscape, SLOT(setAbscissa(int)));
    connect(ui->fitnessDim2SpinBox , SIGNAL(valueChanged(int)), fitnessLandscape, SLOT(setOrdinate(int)));
    connect(ui->dimensionSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setMaxDimensionTrajectory(int)));

    // Density scaling
    connect(ui->densityScalineComboBox, SIGNAL(currentIndexChanged(int)), densityVisualisation, SLOT(setScalingType(int)));

    // Fitness landscape range
    connect(ui->fitnessColorMinSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMinFitnessColor(double)));
    connect(ui->fitnessColorMaxSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setMaxFitnessColor(double)));
    connect(ui->fitnessColorMaxSpinBox, SIGNAL(valueChanged(double)), fitnessLandscape, SLOT(setMax(double)));
    connect(ui->fitnessColorMinSpinBox, SIGNAL(valueChanged(double)), fitnessLandscape, SLOT(setMin(double)));

    connect(ui->displayAllFitnessCheckBox, SIGNAL(clicked(bool)), fitnessVisualisation, SLOT(setDisplayStyle(bool)));
    connect(ui->previousPosSpinBox , SIGNAL(valueChanged(int)), trajectoryVisualisation, SLOT(setPreviousPosition(int)));
    reloadSimulationParameterFromUi();

    slotReset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectVisualisation(AbstractVisualisation *visualisation)
{
    visualisation->setSwarmManager(m_swarmManager); // Connect swarmmanager and visualization
    visualisation->setScreenshot(m_screenshot); // Connect file management with visualization
    connect(m_swarmManager, SIGNAL(resetRequested()), visualisation, SLOT(reset())); // Reset trigger
    connect(m_swarmManager, SIGNAL(stepped()), visualisation, SLOT(performStepComputation())); // Step trigger

    connect(ui->screenshotsPushButton, SIGNAL(clicked()), visualisation, SLOT(save())); // Snapshot from visualization

}

void MainWindow::slotReset()
{
    QString text = QString("%1\n%2").arg(tr("Current run: %n", "", 0),
                                         tr("Current step: %n", "", 0));
    ui->infoLabel->setText(text);
}

void MainWindow::slotCurrentIterationChanged(int run, int step, double fitness_value)
{
    char text[100];
    sprintf(text, "Current run: %i\nCurrent step: %i\nBest fitness: %f", run, step, fitness_value);
    QString label = QString(text);
    ui->infoLabel->setText(label);
}

void MainWindow::setSimulationSpeed(int speed)
{
    int time = (ui->speedHorizontalSlider->maximum() - speed)*20;
    m_swarmManager->setTimerInterval(time);
    ui->speedLabel->setText("Speed: " + QString::number(time) +  " ms delay");
}

void MainWindow::setMaxDimensionTrajectory(int value)
{
    ui->trajectoryDim1SpinBox->setMaximum(value);
    ui->trajectoryDim2SpinBox->setMaximum(value);
    ui->fitnessDim1SpinBox->setMaximum(value);
    ui->fitnessDim2SpinBox->setMaximum(value);
}

void MainWindow::setMaximumNeighboursNumber(int particulesNumber)
{
    ui->numberNeighborSpinBox->setMaximum (particulesNumber);
}


void MainWindow::filesBrowsing()
{
    bool isDir = true;
    QPushButton *button = (QPushButton *)sender();
    QString message;
    QObject * receiver;

    // Determine receiver of the chosen file
    if (button->objectName() == "outputDirPushButton")
    {
        message = "Ouput directory";
        receiver = ui->outputDirTextEdit;
    }
    else if (button->objectName() == "inputDirPushButton")
    {
        message = "Input directory";
        receiver = ui->inputDirTextEdit;
    }
    else if (button->objectName() == "inputParamPushButton")
    {
        isDir = false;
        message = "Input parameter file";
        receiver = ui->inputParamTextEdit;
    }

    QString output;
    QFileDialog * filedialog = new QFileDialog();
    if(isDir)
        output = filedialog->getExistingDirectory(ui->tabWidget, message, getenv("HOME"), QFileDialog::ShowDirsOnly);
    else
        output = filedialog->getOpenFileName(ui->tabWidget, message, getenv("HOME"));
    if (output == "")
        return;
    connect(this, SIGNAL(fileToTextEdit(QString)), receiver, SLOT(setText(QString)));
    emit fileToTextEdit(output);
    disconnect(receiver);

}

void MainWindow::resetInput(QAbstractButton * button)
{
    if (ui->buttonBox->buttonRole(button) != QDialogButtonBox::ResetRole)
        return;
    connect(this, SIGNAL(fileToTextEdit(QString)), ui->inputDirTextEdit, SLOT(setText(QString)));
    connect(this, SIGNAL(fileToTextEdit(QString)), ui->inputParamTextEdit, SLOT(setText(QString)));
    connect(this, SIGNAL(fileToTextEdit(QString)), ui->inputInfoLabel, SLOT(setText(QString)));
    connect(this, SIGNAL(fileToTextEdit(QString)), ui->inputInfoLabel_2, SLOT(setText(QString)));
    connect(this, SIGNAL(fileToTextEdit(QString)), m_screenshot, SLOT(setInParamName(QString)));
    connect(this, SIGNAL(fileToTextEdit(QString)), m_screenshot, SLOT(setInputDir(QString)));
    emit fileToTextEdit("");
    disconnect(ui->inputDirPushButton);
    disconnect(ui->inputParamPushButton);
    disconnect(this, SIGNAL(fileToTextEdit(QString)), m_screenshot, SLOT(setInParamName(QString)));
    disconnect(this, SIGNAL(fileToTextEdit(QString)), m_screenshot, SLOT(setInputDir(QString)));
}

void MainWindow::launchReadSimulation(QAbstractButton *button)
{
    if (ui->buttonBox->buttonRole(button) != QDialogButtonBox::AcceptRole)
        return;
    if (!m_screenshot->isReadingReady())
        return;

    ui->tabWidget->setCurrentIndex(0);
    ui->isReadCheckBox->setEnabled(true);
    if (!ui->isReadCheckBox->isChecked())
        ui->isReadCheckBox->click();
}


void MainWindow::dispInputDim(int dim)
{
    char text[100];
    sprintf(text, "Dimensions: %i", dim);
    QString label = QString(text);
    ui->inputInfoLabel_2->setText(label);
}

void MainWindow::dispPartnumAndMaxiter(int particles, int iterations)
{
    char text[100];
    sprintf(text, "Swarm size: %i\nNumber of iterations: %i", particles, iterations);
    QString label = QString(text);
    ui->inputInfoLabel->setText(label);
}

void MainWindow::toggleSimulationMode(bool isRead)
{
    // Disable/enable the swarm parameter tab
   ui->tabWidget->setTabEnabled(2, !isRead);

   // Give proper density color scaling parameters
   QVariant v(0);
   if (isRead)
   {
       //Disable simulation specific option

       // Enable all options
       QVariant v(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       QModelIndex index = ui->densityScalineComboBox->model()->index(0,0);
       ui->densityScalineComboBox->model()->setData( index, v, Qt::UserRole -1);

       index = ui->densityScalineComboBox->model()->index(1,0);
       ui->densityScalineComboBox->model()->setData( index, v, Qt::UserRole-1);

       index = ui->densityScalineComboBox->model()->index(2,0);
       ui->densityScalineComboBox->model()->setData( index, v, Qt::UserRole-1);

       index = ui->fitnessColorComboBox->model()->index(0,0);
       ui->fitnessColorComboBox->model()->setData( index, v, Qt::UserRole-1);

       index = ui->fitnessColorComboBox->model()->index(1,0);
       ui->fitnessColorComboBox->model()->setData( index, v, Qt::UserRole-1);

       index = ui->fitnessColorComboBox->model()->index(2,0);
       ui->fitnessColorComboBox->model()->setData( index, v, Qt::UserRole-1);


       // Set selected to 1
       ui->fitnessColorComboBox->setCurrentIndex(1);
       ui->densityScalineComboBox->setCurrentIndex(1);
   }
   else
   {
       // disable reading specific option
       QModelIndex index = ui->densityScalineComboBox->model()->index(1,0);
       ui->densityScalineComboBox->model()->setData( index, v, Qt::UserRole -1);

       index = ui->fitnessColorComboBox->model()->index(1,0);
       ui->fitnessColorComboBox->model()->setData( index, v, Qt::UserRole-1);

       // enable simulation specific option
       QVariant v(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
       index = ui->densityScalineComboBox->model()->index(0,0);
       ui->densityScalineComboBox->model()->setData( index, v, Qt::UserRole-1);

       index = ui->densityScalineComboBox->model()->index(2,0);
       ui->densityScalineComboBox->model()->setData( index, v, Qt::UserRole -1);

       index = ui->fitnessColorComboBox->model()->index(0,0);
       ui->fitnessColorComboBox->model()->setData( index, v, Qt::UserRole-1);

       index = ui->fitnessColorComboBox->model()->index(2,0);
       ui->fitnessColorComboBox->model()->setData( index, v, Qt::UserRole-1);


       // Set selected to 0
       ui->fitnessColorComboBox->setCurrentIndex(0);
       ui->densityScalineComboBox->setCurrentIndex(0);
   }
   ui->iterationRangeLabel->setEnabled(isRead);
   ui->minIterationSpinBox->setEnabled(isRead);
   ui->maxIterationSpinBox->setEnabled(isRead);

   if(isRead)
       return;
   // Reload all the simulation parameters
   reloadSimulationParameterFromUi();
}

void MainWindow::reloadSimulationParameterFromUi()
{
   m_swarmManager->setDimension(ui->dimensionSpinBox->value(), false);
   m_swarmManager->setSize(ui->particlesSpinBox->value(), false);
   m_swarmManager->setNoise(ui->noiseDoubleSpinBox->value(), false);
   m_swarmManager->setFitnessFunctionIndex(ui->fitnessFunctionComboBox->currentIndex(), false);
   m_swarmManager->setMaximum(ui->maximumDoubleSpinBox->value(), false);
   m_swarmManager->setMinimum(ui->minimumDoubleSpinBox->value(), false);
   m_swarmManager->setMaximumVelocity(ui->maximumVelocityDoubleSpinBox->value(), false);
   m_swarmManager->setInertia(ui->inertiaDoubleSpinBox->value(), false);
   m_swarmManager->setMaxIterations(ui->maxIterationsSpinBox->value(), false);
   m_swarmManager->setLocalBestWeight(ui->localWeightDoubleSpinBox->value(), false);
   m_swarmManager->setNeighbourBestWeight(ui->neighbourWeightDoubleSpinBox->value(), false);
   m_swarmManager->setNeighbourNumber(ui->numberNeighborSpinBox->value());

}

void MainWindow::setNewRange(int min, int max)
{
    ui->minIterationSpinBox->setMaximum(max);
    ui->maxIterationSpinBox->setMinimum(min);
}

void MainWindow::newRealMax(int max)
{
    ui->maxIterationSpinBox->setMaximum(max);

}

void MainWindow::enableFitnessTrajectoryColoring(bool enable)
{
    ui->fitnessColorLabel->setEnabled(enable);
    ui->fitnessColorComboBox->setEnabled(enable);
   // Custom fitness range
   ui->fitnessRangeLabel->setEnabled(enable);
   ui->fitnessRangeMaxSpinBox->setEnabled(enable);
   ui->fitnessRangeMinSpinBox->setEnabled(enable);

}

void MainWindow::setMinFitnessRange(int newMin)
{
    ui->fitnessRangeMaxSpinBox->setMinimum(newMin + 1);
}

void MainWindow::setMaxFitnessRange(int newMax)
{
    ui->fitnessRangeMinSpinBox->setMaximum(newMax - 1);
}
void MainWindow::setMinFitnessColor(double newMin)
{
    ui->fitnessColorMaxSpinBox->setMinimum(newMin + 0.00001);
}

void MainWindow::setMaxFitnessColor(double newMax)
{
    ui->fitnessColorMinSpinBox->setMaximum(newMax - 0.00001);
}

