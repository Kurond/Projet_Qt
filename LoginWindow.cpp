#include <iostream>
#include <QMessageBox>
#include "LoginForm.h"
#include "ui_LoginForm.h"

/**
 * @brief LoginWindow::LoginWindow
 * @param parent
 */
LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

/**
 * @brief LoginWindow::~LoginWindow
 */
LoginWindow::~LoginWindow() {
    delete ui;
}

bool LoginWindow::futureDBconnection() {
    QString tempLogin("login");
    QString tempPass("password");

    if (tempLogin == ui->loginText->text()) {
        if (tempPass == ui->passText->text()) {
            return true;
        }
    }

    return false;
}

// SLOTS

void LoginWindow::onConnection(bool success) {
    if (success) {
        this->close();
    } else {
        QMessageBox::warning(this, tr("Login error"),
            tr("The login or the passsword is wrong"),
            QMessageBox::Ok,
            QMessageBox::Cancel);

        ui->passText->setText("");
    }
}

void LoginWindow::on_connectButton_clicked() {
    if (futureDBconnection()) {
        emit connectionSucceded(true);
    } else {
        emit connectionSucceded(false);
    }
}

void LoginWindow::on_cancelButon_clicked() {
    emit connectionCancel();
}
