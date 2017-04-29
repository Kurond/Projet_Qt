#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddStaffForm.h"
#include "StaffConnector.h"
#include "c_init_bd.h"
#include <iostream>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit_clicked()));
    connect(ui->actionPatient,  SIGNAL(triggered()), this, SLOT(addPatient()));

    //c_init_bd::Creation_BD();
    //

    c_init_bd::Creation_BD();
<<<<<<< HEAD
    QStringList list = c_init_bd::getAllTypes();
    QStandardItem * rootNode = standardModel->invisibleRootItem();

    for (int i = 0; i < list.size(); ++i) {
       QStandardItem * item =  new QStandardItem(list.at(i));
       typesList.append(item);
=======

    StaffConnector connector;
    QList<Staff> list = connector.selectAll();

    qDebug() << "size: " << list.size();
    for (int i = 0; i < list.size(); i++) {
        qDebug() << QString(list[i].getFirstName().c_str());
    }
>>>>>>> cf3f68c3fa81f4d4cadc87afbb726562bc411129

    }
    // qtree view initialization
    standardModel = new QStandardItemModel;
    rootNode->appendRows(typesList);
    ui->treeView->setModel(standardModel);
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


    QListIterator<QStandardItem *> list(typesList);
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

        std::cout << newPatient.getFistName() << " " << newPatient.getLastName() << std::endl;
    }

}
