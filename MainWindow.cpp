#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddStaffForm.h"
#include "AccountConnector.h"
#include <iostream>
#include <QDebug>
#include <QString>
#include <QModelIndex>
#include <QMessageBox>
#include "StringFormatter.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _typesModel(new QStandardItemModel(this))
{
    ui->setupUi(this);
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit_clicked()));
    connect(ui->actionPatient,  SIGNAL(triggered()), this, SLOT(addPatient()));

    _patientClickedIndex = -1;

    // Getting connectors instance
    _staffConnector = StaffConnector::getInstance();
    _patientConnector = PatientConnector::getInstance();
    _staffTypeConnector = StaffTypeConnector::getInstance();
    _consultConnector = ConsultConnector::getInstance();
    _accountConnector = AccountConnector::getInstance();

    // staff tree view initialization
    setupStaffTab();

    // patient table view initialization
    setupPatientTab();

    // Initiate date
    ui->beginDateEdit->setDate(QDate::currentDate());
    ui->endDateEdit->setDate(QDate::currentDate());

    ui->statusBar->showMessage("Choisissez une action");
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::arePatientButtonsEnable(bool active)
{
    ui->deletePatientButton->setEnabled(active);
    ui->editPatientButton->setEnabled(active);
}

void MainWindow::areStaffButtonsEnable(bool active)
{
    ui->deleteStaffButton->setEnabled(active);
    ui->editStaffButton->setEnabled(active);
}

void MainWindow::setupPatientTab()
{
    _patientsModel = _patientConnector->getTableModel(this);
    ui->patientsTableView->setModel(_patientsModel);
    ui->patientsTableView->hideColumn(3);
    ui->patientsTableView->hideColumn(5);
    ui->patientsTableView->hideColumn(6);
    ui->patientsTableView->hideColumn(7);
    ui->patientsTableView->hideColumn(9);
    ui->patientsTableView->hideColumn(10);
    ui->patientsTableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->patientsTableView->show();

    arePatientButtonsEnable(false);
}

void MainWindow::setupStaffTab()
{
    // Prepare the tree view
    QList<Staff> staffList = _staffConnector->getAll();
    QList<StaffType> typeList = _staffTypeConnector->getAll();

    QStandardItem * rootNode = _typesModel->invisibleRootItem();
    _typesModel->setColumnCount(4);
    _typesModel->setHeaderData(0,Qt::Horizontal,"Prénom");
    _typesModel->setHeaderData(1,Qt::Horizontal,"Nom");
    _typesModel->setHeaderData(2,Qt::Horizontal,"Consultation");
    _typesModel->setHeaderData(3,Qt::Horizontal,"Durée");

    for (int i = 0; i < typeList.size(); ++i) {
       QStandardItem * item =  new QStandardItem(typeList.at(i).getName().c_str());
       _typeItemsList.append(item);
    }
    rootNode->appendRows(_typeItemsList);

    for (int i = 0; i < staffList.size(); i++) {
        Staff staff = staffList.at(i);
        QList<Patient> patients = _patientConnector->getAll(staff.getId());
        staff.setPatientsConsult(patients);
        for (int j = 0; j < _typeItemsList.size(); ++j) {
            if (staffList.at(i).getTypeId() == typeList.at(j).getId()) {
                QList<QStandardItem*> items;
                items.append(new QStandardItem(staff.getFirstName().c_str()));
                items.append(new QStandardItem(staff.getLastName().c_str()));
                QList<Patient> consultations = staff.getPatientsConsult();
                QString dates = "", durations = "";
                for (int k = 0; k < consultations.size(); ++k) {
                    dates += ("- " + StringFormatter::toFrDate(consultations.at(k).getConsultationDate()) + (k+1 < consultations.size() ? "\n" : ""));
                    durations += ("- " + StringFormatter::toReadableDuration(consultations.at(k).getDuration()) + (k+1 < consultations.size() ? "\n" : ""));
                }
                items.append(new QStandardItem(dates));
                items.append(new QStandardItem(durations));

                _typeItemsList.at(j)->appendRow(items);
            }
        }
        // display satff
        staff.display();
    }
    ui->treeView->setModel(_typesModel);
    ui->treeView->setEditTriggers(QTreeView::NoEditTriggers);
    ui->treeView->setColumnWidth(0, 200);
    ui->treeView->setColumnWidth(1, 150);
    ui->treeView->setColumnWidth(2, 150);
    ui->treeView->expandAll();

    areStaffButtonsEnable(false);

    //selection changes shall trigger a slot
    QItemSelectionModel *selectionModel= ui->treeView->selectionModel();
    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
            this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
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
            //----------------------------------------------------------------
            for (int i = 0; i < accounts.size(); i++) {
                qDebug() << accounts[i].getLogin().c_str() << " " << accounts[i].getPassword().c_str() << "\n";
            }
            //-----------------------------------------------------------------
        }
        ui->statusBar->showMessage("Personnel ajouté");
    }
    else ui->statusBar->showMessage("Ajout de personnel annulé");

    // Recreate the tree on the window
    QListIterator<QStandardItem *> list(_typeItemsList);
    while (list.hasNext()) {
        QStandardItem * type = list.next();
        if (type->text().toStdString() == newStaff.getType()){
            QList<QStandardItem*> items;
            items.append(new QStandardItem(newStaff.getFirstName().c_str()));
            items.append(new QStandardItem(newStaff.getLastName().c_str()));
            type->appendRow(items);
        }
    }
}

