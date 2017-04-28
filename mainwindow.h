#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AddPatientForm.h"
#include "QStandardItemModel"
#include "Staff.h"

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
    QStandardItemModel * standardModel;
    QList<QStandardItem *> typesList;

private slots:
    void quit_clicked();
    void addPatient();
};

#endif // MAINWINDOW_H
