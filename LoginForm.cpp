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
LoginForm::LoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    _accountConnector = AccountConnector::getInstance();
    ui->setupUi(this);
}

/**
 * @brief LoginWindow::~LoginWindow
 */
LoginForm::~LoginForm() {
    delete ui;
}

bool LoginForm::future_dbconnection() {
    Account account = _accountConnector->getOne(ui->loginText->text().toStdString(), "Login");

    if (ui->passText->text().toStdString() == account.getPassword()) {
         return true;
    }

    return false;
}

// SLOTS

void LoginForm::onConnection(bool success) {
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

void LoginForm::on_connectButton_clicked() {
    if (future_dbconnection()) {
        emit connectionSucceded(true);
    } else {
        emit connectionSucceded(false);
    }
}

void LoginForm::on_cancelButon_clicked() {
    emit connectionCancel();
}