void MainWindow::quit_clicked() {
    emit quit();
}

void MainWindow::addPatient() {
    PatientForm addPatientForm;

    // Execute the patient form ans wait for an acceted return
    if (addPatientForm.exec() == QDialog::Accepted) {
        Consult consult;

        // Get the patient created with the form and add it to the database.
        Patient newPatient = addPatientForm.getPatient();
        consult._idPatient = _patientConnector->insert(newPatient);

        _patientConnector->refreshModel();
        ui->patientsTableView->setModel(_patientsModel);

        // Get the affected ressource and add the to the database
        QList<Staff> ressources = addPatientForm.getAffectedStaff();

        for (int i = 0; i < ressources.size(); i++) {
            consult._idRessource = ressources[i].getId();
            _consultConnector->insert(consult);
        }
        ui->statusBar->showMessage("Patient ajouté");
    }
    else ui->statusBar->showMessage("Ajout de patient annulé");
}

void MainWindow::on_searchButton_clicked()
{
    qDebug() << ui->searchTextBox->text();
    _patientConnector->searchFilterModel(ui->searchTextBox->text());
    _patientConnector->searchDateFilterModel(ui->beginDateEdit->date(), ui->endDateEdit->date());

    arePatientButtonsEnable(false);

}

void MainWindow::on_editPatientButton_clicked()
{
    if (_patientClickedIndex != -1) {
        PatientForm addPatientForm;
        Patient patient(_patientsModel->record(_patientClickedIndex));
        addPatientForm.setPatient(&patient);

        // Execute the patient form ans wait for an acceted return
        if (addPatientForm.exec() == QDialog::Accepted) {
            Patient updatedPatient = addPatientForm.getPatient();
            _patientConnector->updateRecord(_patientClickedIndex, updatedPatient);

            // Update the consults
            QList<Consult> oldConsults = _consultConnector->getPatientConsult(updatedPatient.getId());
            QList<Staff> newAffectedStaff = addPatientForm.getAffectedStaff();

            QList<Consult> consultToAdd;
            QList<Consult> consultToDelete;

            // Find new consult
            for (int i = 0; i < newAffectedStaff.size(); i++) {
                bool found = false;

                for (int j = 0; j < oldConsults.size(); j++) {
                    // If the consult is in both old and new : nothing to change
                    if (oldConsults[j]._idRessource == newAffectedStaff[i].getId()) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    Consult consult;
                    consult._idPatient = updatedPatient.getId();
                    consult._idRessource = newAffectedStaff[i].getId();

                    consultToAdd << consult;
                }
            }

            // Find deleted consult
            for (int i = 0; i < oldConsults.size(); i++){
                bool found = false;

                for (int j = 0; j < newAffectedStaff.size(); j++) {
                    // If the consult is in both old and new : nothing to change
                    if (oldConsults[i]._idRessource == newAffectedStaff[j].getId()) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    consultToDelete << oldConsults[i];
                }
            }

            // Add
            for (int i = 0; i < consultToAdd.size(); i++) {
                _consultConnector->insert(consultToAdd[i]);
            }

            // DeleteS
            for (int i = 0; i < consultToDelete.size(); i++) {
                _consultConnector->suppr(consultToDelete[i]._id);
            }

            ui->statusBar->showMessage("Patient modifié");
        }
    }
}


void MainWindow::on_patientsTableView_pressed(const QModelIndex &index)
{
    arePatientButtonsEnable(true);
    if (index.isValid() && (_patientClickedIndex == -1 || _patientClickedIndex != index.row())) {
        _patientClickedIndex = index.row();
    }
}

void MainWindow::on_patientsTableView_doubleClicked(const QModelIndex &index)
{
    on_patientsTableView_pressed(index);
    on_editPatientButton_clicked();
}

void MainWindow::on_addPatientPushButton_clicked()
{
    addPatient();
}

void MainWindow::on_deletePatientButton_clicked()
{
    // Delete consult involving this patient
    QList<Consult> consultToDelete = _consultConnector->getPatientConsult(_patientsModel->record(_patientClickedIndex).value("Id").toInt());

    for (int i = 0; i < consultToDelete.size(); i++) {
        qDebug() << "delete : " << consultToDelete[i]._id << ", " << consultToDelete[i]._idPatient << ", " << consultToDelete[i]._idRessource;
        _consultConnector->suppr(consultToDelete[i]._id);
    }

    qDebug() << "remainning consult";

    QList<Consult> test = _consultConnector->getAll();
    for (int i = 0; i < test.size(); i++) {
        qDebug() << test[i]._id << ", " << test[i]._idPatient << ", " << test[i]._idRessource;
    }

    // delete the patient
    ui->patientsTableView->hideRow(_patientClickedIndex);
    ui->patientsTableView->setModel(_patientsModel);
    _patientConnector->deleteRecord(_patientClickedIndex);
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Attention", "Voulez-vous vraiment supprimer ce patient ?",QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        ui->patientsTableView->hideRow(_patientClickedIndex);
        ui->patientsTableView->setModel(_patientsModel);
        _patientConnector->deleteRecord(_patientClickedIndex);
        ui->statusBar->showMessage("Patient supprimé");
      }
}

void MainWindow::selectionChangedSlot(const QItemSelection &, const QItemSelection &)
{
    areStaffButtonsEnable(true);
}
