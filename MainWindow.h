#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "AddPatientForm.h"
#include "QStandardItemModel"
#include "StaffConnector.h"
#include "ConsultConnector.h"
#include "StaffTypeConnector.h"
#include "PatientConnector.h"
#include "AccountConnector.h"
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
    QStandardItemModel * _standardModel;
    QList<QStandardItem *> _typeItemsList;

    StaffConnector* _staffConnector;
    PatientConnector* _patientConnector;
    StaffTypeConnector* _staffTypeConnector;
    ConsultConnector* _consultConnector;
    AccountConnector* _accountConnector;

private slots:
    void quit_clicked();
    void addPatient();
};

#endif // MAINWINDOW_H
