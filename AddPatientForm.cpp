#include "AddPatientForm.h"
#include "ui_AddPatientForm.h"
#include<iostream>
#include <QMessageBox>

AddPatientForm::AddPatientForm(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::AddPatientForm)
{
    ui->setupUi(this);
}

AddPatientForm::~AddPatientForm()
{
    delete ui;
}

Patient AddPatientForm::getPatient() {
    return _patient;
}

string AddPatientForm::isFormValid() {
    string errors = "";

    // If the first name wasn't set
    if (ui->firstnameText->text().isEmpty()) {
        errors = errors.append("Le champs prenom ne peut pas être vide. \n");
    }
    else {
        _patient.set_fistName(ui->firstnameText->text().toStdString());
    }

    // If the last name wasn't set
    if (ui->lastnameText->text().isEmpty()) {
        errors = errors.append("Le champs nom ne peut pas être vide. \n");
    }
    else {
        _patient.set_lastName(ui->lastnameText->text().toStdString());
    }

    // If the adress wasn't set
    if (ui->addressText->text().isEmpty()) {
        errors = errors.append("Le champs adresse ne peut pas être vide. \n");
    }
    else {
        _patient.set_address(ui->addressText->text().toStdString());
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
            _patient.set_postalCode(postalcode);
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
            _patient.set_postalCode(phoneNumber);
        }
    }

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
