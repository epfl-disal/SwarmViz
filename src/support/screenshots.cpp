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

#include "screenshots.h"
#include <QtCore/QDebug>
#include <QApplication>
#include <QComboBox>
#include <sys/stat.h>
#include "pso/particle.h"
#include "pso/swarm.h"
/**
  * @file screenshots.cpp
  * @short Definition of the class screenshots
  **/


Screenshots::Screenshots(QObject *parent):QObject(parent)
{
    m_quality = -1;
    m_scale = 1;
    m_size = 500;
    m_swarmsize = 0;
    m_dimension = 0;
    m_maxiteration = 0;
    m_outputdir = "/tmp";
    m_ui = (MainWindow *) QApplication::activeWindow();
    m_writeStates = false;
    m_inParamName = "";
    m_isRead = false;
    m_format = 0;
}

void Screenshots::setOutputDir(QString outputdir)
{
    m_outputdir = outputdir + "/simulation_" + QString::number(time(0));
    mkdir(m_outputdir.toStdString().c_str(), 0777);
    m_writeStates = true;
    emit resetSwarmManager();
}

void Screenshots::formatChange(int format)
{
    QComboBox *combobox = (QComboBox *)sender();
    m_format = format;
    switch(format)
    {
    case PDF:
        combobox->parent()->findChild<QWidget *>((QString) "scaleDoubleSpinBox")->setEnabled(false);
        combobox->parent()->findChild<QWidget *>((QString) "qualitySpinBox")->setEnabled(false);
        break;
    case BMP:
        combobox->parent()->findChild<QWidget *>((QString) "scaleDoubleSpinBox")->setEnabled(true);
        combobox->parent()->findChild<QWidget *>((QString) "qualitySpinBox")->setEnabled(false);
        break;
    case PNG:
    case JPG:
        combobox->parent()->findChild<QWidget *>((QString) "scaleDoubleSpinBox")->setEnabled(true);
        combobox->parent()->findChild<QWidget *>((QString) "qualitySpinBox")->setEnabled(true);
        break;
    default:
        combobox->parent()->findChild<QWidget *>((QString) "scaleDoubleSpinBox")->setEnabled(false);
        combobox->parent()->findChild<QWidget *>((QString) "qualitySpinBox")->setEnabled(false);
    }

}

void Screenshots::setQuality(int quality)
{
    m_quality = quality;
}

void Screenshots::setSize(int size)
{
    m_size = size;
}

void Screenshots::setScale(double scale)
{
    m_scale = scale;
}

void Screenshots::getSubdir(char subdir[]) const
{
    long int now = static_cast<long int>(time(0));
    struct stat sb;
    char outDir[400];
    bool found = false;
    // Verify is a directoy has been created in the last 2 seconds
    for (int i =-2; i < 1; i++)
    {
        sprintf(outDir, "%s/%li", m_outputdir.toStdString().c_str(), now + i);
        if (stat(outDir, &sb) == 0 && S_ISDIR(sb.st_mode))
        {    if (!m_writeStates)
                return;
            found = true;
            sprintf(subdir, "%li", now+i);
            break;
        }
    }
    if (!found)
    {
        sprintf(subdir, "%li", now);
        sprintf(outDir, "%s/%s", m_outputdir.toStdString().c_str(), subdir);
        int f = mkdir(outDir, 0777);
        if(f < 0)
        {
            qDebug() << "Fail to create output directory " << outDir;
        }
    }
}

void Screenshots::saveScreenshots(const char subdir[20], AbstractVisualisation *visualisation) const
{
    QString outputName =  m_outputdir + "/" + subdir + "/" + visualisation->m_titlePlot;
    switch(m_format)
    {
    case PDF:
        outputName += ".pdf";
        visualisation->savePdf(outputName, m_quality, m_size, m_size);
        break;
    case BMP:
        outputName += ".bmp";
        visualisation->saveBmp(outputName, m_size, m_size, m_scale);
        break;
    case PNG:
        outputName += ".png";
        visualisation->savePng(outputName, m_size, m_size, m_scale, m_quality);
        break;
    case JPG:
        outputName += ".jpg";
        visualisation->saveJpg(outputName, m_size, m_size, m_scale, m_quality);
        break;
    }
}

void Screenshots::writePsoParam(const int maxIter, const int size) const
{
    if (!m_writeStates)
        return;
    QString filename;
    FILE *output;
    // param file file name
    filename = m_outputdir+"/pso_param.txt";

    output = fopen(filename.toStdString().c_str(),"w");
    if(output == NULL){
        qDebug() << "opening file failed";
    }

    fprintf(output, "fit_its_pso 640\n");
    fprintf(output, "fit_its_eval 640\n");
    fprintf(output, "noisy 1\n");
    fprintf(output, "total_its %d\n", maxIter);
    fprintf(output, "swarmsize %d\n", size);

    fclose(output);

}

