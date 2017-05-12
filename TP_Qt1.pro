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
    Connector.cpp \
    StaffConnector.cpp \
    PatientConnector.cpp \
    Account.cpp \
    StaffTypeConnector.cpp \
    AccountConnector.cpp \
    ConsultConnector.cpp \
    Consult.cpp

HEADERS  += \
    Patient.h \
    AddStaffForm.h \
    AddPatientForm.h \
    LoginForm.h \
    MainWindow.h \
    Staff.h \
    StaffType.h \
    Connector.h \
    StaffConnector.h \
    PatientConnector.h \
    Account.h \
    StaffTypeConnector.h \
    AccountConnector.h \
    ConsultConnector.h \
    Consult.h

FORMS    += \
    LoginForm.ui \
    MainWindow.ui \
    AddStaffForm.ui \
    AddPatientForm.ui
