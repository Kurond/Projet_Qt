#include "MainWindow.h"
#include "LoginForm.h"
#include "AddStaffForm.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    StaffConnector::createDatabase();
    LoginForm loginForm;
    MainWindow * mainWindow;

    // QObject::connect(&loginWindow, SIGNAL(connectionSucceded(bool)), &mainWindow, SLOT(setVisible(bool)));

    // QObject::connect(&loginForm, SIGNAL(connectionSucceded(bool)), &loginForm, SLOT(onConnection(bool)));
    // QObject::connect(&loginForm, SIGNAL(connectionCancel()), &app, SLOT(quit()));
    // QObject::connect(&mainWindow, SIGNAL(quit()), &app, SLOT(quit()));


    if (loginForm.exec() == QDialog::Accepted) {
        mainWindow = new MainWindow();
        mainWindow->setVisible(true);
    }
    else app.quit();

    return app.exec();
}