void Screenshots::setInputDir(QString inputdir)
{
    // Write PSO param in file
    struct stat sb;

    // Check if the directoy exists
    if (stat(inputdir.toStdString().c_str(), &sb) != 0 || !S_ISDIR(sb.st_mode))
    {
        qDebug() << "Fail to open dir " << inputdir;
        return;
    }
    m_inputdir = inputdir;

    readDimension();
    setGlobalMinMax();

    // Looks for pso_params.txt
    inputdir += "/pso_params.txt";
    FILE *params;
    params = fopen(inputdir.toStdString().c_str(),"r");
    if (params != NULL)
    {
        emit inputParamFound(inputdir);
    }
}

void Screenshots::setInParamName(QString inparamname)
{
    m_inParamName = inparamname;
    readPsoParam();
    setGlobalMinMax();
}

void Screenshots::readPsoParam()
{
    // Load PSO parameters from output files
    char param_name[255];
    FILE *params;
    int param_value;
    params = fopen(m_inParamName.toStdString().c_str(),"r");
    if(params == NULL)
        qDebug() << "Unable to open PSO parameters file" << m_inParamName ;
    else
    {
        while(fscanf(params,"%s %d",param_name,&param_value)>0){
            /*
            if(strcmp(param_name,"fit_its_pso")==0){
                psodata->fit_its_pso=param_value;
            }else if(strcmp(param_name,"fit_its_eval")==0){
                psodata->fit_its_eval=param_value;
            }else*/ if(strcmp(param_name,"swarmsize")==0){
                m_swarmsize = param_value;
            }else if(strcmp(param_name,"total_its")==0){
                m_maxiteration = param_value;
            }/*else if(strcmp(param_name,"noisy")==0){
                psodata->noisy=param_value;
            }*/
            else{
                printf("Unknown parameter %s in %s\n",param_name, m_inParamName.toStdString().c_str());
            }
        }
        fclose(params);
    }

    emit readPartNum(m_swarmsize, m_maxiteration);
}

void Screenshots::readDimension()
{
    FILE * params;
    int dim = -1;
    // Get the dimension and swarm size from first Bstate file
    QString filename = m_inputdir + "/" + "state_0_0.txt";
    params = fopen(filename.toStdString().c_str(),"r");
    if(params == NULL)
        qDebug() << "Unable to open first state file" <<filename;
    else
    {
        dim = 0;
        double tmp[4];
        fscanf(params, "Particle 0");
        while(fscanf(params, "%lf %lf %lf %lf", &tmp[0], &tmp[1], &tmp[2], &tmp[3])>0)
        {
            dim++;
        }
        m_dimension = dim;
    }
    emit readDimChanged(dim);

}

void Screenshots::getReadParam(SwarmManager *swarmmanager) const
{
    swarmmanager->setDimension(m_dimension, false);
    swarmmanager->setSize(m_swarmsize, false);
    swarmmanager->setMaxIterations(m_maxiteration, false);
}

bool Screenshots::isReadingReady() const
{
    return (m_dimension >0 && m_swarmsize > 0 && m_maxiteration >0);
}

void Screenshots::setReadOrSimulate(bool isRead)
{
    m_isRead = isRead;
    emit resetSwarmManager();
}

bool Screenshots::isRead() const
{
    return m_isRead;
}

void Screenshots::writeState(const QVector<double> best, Swarm * swarm, int iteration) const
{
    if (!m_writeStates)
        return;
    FILE *output;
    QString filename;
    filename = m_outputdir + "/state_0_" + QString::number(iteration) + ".txt";
    output = fopen(filename.toStdString().c_str(), "w");
    if(output == NULL)
    {
            qDebug() << "opening file failed";
            return;
    }
    for (int i = 0; i < swarm->size(); i++) {
        Particle *particle = (*swarm)[i];
        fprintf(output, "Particle %d\n", i);
        //qDebug() << "Particle " << i;
        for (int j = 0; j < swarm->dimension(); j++)
        {
            fprintf(output, "%e %e %e %e\n",particle->position[j], particle->localBest[j],particle->neighbourBest[j],particle->velocity[j]);
            //qDebug() << particle->position[j] << "" << particle->localBest[j]<< " " <<particle->neighbourBest[j] << " " <<particle->velocity[j];
        }
        fprintf(output, "Fitness %d\n", i);
        fprintf(output, "%e %e %i %e\n", swarm->m_performance[i],particle->localBestPerformance, particle->age,particle->neighbourBestPerformance);
    }
    fprintf(output, "Gbest\n");
    for (int i = 0; i < swarm->dimension(); i++)
    {
        fprintf(output, "%e\n", best[i]);

    }
    fprintf(output, "Fitness ");
    fprintf(output, "%e", swarm->m_bestPerformance);
    fclose(output);
}

