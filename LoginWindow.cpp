#include <iostream>
#include <QMessageBox>
#include "LoginForm.h"
#include "ui_LoginForm.h"
#include "AccountConnector.h"
#include "Account.h"

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

bool LoginWindow::future_dbconnection() {
    AccountConnector accountConnector;
    Account account = accountConnector.getOne(ui->loginText->text().toStdString(), "Login");

    if (ui->passText->text().toStdString() == account.getPassword()) {
         return true;
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
    if (future_dbconnection()) {
        emit connectionSucceded(true);
    } else {
        emit connectionSucceded(false);
    }
}

void LoginWindow::on_cancelButon_clicked() {
    emit connectionCancel();
}
