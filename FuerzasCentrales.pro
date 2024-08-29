#-------------------------------------------------
#
# Project created by QtCreator 2017-07-07T17:19:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = FuerzasCentrales
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot/qcustomplot.cpp \
    verletalgorithm.cpp \
    verletpolares.cpp \
    verletcartesianas.cpp \
    instrucciones.cpp

HEADERS  += mainwindow.h \
    qcustomplot/qcustomplot.h \
    verletalgorithm.h \
    verletpolares.h \
    verletcartesianas.h \
    instrucciones.h

FORMS    += mainwindow.ui \
    instrucciones.ui

RESOURCES += \
    instrucciones.qrc
