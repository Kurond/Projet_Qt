#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PatientForm.h"
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

private:
    Ui::MainWindow *ui;
    QStandardItemModel * _typesModel;
    QList<QStandardItem *> _typeItemsList;
    QList<Patient> _patients;

    StaffConnector* _staffConnector;
    PatientConnector* _patientConnector;
    StaffTypeConnector* _staffTypeConnector;
    ConsultConnector* _consultConnector;
    AccountConnector* _accountConnector;

    QSqlTableModel* _patientsModel;
    int _patientClickedIndex;

    void areButtonsEnable(bool active);
    void setupPatientTab();
    void setupStaffTab();

private slots:
    void on_addStaffPushButton_clicked();
    void quit_clicked();
    void addPatient();
    void on_searchButton_clicked();
    void on_editPatientButton_clicked();
    void on_patientsTableView_pressed(const QModelIndex &index);
    void on_patientsTableView_doubleClicked(const QModelIndex &index);
    void on_addPatientPushButton_clicked();
    void on_deletePatientButton_clicked();
};

#endif // MAINWINDOW_H