const QVector<double> Screenshots::readState(Swarm * swarm, int iteration, const bool firstIt) const
{
    qDebug() << iteration;
    char input[100];
    int i, j, read_n;
    FILE *fp;
    double tmp[4];
    QString filename;
    double range[2];
    if (firstIt)
    {
        swarm->m_initFitnessRange[0] = 1000000;
        swarm->m_initFitnessRange[1] = -1000000;
    }

    // Initialize min and max if first iteration
    if(iteration < 0)
    {
        range[0] = 10000;
        range[1] = -10000;
    }

    // State file name
    filename = m_inputdir + "/state_0_" + QString::number(iteration) + ".txt";
    fp = fopen(filename.toStdString().c_str(),"r");
    if(fp == NULL){
        qDebug() << "opening file failed " << filename;
        swarm->m_errorWhileReading = true;
        Particle * particle = (*swarm)[0];
        return particle->position;
    }

    //Read data
    for (i = 0; i < m_swarmsize; i++) {
            fscanf(fp,"%s %d",input,&read_n);
            if(read_n!=i || strcmp(input,"Particle")){
                    qDebug() << "Error in file format: " << filename << " " << input << " " << read_n;
                    fclose(fp);
            }
            Particle *particle = (*swarm)[i];
            for (j = 0; j < m_dimension; j++) {
                fscanf(fp,"%lf %lf %lf %lf\n", &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
                particle->position[j] = tmp[0];
                particle->localBest[j] = tmp[1];
                particle->neighbourBest[j] = tmp[2];
                particle->velocity[j] = tmp[3];
                if(iteration < 0)
                {
                    if (tmp[0] < range[0])
                        range[0] = tmp[0];
                    if (tmp[0] > range[1])
                        range[1] = tmp[0];
                }
            }
            fscanf(fp,"%s %d",input,&read_n);
            if(strcmp(input,"Fitness")){
                qDebug() << "Error in file format: " << filename << " " << input;
                    fclose(fp);
            }
            fscanf(fp,"%lf %lf %lf %lf\n", &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
            swarm->m_performance[i] = tmp[0];
            if(firstIt && swarm->m_initFitnessRange[0] > swarm->m_performance[i])
                swarm->m_initFitnessRange[0] = swarm->m_performance[i];
            if(firstIt && swarm->m_initFitnessRange[1] < swarm->m_performance[i])
                swarm->m_initFitnessRange[1] = swarm->m_performance[i];
            particle->localBestPerformance = tmp[1];
            particle->neighbourBestPerformance = tmp[3];
    }

    fscanf(fp,"%s",input);
    if(strcmp(input,"Gbest")){
        qDebug() << "Error in file format: " << filename << " " << input;
            fclose(fp);
    }

     // Find best
    Particle *particle = (*swarm)[0];
    QVector<double> best = particle->position ;

    for (j = 0; j < swarm->m_dimension; j++) {
        fscanf(fp,"%lf\n", &tmp[0]);
        best[j] = tmp[0];
    }

    fscanf(fp,"%s",input);
    if(strcmp(input,"Fitness")){
        qDebug() << "Error in file format: " << filename << " " << input;
            fclose(fp);
    }
    fscanf(fp,"%lf\n", &tmp[0]);
    fclose(fp);
    swarm->m_bestPerformance = tmp[0];


   // Update initial range in swarm at iteration -1
    if (iteration < 0)
    {
        swarm->m_minimum = range[0];
        swarm->m_maximum = range[1];
        qDebug() << swarm->maximum();
    }

    return best;
}


void Screenshots::setGlobalMinMax()
{
    char input[100];
    int k, i, j, read_n;
    FILE *fp;
    double tmp[4];
    QString filename;
    m_globalRange[0] = 10000;
    m_globalRange[1] = -10000;
    m_globalRangeFitness[0] = 10000;
    m_globalRangeFitness[1] = -10000;

    for (k =-1; k < m_maxiteration; k++)
    {
        filename = m_inputdir + "/state_0_" + QString::number(k) + ".txt";
        fp = fopen(filename.toStdString().c_str(),"r");
        if(fp == NULL){
            qDebug() << "opening file failed " << filename;
            return;
        }

        //Read data
        for (i = 0; i < m_swarmsize; i++) {
            fscanf(fp,"%s %d",input,&read_n);
            if(read_n!=i || strcmp(input,"Particle")){
                qDebug() << "Error in file format (particle): " << filename << " " << input << " " << read_n << " " << i << " " << input;
                fclose(fp);
            }
            for (j = 0; j < m_dimension; j++) {
                fscanf(fp,"%lf %lf %lf %lf\n", &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
                if (m_globalRange[0] > tmp[0])
                    m_globalRange[0] = tmp[0];
                if (m_globalRange[1] < tmp[0])
                    m_globalRange[1] = tmp[0];
            }
            fscanf(fp,"%s %d",input,&read_n);
            if(read_n!=i || strcmp(input,"Fitness")){
                qDebug() << "Error in file format (fitness): " << filename << " " << input << " " << read_n << " " << i << " " << input;
                fclose(fp);
            }
            fscanf(fp,"%lf %lf %lf %lf\n", &tmp[0], &tmp[1], &tmp[2], &tmp[3]);
            if (m_globalRangeFitness[0] > tmp[0])
                m_globalRangeFitness[0] = tmp[0];
            if (m_globalRangeFitness[1] < tmp[0])
                m_globalRangeFitness[1] = tmp[0];


        }
    }
}

