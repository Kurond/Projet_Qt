#include "addpatient.h"
#include "ui_addpatient.h"

AddPatient::AddPatient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatient)
{
    ui->setupUi(this);
}

AddPatient::~AddPatient()
{
    delete ui;
}
