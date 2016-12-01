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
        mainwindow.cpp \
    tinifycompresser.cpp \
    imageinfo.cpp \
    compresser.cpp

HEADERS  += mainwindow.h \
    icompressible.h \
    tinifycompresser.h \
    compresser.h \
    imageinfo.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/Cellar/pngquant/2.7.1/include
INCLUDEPATH += /usr/local/Cellar/libpng/1.6.25/include
LIBS += /usr/local/Cellar/libpng/1.6.25/lib/libpng.dylib
LIBS += /usr/local/Cellar/pngquant/2.7.1/lib/libimagequant.a

RESOURCES +=
