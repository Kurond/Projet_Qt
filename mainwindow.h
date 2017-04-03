#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void openAddStaff();
    void quit();

private slots:
    void on_addStaffPushButton_clicked();

private:
    Ui::MainWindow *ui;

private slots:
    void quit_clicked();
};

#endif // MAINWINDOW_H
