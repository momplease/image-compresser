#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T22:46:23
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Compresser
TEMPLATE = app


SOURCES += main.cpp\
    tinifycompresser.cpp \
    imageinfo.cpp \
    compresser.cpp \
    imageinfomodel.cpp \
    mainwindowcontroller.cpp

HEADERS  += \
    icompressible.h \
    tinifycompresser.h \
    compresser.h \
    imageinfo.h \
    imageinfomodel.h \
    mainwindowcontroller.h

FORMS    += mainwindow.ui


RESOURCES +=
