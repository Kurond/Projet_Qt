#include "AddPatientForm.h"
#include "ui_AddPatientForm.h"
#include "QList"
#include "Staff.h"
#include "StaffConnector.h"
#include<iostream>
#include <QMessageBox>
#include <QDate>

AddPatientForm::AddPatientForm(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::AddPatientForm)
{
    ui->setupUi(this);


    _staffConnector = StaffConnector::getInstance();

    // Fill combo box
    _availableStaffs = _staffConnector->getNonIt();
    for (int i = 0; i < _availableStaffs.size(); i++) {
        QString item = QString(_availableStaffs[i].getFirstName().c_str()) + " " + QString(_availableStaffs[i].getLastName().c_str());
        ui->ressourceBox->addItem(item);
    }
}

AddPatientForm::~AddPatientForm()
{
    delete ui;
}

Patient AddPatientForm::getPatient() {
    return _patient;
}

QList<Staff> AddPatientForm::getAffectedStaff() {
    return _affectedStaffs;
}

string AddPatientForm::isFormValid() {
    string errors = "";

    // If the first name wasn't set
    if (ui->firstnameText->text().isEmpty()) {
        errors = errors.append("Le champs prenom ne peut pas être vide. \n");
    }
    else {
        _patient.setFirstName(ui->firstnameText->text().toStdString());
    }

    // If the last name wasn't set
    if (ui->lastnameText->text().isEmpty()) {
        errors = errors.append("Le champs nom ne peut pas être vide. \n");
    }
    else {
        _patient.setLastName(ui->lastnameText->text().toStdString());
    }

    // If the adress wasn't set
    if (ui->addressText->text().isEmpty()) {
        errors = errors.append("Le champs adresse ne peut pas être vide. \n");
    }
    else {
        _patient.setAddress(ui->addressText->text().toStdString());
    }

    // If the date wasn't set
    if (!_affectedStaffs.isEmpty() && !ui->consultationText->text().isEmpty()) {
        QDate consultationDate = QDate::fromString(ui->consultationText->text(), "dd/MM/yyyy");

        // If date doesn't respect the format
        if (!consultationDate.isValid()) {
            errors = errors.append("Le champs date ne respecte pas le format. \n");
        }
        else {
            _patient.setConsultationDate(consultationDate.toString().toStdString());
        }
    }
    else if (!_affectedStaffs.isEmpty()){
        errors = errors.append("Le champs date ne peut pas être vide. \n");
    }

    // If the postal code wasn't set
    if (ui->postalCodeText->text().isEmpty()) {
        errors = errors.append("Le champs code postal ne peut pas être vide. \n");
    }
    else {
        int postalcode = ui->postalCodeText->text().toInt();

        // If the postal code wasn't a number
        if (postalcode == 0) {
            errors = errors.append("Le champs code postal doit être un nombre. \n");
        }
        else {
            _patient.setPostalCode(postalcode);
        }
    }

    // If the phone number wasn't set
    if (!ui->phoneText->text().isEmpty()) {
        int phoneNumber = ui->phoneText->text().toInt();

        // If the phone number wasn't a number
        if (phoneNumber == 0) {
            errors = errors.append("Le champs téléphone doit être un nombre. \n");
        }
        else {
            _patient.setPhone(phoneNumber);
        }
    }

    _patient.setDuration(ui->durationBox->currentText().toInt());

    return errors;
}

void AddPatientForm::on_cancelButton_clicked() {
    reject();
}

void AddPatientForm::on_addButton_clicked() {
    string accepted = isFormValid();

    if (accepted == "") {
        accept();
    }
    else {
        QMessageBox::warning(this, tr("Erreurs"),
            tr(accepted.c_str()),
            QMessageBox::Ok,
            QMessageBox::Cancel);
    }

}

void AddPatientForm::on_addRessourceButton_clicked()
{
    // Add the resource to the list
    _affectedStaffs << _availableStaffs[ui->ressourceBox->currentIndex()];

    // resize the table
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    ui->tableWidget->setColumnCount(2);

    // Creates new elements
    QTableWidgetItem* firstNameItem = new QTableWidgetItem();
    firstNameItem->setText(_affectedStaffs[ui->tableWidget->rowCount() - 1].getFirstName().c_str());

    QTableWidgetItem* lastNameItem = new QTableWidgetItem();
    lastNameItem->setText(_affectedStaffs[ui->tableWidget->rowCount() - 1].getLastName().c_str());

    // Add elements to the table
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, firstNameItem);
    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, lastNameItem);

    // Delete ressource from combo box
    _availableStaffs.removeAt(ui->ressourceBox->currentIndex());
    ui->ressourceBox->clear();

    for (int i = 0; i < _availableStaffs.size(); i++) {
        QString item = QString(_availableStaffs[i].getFirstName().c_str()) + " " + QString(_availableStaffs[i].getLastName().c_str());
        ui->ressourceBox->addItem(item);
    }
}
