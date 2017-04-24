#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T18:45:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP_Qt1
TEMPLATE = app


SOURCES +=\
    Patient.cpp \
    AddPatientForm.cpp \
    AddStaffForm.cpp \
    LoginWindow.cpp \
    Main.cpp \
    MainWindow.cpp \
    Staff.cpp

HEADERS  += \
    Patient.h \
    AddStaffForm.h \
    AddPatientForm.h \
    LoginForm.h \
    MainWindow.h \
    Staff.h

FORMS    += \
    LoginForm.ui \
    MainWindow.ui \
    AddStaffForm.ui \
    AddPatientForm.ui
