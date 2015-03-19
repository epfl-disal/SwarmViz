/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
 * Copyright (C) 2013 Guillaume Jornod <guillaume.jornod@gmail.com> Additional          *
 *      rainbowCoding implementations, gradient                                        *
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
 * @file visualisationhelper.cpp
 * @short Implementation of class VisualisationHelper
 */

#include "visualisationhelper.h"
#include "QtCore/QDebug"
#include <math.h>
const double pi = 4.0 * atan(1.0);

QColor VisualisationHelper::rainbowCoding(int index, int count)
{
    int h = 360 / count * index;
    return QColor::fromHsv(h, 255, 255);
}
QColor VisualisationHelper::rainbowCoding(int index, int count, const double * performance, const double min, const double max)
{

    double R = (255*(performance[index] - min))/(max - min);
    R = (R>255)?255:R;
    R = (R<0)?0:R;
    return QColor::fromRgb(R, 255-R, 0);
}

QColor VisualisationHelper::rainbowCoding(int index, int count, const QVector<double> performance, const double min, const double max)
{
    int gBegin = 10;
    int rBegin = 255;
    int gEnd = 230;
    int rEnd = 10;
    double dr = (rEnd - rBegin)/count;
    double dg = (gEnd - gBegin)/count;
    double R = rBegin + dr*(count - index);
    double G = gBegin + dg*(count - index);

    /*
    double R = (255*(performance[index] - min))/(max - min);
*/
    R = (R>255)?255:R;
    R = (R<0)?0:R;
    G = (G>255)?255:G;
    G = (G<0)?0:G;
    return QColor::fromRgb(R, G, 0);
}


QColor VisualisationHelper::gradient(const int index, const int size)
{
    double frequency = pi/size;
    double m = 127.0;
    double p = 128.0;
    int ind = size - index;
    double red = cos(frequency*ind + 0) * m + p;
    double green = cos(frequency*ind + 2.0*pi/3.0) * m + p;
    double blue  = cos(frequency*ind + 4.0*pi/3.0) * m + p;

    //qDebug() << index << " " << red << " " << green << " " << blue;

    return QColor::fromRgb(red, green, blue);
}
