#include "healthcarestaff.h"
#include "ui_healthcarestaff.h"

HealthCareStaff::HealthCareStaff(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HealthCareStaff)
{
    ui->setupUi(this);
    QStringList typeItemsList;
    typeItemsList.append("Medecin A");
    typeItemsList.append("Médecin B");
    typeItemsList.append("Radiologue");
    typeItemsList.append("Informaticien");
    ui->typeComboBox->addItems(typeItemsList);

    setVisibleConnexion(false);
}

HealthCareStaff::~HealthCareStaff()
{
    delete ui;
}

void HealthCareStaff::on_addPushButton_clicked()
{

}

void HealthCareStaff::on_cancelPushButton_clicked()
{

}

void HealthCareStaff::displayAddStaff() {
    setVisible(true);
}

void HealthCareStaff::on_typeComboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Informaticien") setVisibleConnexion(true);

    else setVisibleConnexion(false);
}

void HealthCareStaff::setVisibleConnexion(bool isVisible) {
    ui->loginLineEdit->setVisible(isVisible);
    ui->passwordLineEdit->setVisible(isVisible);
    ui->loginLabel->setVisible(isVisible);
    ui->passwordLabel->setVisible(isVisible);
    ui->sepLine->setVisible(isVisible);
}
