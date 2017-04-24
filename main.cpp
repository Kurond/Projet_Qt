#include "MainWindow.h"
#include "LoginForm.h"
#include "AddStaffForm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    LoginWindow loginWindow;
    AddStaffForm staffWindow;

    QObject::connect(&loginWindow, SIGNAL(connectionSucceded(bool)), &mainWindow, SLOT(setVisible(bool)));
    QObject::connect(&loginWindow, SIGNAL(connectionCancel()), &app, SLOT(quit()));
    QObject::connect(&loginWindow, SIGNAL(connectionSucceded(bool)), &loginWindow, SLOT(onConnection(bool)));

    QObject::connect(&mainWindow, SIGNAL(openAddStaff()), &staffWindow, SLOT(displayAddStaff()));
    QObject::connect(&mainWindow, SIGNAL(quit()), &app, SLOT(quit()));

    //mainWindow.show();
    loginWindow.show();

    return app.exec();
}
