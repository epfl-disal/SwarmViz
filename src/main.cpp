/****************************************************************************************
 * Copyright (C) 2013 Guillaume Jornod <guillaume.jornod@gmail.com>                     *
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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
 * @file main.cpp
 * @short Entry point of the program
 */
#include <QApplication>
#include "mainwindow.h"
/**
  \mainpage
  Machine learning optimization techniques are widely used for mobile robotics in the scope of distributed learning. Using these techniques,
 robots learn complex behavior in which human design would be far from optimal. Several techniques are used, such as Genetic Algorithms (GAs) or Particle Swarm Optimization (PSO).
 This project focuses on PSO, but is extendible to other adaptation algorithms.

Particle Swarm Optimization is a relatively new meta-heuristic introduced in 1995\cite eberhart1995new. Inspired by the movement of birds, this optimization
algorithm lets particles, candidate solutions, move in a n-dimensional space corresponding to the search space of the problem. The movement of the particles is
influenced by best performances achieved until a satisfying convergence is obtained.

However, the learning of behavior with such machine learning techniques has a dramatic cost. The evaluation of each
candidate solution leads to a real-life experiment, increasing dramatically the cost of the learning. Additionally, sensor noise leads
 to a need of reevaluation, which increases even more the cost of the optimization process \cite di2012distributed.

Moreover, PSO has a significant amount of parameters, which all impacts drastically the efficiency of the algorithm. Working with classical benchmark
functions allows to take advantage of an initial guess regarding these parameters and the possibility to tweak the algorithm parameters until satisfactory
convergence. When it comes to distributed learning with mobile robots, the initial insight is less instinctive, and the parameters tweaking has a huge cost.

Furthermore, robotic learning processes are high dimensional problems, for instance, the learning of a behavior with e-pucks (\cite mondada2009puck), using a Braitenberg controller,
 leads to a 22 dimensions problem. This high dimensionality is a computational concern, but also leads to a complexification of the visualization of the states of the algorithm.

Thus, there is a need for a tool to visualize what is happening during the optimization process. This visualization should lead to
the understanding of the impact of the parameters by studying the behavior of the PSO with benchmark functions, and by observing the learning with real-life robots. This tool is the scope of the present project.

\author Guillaume Jornod

*/

/**
 * @brief Entry point of the program
 * @param argc argc.
 * @param argv argv.
 * @return exit code.
 */
int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    setlocale(LC_NUMERIC, "C");

    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}
