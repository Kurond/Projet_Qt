#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddStaffForm.h"
#include "c_init_bd.h"
#include <iostream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit_clicked()));
    connect(ui->actionPatient,  SIGNAL(triggered()), this, SLOT(addPatient()));

    c_init_bd::Creation_BD();
    QStringList list = c_init_bd::getAllTypes();

    while (list.hasNext()) {
      QStandardItem * item =  new QStandardItem(list.next());

    }
    // qtree view initialization
    standardModel = new QStandardItemModel;


    QStandardItem * rootNode = standardModel->invisibleRootItem();
    QStandardItem * doctorA =  new QStandardItem("Medecin A");
    QStandardItem * doctorB =  new QStandardItem("Medecin B");
    typesList.append(doctorA);
    typesList.append(doctorB);
    rootNode->appendRows(typesList);

    ui->treeView->setModel(standardModel);
    ui->treeView->expandAll();

    c_init_bd::Creation_BD();
    QStringList list = c_init_bd::getAllTypes();
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
