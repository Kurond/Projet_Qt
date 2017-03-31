#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T18:45:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP_Qt1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    addpatient.cpp \
    healthcarestaff.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    addpatient.h \
    healthcarestaff.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    addpatient.ui \
    healthcarestaff.ui
