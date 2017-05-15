#include "PatientForm.h"
#include "ui_AddPatientForm.h"
#include "QList"
#include "Staff.h"
#include "StaffConnector.h"
#include<iostream>
#include <QMessageBox>
#include <QDate>

PatientForm::PatientForm(QWidget * parent) :
    QDialog(parent),
    ui(new Ui::PatientForm)
{
    ui->setupUi(this);
    setWindowTitle("Ajout d'un patient");

    _staffConnector = StaffConnector::getInstance();

    // Fill staff combo box
    _availableStaffs = _staffConnector->getNonIt();
    for (int i = 0; i < _availableStaffs.size(); i++) {
        QString item = QString(_availableStaffs[i].getFirstName().c_str()) + " " + QString(_availableStaffs[i].getLastName().c_str());
        ui->ressourceComboBox->addItem(item);
    }
    ui->hoursDurationComboBox->setCurrentIndex(1);
    ui->minsDurationComboBox->setCurrentIndex(0);
}

PatientForm::~PatientForm()
{
    delete ui;
}

Patient PatientForm::getPatient() {
    return _patient;
}

QList<Staff> PatientForm::getAffectedStaff() {
    return _affectedStaffs;
}

void PatientForm::setPatient(Patient * patient)
{
    setWindowTitle("Modification d'un patient");

    ui->firstnameLineEdit->setText(patient->getFirstName().c_str());
    ui->lastnameLineEdit->setText(patient->getLastName().c_str());
    ui->commentTextEdit->setText(patient->getComment().c_str());
    ui->addressLineEdit->setText(patient->getAddress().c_str());
    ui->cityLineEdit->setText(patient->getCity().c_str());
    ui->postalCodeLineEdit->setText(QString::number(patient->getPostalCode()));
    ui->phoneLineEdit->setText(QString::number(patient->getPhone()));
    ui->priorityComboBox->setCurrentIndex(patient->getPriority()-1);

    // format & display date
    string formattedDate = patient->getConsultationDate().substr(8,2) + "/" +
            patient->getConsultationDate().substr(5,2) + "/" +
            patient->getConsultationDate().substr(0,4);
    ui->consultationDateLineEdit->setText(formattedDate.c_str());

    // format & display duration
    int hours = patient->getDuration()/60;
    int mins = hours != 0 ? patient->getDuration()%(hours*60) : patient->getDuration();
    ui->hoursDurationComboBox->setCurrentIndex(hours);
    for (int i = 0; i < 12; i++) {
        if (ui->minsDurationComboBox->itemText(i) == to_string(mins).c_str())
            ui->minsDurationComboBox->setCurrentIndex(i);
    }
}

string PatientForm::isFormValid() {
    string errors = "";

    // If the first name wasn't set
    if (ui->firstnameLineEdit->text().isEmpty()) {
        errors = errors.append("Le champs prenom ne peut pas être vide. \n");
    }
    else {
        _patient.setFirstName(ui->firstnameLineEdit->text().toStdString());
    }

    // If the last name wasn't set
    if (ui->lastnameLineEdit->text().isEmpty()) {
        errors = errors.append("Le champs nom ne peut pas être vide. \n");
    }
    else {
        _patient.setLastName(ui->lastnameLineEdit->text().toStdString());
    }

    // If the city wasn't set
    if (ui->cityLineEdit->text().isEmpty()) {
        errors = errors.append("Le champs ville ne peut pas être vide. \n");
    }
    else {
        _patient.setCity(ui->cityLineEdit->text().toStdString());
    }

    // If the adress wasn't set
    if (ui->addressLineEdit->text().isEmpty()) {
        errors = errors.append("Le champs adresse ne peut pas être vide. \n");
    }
    else {
        _patient.setAddress(ui->addressLineEdit->text().toStdString());
    }

    // If the date wasn't set
    if (!ui->consultationDateLineEdit->text().isEmpty()) {
        QDate consultationDate = QDate::fromString(ui->consultationDateLineEdit->text(), "dd/MM/yyyy");

        // If date doesn't respect the format
        if (!consultationDate.isValid()) {
            errors = errors.append("Le champs date ne respecte pas le format. \n");
        }
        else {
            int month = consultationDate.month();
            int day = consultationDate.day();
            QString formattedDate = QString::number(consultationDate.year()) + "-" +
                    (month < 10 ? "0"+QString::number(month) : QString::number(month)) + "-" +
                    (day < 10 ? "0"+QString::number(day) : QString::number(day));

            qDebug() << formattedDate;
            _patient.setConsultationDate(formattedDate.toStdString());
        }
    }
    else if (!_affectedStaffs.isEmpty()){
        errors = errors.append("Le champs date ne peut pas être vide. \n");
    }

    // If the postal code wasn't set
    if (ui->postalCodeLineEdit->text().isEmpty()) {
        errors = errors.append("Le champs code postal ne peut pas être vide. \n");
    }
    else {
        int postalcode = ui->postalCodeLineEdit->text().toInt();

        // If the postal code wasn't a number
        if (postalcode == 0) {
            errors = errors.append("Le champs code postal doit être un nombre. \n");
        }
        else {
            _patient.setPostalCode(postalcode);
        }
    }

    // If the phone number wasn't set
    if (!ui->phoneLineEdit->text().isEmpty()) {
        int phoneNumber = ui->phoneLineEdit->text().toInt();

        // If the phone number wasn't a number
        if (phoneNumber == 0) {
            errors = errors.append("Le champs téléphone doit être un nombre. \n");
        }
        else {
            _patient.setPhone(phoneNumber);
        }
    }

    // Save the comment
    _patient.setComment(ui->commentTextEdit->toPlainText().toStdString());
    // Save the priority
    _patient.setPriority(ui->priorityComboBox->currentText().toInt());
    // Save the duration
    _patient.setDuration(ui->hoursDurationComboBox->currentText().toInt()*60+ui->minsDurationComboBox->currentText().toInt());

    return errors;
}

void PatientForm::on_cancelButton_clicked() {
    reject();
}

void PatientForm::on_addButton_clicked() {
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

void PatientForm::on_addRessourceButton_clicked()
{
    // Add the resource to the list
    _affectedStaffs << _availableStaffs[ui->ressourceComboBox->currentIndex()];

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
    _availableStaffs.removeAt(ui->ressourceComboBox->currentIndex());
    ui->ressourceComboBox->clear();

    for (int i = 0; i < _availableStaffs.size(); i++) {
        QString item = QString(_availableStaffs[i].getFirstName().c_str()) + " " + QString(_availableStaffs[i].getLastName().c_str());
        ui->ressourceComboBox->addItem(item);
    }
}
