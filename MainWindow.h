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

    void patientRowClicked(bool success);


private slots:
    void on_addStaffPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel * _standardModel;
    QList<QStandardItem *> _typeItemsList;
    QList<Patient> _patients;

    StaffConnector* _staffConnector;
    PatientConnector* _patientConnector;
    StaffTypeConnector* _staffTypeConnector;
    ConsultConnector* _consultConnector;
    AccountConnector* _accountConnector;

private slots:
    void quit_clicked();
    void addPatient();
    void on_searchButton_clicked();
    void on_patientsTableView_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
