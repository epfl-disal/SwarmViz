TEMPLATE = app
TARGET = swarmviz

QT = core gui
QT += widgets
QT += printsupport

HEADERS +=  \
            pso/particle.h \
            pso/swarm.h \
            view/swarmmanager.h \
            view/visualisationhelper.h \
            view/abstractvisualisation.h \
            view/trajectoryvisualisation.h \
            view/densityvisualisation.h \
            view/linesvisualisation.h \
            view/fitnessvisualisation.h \
    view/euclideanvisualisation.h \
            mainwindow.h \
            view/sammonvisualisation.h \
	    qcustomplot/qcustomplot.h \
    support/screenshots.h \
    view/fitnesslandscape.h \
    sammon/codegen/dll/sammon/eye.h \
    sammon/codegen/dll/sammon/power.h \
    sammon/codegen/dll/sammon/randn.h \
    sammon/codegen/dll/sammon/rdivide.h \
    sammon/codegen/dll/sammon/rt_nonfinite.h \
    sammon/codegen/dll/sammon/rtGetInf.h \
    sammon/codegen/dll/sammon/rtGetNaN.h \
    sammon/codegen/dll/sammon/rtwtypes.h \
    sammon/codegen/dll/sammon/sammon_data.h \
    sammon/codegen/dll/sammon/sammon_emxAPI.h \
    sammon/codegen/dll/sammon/sammon_emxutil.h \
    sammon/codegen/dll/sammon/sammon_initialize.h \
    sammon/codegen/dll/sammon/sammon_terminate.h \
    sammon/codegen/dll/sammon/sammon_types.h \
    sammon/codegen/dll/sammon/sammon.h \
    sammon/codegen/dll/sammon/sqrt.h \
    sammon/codegen/dll/sammon/sum.h \
    view/pbestvisualisation.h \
    support/fitnessfunction.h \
    pso/psohelper.h
SOURCES +=  main.cpp \
            pso/psohelper.cpp \
            pso/particle.cpp \
            pso/swarm.cpp \
            view/swarmmanager.cpp \
            view/visualisationhelper.cpp \
            view/abstractvisualisation.cpp \
            view/trajectoryvisualisation.cpp \
            view/densityvisualisation.cpp \
            view/linesvisualisation.cpp \
            view/fitnessvisualisation.cpp \
            mainwindow.cpp \
            view/sammonvisualisation.cpp \
	    qcustomplot/qcustomplot.cpp \
    support/screenshots.cpp \
    view/fitnesslandscape.cpp \
    view/euclideanvisualisation.cpp \
    sammon/codegen/dll/sammon/eye.c \
    sammon/codegen/dll/sammon/power.c \
    sammon/codegen/dll/sammon/randn.c \
    sammon/codegen/dll/sammon/rdivide.c \
    sammon/codegen/dll/sammon/rt_nonfinite.c \
    sammon/codegen/dll/sammon/rtGetInf.c \
    sammon/codegen/dll/sammon/rtGetNaN.c \
    sammon/codegen/dll/sammon/sammon_data.c \
    sammon/codegen/dll/sammon/sammon_emxAPI.c \
    sammon/codegen/dll/sammon/sammon_emxutil.c \
    sammon/codegen/dll/sammon/sammon_initialize.c \
    sammon/codegen/dll/sammon/sammon_terminate.c \
    sammon/codegen/dll/sammon/sammon.c \
    sammon/codegen/dll/sammon/sqrt.c \
    sammon/codegen/dll/sammon/sum.c \
    view/pbestvisualisation.cpp \
    support/fitnessfunction.cpp
FORMS +=    mainwindow.ui

OTHER_FILES += \
    sammon/codegen/dll/sammon/sammon_ref.rsp \
    sammon/codegen/dll/sammon/buildInfo.mat \
    sammon/codegen/dll/sammon/codeInfo.mat \
    sammon/codegen/dll/sammon/rtw_proj.tmw \
    sammon/codegen/dll/sammon/sammon_rtw.mk \
    sammon/codegen/dll/sammon/sammon.def

Release:DESTDIR = bin
Release:OBJECTS_DIR = bin/.obj
Release:MOC_DIR = bin/.moc
Release:RCC_DIR = bin/.rcc
Release:UI_DIR = bin/.ui
