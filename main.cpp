#include "mainwindow.h"
#include "loginwindow.h"
#include "healthcarestaff.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    LoginWindow loginWindow;
    HealthCareStaff staffWindow;

    QObject::connect(&loginWindow, SIGNAL(connectionSucceded(bool)), &mainWindow, SLOT(setVisible(bool)));
    QObject::connect(&loginWindow, SIGNAL(connectionCancel()), &app, SLOT(quit()));
    QObject::connect(&loginWindow, SIGNAL(connectionSucceded(bool)), &loginWindow, SLOT(onConnection(bool)));

    QObject::connect(&mainWindow, SIGNAL(openAddStaff()), &staffWindow, SLOT(displayAddStaff()));

    //mainWindow.show();
    loginWindow.show();

    return app.exec();
}
