#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

signals:
    void connectionCancel();
    void connectionSucceded(bool success);

private:
    Ui::LoginWindow *ui;
    bool future_dbconnection();

public slots:
    void onConnection(bool success);

private slots:
    void on_connectButton_clicked();
    void on_cancelButon_clicked();
};



#endif // LOGINWINDOW_H
