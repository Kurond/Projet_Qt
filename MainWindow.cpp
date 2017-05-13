#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddStaffForm.h"
#include "StaffConnector.h"
#include "PatientConnector.h"
#include "StaffTypeConnector.h"
#include "ConsultConnector.h"
#include "AccountConnector.h"
#include <iostream>
#include <QDebug>
#include <QString>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _standardModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit_clicked()));
    connect(ui->actionPatient,  SIGNAL(triggered()), this, SLOT(addPatient()));

    StaffConnector::loadDatabase();
    StaffConnector _staffConnector;
    StaffTypeConnector _staffTypeConnector;
    PatientConnector patientConnector;

    QList<Staff> staffList = _staffConnector.getAll();
    QList<StaffType> typeList = _staffTypeConnector.getAll();

    QStandardItem * rootNode = _standardModel->invisibleRootItem();

    for (int i = 0; i < typeList.size(); ++i) {
       QStandardItem * item =  new QStandardItem(typeList.at(i).getName().c_str());
       _typeItemsList.append(item);
    }
    rootNode->appendRows(_typeItemsList);

    for (int i = 0; i < staffList.size(); i++) {
        for (int j = 0; j < _typeItemsList.size(); ++j) {
            if (staffList.at(i).getTypeId() == typeList.at(j).getId()) {
                QStandardItem * item =  new QStandardItem((staffList.at(i).getFirstName() + " " + staffList.at(i).getLastName()).c_str());
                _typeItemsList.at(j)->appendRow(item);
            }
        }
    }

    // qtree view initialization
    ui->treeView->setModel(_standardModel);
    ui->treeView->expandAll();

    QSqlTableModel * model = patientConnector.getTableModel(this);
    ui->patientsTableView->setModel(model);
    ui->patientsTableView->hideColumn(0);
    ui->patientsTableView->show();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addStaffPushButton_clicked()
{
    AddStaffForm healthCareStaff;
    Staff newStaff;

    // Execute staff form and wait for an accepted return
    if(healthCareStaff.exec()==QDialog::Accepted)
    {
        StaffConnector staffConnector;
        StaffTypeConnector typeConnector;


        // Get staff from form and complete it
        newStaff = healthCareStaff.getStaff();
        StaffType type = typeConnector.getOne(newStaff.getType(),"Label");
        newStaff.setTypeId(type.getId());

        // Insert the staff in database
        int staffId = staffConnector.insert(newStaff);

        // If the login was setted, the staff is an 'Informaticien'
        if (!newStaff.getLogin().empty()) {
            AccountConnector accountConnector;
            Account newAccount;

            newAccount.setStaffId(staffId);
            newAccount.setLogin(newStaff.getLogin());
            newAccount.setPassword(newStaff.getPassword());

            accountConnector.insert(newAccount);

            QList<Account> accounts = accountConnector.getAll();
            for (unsigned int i = 0; i < accounts.size(); i++) {
                qDebug() << accounts[i].getLogin().c_str() << " " << accounts[i].getPassword().c_str() << "\n";
            }
        }
    }

    // Recreate the tree on the window
    QListIterator<QStandardItem *> list(_typeItemsList);
    while (list.hasNext()) {
        QStandardItem * type = list.next();
        if (type->text().toStdString() == newStaff.getType()){
            QStandardItem * newStaffItem =  new QStandardItem((newStaff.getFirstName() + " " + newStaff.getLastName()).c_str());
            type->appendRow(newStaffItem);
        }
    }
}

void MainWindow::quit_clicked() {
    emit quit();
}

void MainWindow::addPatient() {
    AddPatientForm addPatientForm;
    PatientConnector patientConnector;
    ConsultConnector consultConnector;

    // Execute the patient form ans wait for an acceted return
    if (addPatientForm.exec() == QDialog::Accepted) {
        Consult consult;

        // Get the patient created with the form and add it to the database.
        Patient newPatient = addPatientForm.getPatient();
        consult._idPatient = patientConnector.insert(newPatient);

        // Get the affected ressource and add the to the database
        QList<Staff> ressources = addPatientForm.getAffectedStaff();

        for (unsigned int i = 0; i < ressources.size(); i++) {
            consult._idRessource = ressources[i].getId();
            consultConnector.insert(consult);
        }
    }

}

void MainWindow::on_searchButton_clicked()
{
    PatientConnector patientConnector;
    qDebug() << ui->searchTextBox->text();
    patientConnector.filterModel(ui->searchTextBox->text());
}
