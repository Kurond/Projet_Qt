#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddStaffForm.h"
#include "AccountConnector.h"
#include <iostream>
#include <QDebug>
#include <QString>
#include <QModelIndex>

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

    // Getting connectors instance
    _staffConnector = StaffConnector::getInstance();
    _patientConnector = PatientConnector::getInstance();
    _staffTypeConnector = StaffTypeConnector::getInstance();
    _consultConnector = ConsultConnector::getInstance();
    _accountConnector = AccountConnector::getInstance();

    // Prepare the tree view
    QList<Staff> staffList = _staffConnector->getAll();
    QList<StaffType> typeList = _staffTypeConnector->getAll();

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

    QSqlTableModel * patientsModel = _patientConnector->getTableModel(this);
    ui->patientsTableView->setModel(patientsModel);
    ui->patientsTableView->hideColumn(3);
    ui->patientsTableView->hideColumn(4);
    ui->patientsTableView->hideColumn(5);
    ui->patientsTableView->hideColumn(6);
    ui->patientsTableView->hideColumn(7);
    ui->patientsTableView->hideColumn(9);
    ui->patientsTableView->hideColumn(10);

    ui->patientsTableView->show();
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addStaffPushButton_clicked()
{
    AddStaffForm addStaffForm;
    Staff newStaff;

    // Execute staff form and wait for an accepted return
    if(addStaffForm.exec()==QDialog::Accepted)
    {
        // Get staff from form and complete it
        newStaff = addStaffForm.getStaff();
        StaffType type = _staffTypeConnector->getOne(newStaff.getType(),"Label");
        newStaff.setTypeId(type.getId());

        // Insert the staff in database
        int staffId = _staffConnector->insert(newStaff);

        // If the login was setted, the staff is an 'Informaticien'
        if (!newStaff.getLogin().empty()) {
            Account newAccount;

            newAccount.setStaffId(staffId);
            newAccount.setLogin(newStaff.getLogin());
            newAccount.setPassword(newStaff.getPassword());

            _accountConnector->insert(newAccount);

            QList<Account> accounts = _accountConnector->getAll();
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

    // Execute the patient form ans wait for an acceted return
    if (addPatientForm.exec() == QDialog::Accepted) {
        Consult consult;

        // Get the patient created with the form and add it to the database.
        Patient newPatient = addPatientForm.getPatient();
        consult._idPatient = _patientConnector->insert(newPatient);

        // Get the affected ressource and add the to the database
        QList<Staff> ressources = addPatientForm.getAffectedStaff();

        for (unsigned int i = 0; i < ressources.size(); i++) {
            consult._idRessource = ressources[i].getId();
            _consultConnector->insert(consult);
        }
    }

}

void MainWindow::on_searchButton_clicked()
{
    qDebug() << ui->searchTextBox->text();
    _patientConnector->filterModel(ui->searchTextBox->text());
}

void MainWindow::on_patientsTableView_clicked(const QModelIndex &index)
{
    qDebug() << "coucocu";
}
