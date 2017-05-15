#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "AccountConnector.h"
namespace Ui {
class LoginWindow;
}

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();
    void login();

signals:
    void connectionCancel();
    void connectionSucceded(bool success);

private:
    Ui::LoginWindow *ui;
    bool isLoginCorrect();

    AccountConnector* _accountConnector;

public slots:
    void onConnection(bool success);

private slots:
    void on_connectButton_clicked();
    void on_cancelButon_clicked();
};



#endif // LOGINWINDOW_H
