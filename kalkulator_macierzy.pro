#-------------------------------------------------
#
# Project created by QtCreator 2014-04-08T20:26:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kalkulator_macierzy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutauthors.cpp \
    exercises.cpp \
    equation.cpp \
    base.cpp \
    matrix.cpp \
    resultmatrix.cpp \
    technicalsupport.cpp

HEADERS  += mainwindow.h \
    aboutauthors.h \
    exercises.h \
    equation.h \
    base.h \
    matrix.h \
    resultmatrix.h \
    technicalsupport.h

FORMS    += mainwindow.ui \
    aboutauthors.ui \
    exercises.ui \
    base.ui \
    technicalsupport.ui

RESOURCES += \
    images.qrc

OTHER_FILES +=
