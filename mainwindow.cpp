#include "addpatient.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit_clicked()));
    connect(ui->actionPatient, SIGNAL(triggered()), this, SLOT(addPatient()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addStaffPushButton_clicked()
{
    emit openAddStaff();
}

void MainWindow::quit_clicked() {
    emit quit();
}

void MainWindow::addPatient() {
    AddPatient addPatientForm;

    if (addPatientForm.exec() == QDialog::Accepted) {

    }
}
