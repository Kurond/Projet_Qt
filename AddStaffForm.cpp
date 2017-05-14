#include "AddStaffForm.h"
#include "ui_AddStaffForm.h"
#include "Staff.h"
#include "QMessageBox"

AddStaffForm::AddStaffForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStaffForm)
{
    ui->setupUi(this);

    _staffTypeConnector = StaffTypeConnector::getInstance();

    fillTypeCombobox();
    setVisibleConnexion(false);
}

AddStaffForm::~AddStaffForm()
{
    delete ui;
}

void AddStaffForm::on_addPushButton_clicked()
{
    string error = isFormValid();
    if (!error.empty()) {
        QMessageBox::warning(this, tr("Erreur"),
            tr(error.c_str()),
            QMessageBox::Ok,
            QMessageBox::Cancel);
    }
    else {
        _staff.setFirstName(ui->firstNameLineEdit->text().toStdString());
        _staff.setLastName(ui->lastNameLineEdit->text().toStdString());
        _staff.setType(ui->typeComboBox->currentText().toStdString());

        if (_staff.getType() == "Informaticien") {
            _staff.setLogin(ui->loginLineEdit->text().toStdString());
            _staff.setPassword(ui->passwordLineEdit->text().toStdString());
        }
        accept();
    }
}

void AddStaffForm::on_cancelPushButton_clicked()
{
    ui->firstNameLineEdit->setText("");
    ui->lastNameLineEdit->setText("");
    ui->passwordLineEdit->setText("");
    ui->loginLineEdit->setText("");
    ui->typeComboBox->setCurrentIndex(0);
    reject();
}

void AddStaffForm::displayAddStaff() {
    setVisible(true);
}

void AddStaffForm::on_typeComboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1 == "Informaticien") setVisibleConnexion(true);

    else setVisibleConnexion(false);
}

void AddStaffForm::setVisibleConnexion(bool isVisible) {
    ui->loginLineEdit->setVisible(isVisible);
    ui->passwordLineEdit->setVisible(isVisible);
    ui->loginLabel->setVisible(isVisible);
    ui->passwordLabel->setVisible(isVisible);
    ui->sepLine->setVisible(isVisible);
    ui->passwordConfLabel->setVisible(isVisible);
    ui->passwordConfLineEdit->setVisible(isVisible);
}

void AddStaffForm::fillTypeCombobox()
{
    QList<StaffType> types = _staffTypeConnector->getAll();
    QStringList typeItemsList;

    // Fill the type combo box in with the content of database
    for (int i = 0; i < types.size(); i++) {
        typeItemsList.append(types.at(i).getName().c_str());
    }

    ui->typeComboBox->addItems(typeItemsList);
    ui->typeComboBox->setCurrentIndex(0);
}

string AddStaffForm::isFormValid() const {
    if (ui->typeComboBox->currentText() != "Informaticien") {
        if (ui->firstNameLineEdit->text().isEmpty() || ui->lastNameLineEdit->text().isEmpty()) {
            return "tous les champs doivent être rempli";
        }
    }
    else {
        if (ui->loginLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty()) {
            return "tous les champs doivent être rempli";
        }
        if (ui->passwordLineEdit->text() != ui->passwordConfLineEdit->text()) {
            return "les mots de passe doivent être identiques";
        }
        if (!(ui->passwordLineEdit->text().length() > 5)) {
            return "le mot de passe doit comporter au moins 6 caractères";
        }
    }
    return "";
}

Staff AddStaffForm::getStaff() const {
    return _staff;
}
