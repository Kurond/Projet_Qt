#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T18:45:42
#
#-------------------------------------------------

QT      += core gui
QT      += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TP_Qt1
TEMPLATE = app


SOURCES +=\
    Patient.cpp \
    AddPatientForm.cpp \
    AddStaffForm.cpp \
    LoginWindow.cpp \
    MainWindow.cpp \
    Staff.cpp \
    StaffType.cpp \
    main.cpp \
    c_init_bd.cpp \
    Connector.cpp \
    StaffConnector.cpp \
    Account.cpp \
    StaffTypeConnector.cpp

HEADERS  += \
    Patient.h \
    AddStaffForm.h \
    AddPatientForm.h \
    LoginForm.h \
    MainWindow.h \
    Staff.h \
    StaffType.h \
    c_init_bd.h \
    Connector.h \
    StaffConnector.h \
    Account.h \
    StaffTypeConnector.h

FORMS    += \
    LoginForm.ui \
    MainWindow.ui \
    AddStaffForm.ui \
    AddPatientForm.ui
