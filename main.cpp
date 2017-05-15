#include "MainWindow.h"
#include "LoginForm.h"
#include "AddStaffForm.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    StaffConnector::loadDatabase();

    LoginForm loginForm;
    MainWindow * mainWindow;

    if (loginForm.exec() == QDialog::Accepted) {
        mainWindow = new MainWindow(app.activeWindow());
        mainWindow->setVisible(true);
    }
    else app.quit();

    return app.exec();
}
