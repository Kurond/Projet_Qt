#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "AddStaffForm.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit_clicked()));
    connect(ui->actionPatient,  SIGNAL(triggered()), this, SLOT(addPatient()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addStaffPushButton_clicked()
{
    emit openAddStaff();
    AddStaffForm healthCareStaff;
    if(healthCareStaff.exec()==QDialog::Accepted)
    {
        Staff newStaff = healthCareStaff.getStaff();
        cout << "FirstName: " << newStaff.getFirstName() << endl;
        cout << "LastName: " <<  newStaff.getLastName() << endl;
        cout << "Type: " <<  newStaff.getType() << endl;
        cout << "Login: " <<  newStaff.getLogin() << endl;
        cout << "Password: " <<  newStaff.getPassword() << endl;
    }
}

void MainWindow::quit_clicked() {
    emit quit();
}

void MainWindow::addPatient() {
    AddPatientForm addPatientForm;

    if (addPatientForm.exec() == QDialog::Accepted) {
        Patient newPatient = addPatientForm.getPatient();

        std::cout << newPatient.get_fistName() << " " << newPatient.get_lastName() << std::endl;
    }

}
