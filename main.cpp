#include "mainwindow.h"
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    LoginWindow loginWindow;

    QObject::connect(&loginWindow, SIGNAL(connectionSucceded(bool)), &mainWindow, SLOT(setVisible(bool)));
    QObject::connect(&loginWindow, SIGNAL(connectionCancel()), &app, SLOT(quit()));
    QObject::connect(&loginWindow, SIGNAL(connectionSucceded(bool)), &loginWindow, SLOT(onConnection(bool)));

    //mainWindow.show();
    loginWindow.show();

    return app.exec();
}
