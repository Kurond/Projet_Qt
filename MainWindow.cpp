#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddStaffForm.h"
#include "StaffConnector.h"
#include "PatientConnector.h"
#include "StaffTypeConnector.h"
#include "ConsultConnector.h"
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

    //c_init_bd::Creation_BD();
    StaffConnector::databaseCreation();
    StaffConnector _staffConnector;
    StaffTypeConnector _staffTypeConnector;

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
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addStaffPushButton_clicked()
{
    AddStaffForm healthCareStaff;
    Staff newStaff;

    if(healthCareStaff.exec()==QDialog::Accepted)
    {
        StaffConnector staffConnector;
        StaffTypeConnector typeConnector;

        newStaff = healthCareStaff.getStaff();

        StaffType type = typeConnector.getOne(newStaff.getType(),"Label");
        newStaff.setTypeId(type.getId());

        staffConnector.insert(newStaff);
    }

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

        QList<Consult> test = consultConnector.getAll();

        for (unsigned int i = 0; i < test.size(); i++) {
            qDebug() << test[i]._idPatient << ", " << test[i]._idRessource;
        }
    }

}
