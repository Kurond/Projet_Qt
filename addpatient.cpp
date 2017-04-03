#include "addpatient.h"
#include "ui_addpatient.h"

#include <QMessageBox>

AddPatient::AddPatient(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::AddPatient)
{
    ui->setupUi(this);
}

AddPatient::~AddPatient()
{
    delete ui;
}

string AddPatient::isFormValid() {
    string errors = "";

    if (ui->firstnameText->text().isEmpty()) {
        errors = errors.append("Le champs prenom ne pas être vide. \n");
    }

    if (ui->lastnameText->text().isEmpty()) {
        errors = errors.append("Le champs nom ne pas être vide. \n");
    }

    if (ui->addressText->text().isEmpty()) {
        errors = errors.append("Le champs adresse ne pas être vide. \n");
    }

    if (ui->postalCodeText->text().toInt() > 0) {
        errors = errors.append("Le champs code postal ne pas être vide. \n");
    }

    if (ui->phoneText->text().toInt() > 0) {
        errors = errors.append("Le champs téléphone ne pas être vide. \n");
    }

    return errors;
}

void AddPatient::on_cancelButton_clicked() {
    reject();
}

void AddPatient::on_addButton_clicked() {
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
