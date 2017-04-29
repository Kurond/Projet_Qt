#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddStaffForm.h"
#include "StaffConnector.h"
#include "StaffTypeConnector.h"
#include "c_init_bd.h"
#include <iostream>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _standardModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit_clicked()));
    connect(ui->actionPatient,  SIGNAL(triggered()), this, SLOT(addPatient()));

    c_init_bd::Creation_BD();
        StaffConnector staffConnector;
        StaffTypeConnector staffTypeConnector;

        QList<Staff> staffList = staffConnector.selectAll();
        QList<StaffType> typeList = staffTypeConnector.selectAll();

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
        newStaff = healthCareStaff.getStaff();
        cout << "FirstName: " << newStaff.getFirstName() << endl;
        cout << "LastName: " <<  newStaff.getLastName() << endl;
        cout << "Type: " <<  newStaff.getType() << endl;
        cout << "Login: " <<  newStaff.getLogin() << endl;
        cout << "Password: " <<  newStaff.getPassword() << endl;
    }


    QListIterator<QStandardItem *> list(_typeItemsList);
    while (list.hasNext()) {
        QStandardItem * type = list.next();
        if (type->text().toStdString() == newStaff.getType()){
            QStandardItem * newStaffItem =  new QStandardItem(QString(newStaff.getLastName().c_str()));
            type->appendRow(newStaffItem);
        }
    }
}

void MainWindow::quit_clicked() {
    emit quit();
}

void MainWindow::addPatient() {
    AddPatientForm addPatientForm;

    if (addPatientForm.exec() == QDialog::Accepted) {
        Patient newPatient = addPatientForm.getPatient();

        std::cout << newPatient.getFirstName() << " " << newPatient.getLastName() << std::endl;
    }

}
