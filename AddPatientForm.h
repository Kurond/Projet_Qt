#ifndef ADDPATIENT_H
#define ADDPATIENT_H

#include <QDialog>
#include "Patient.h"
#include "Staff.h"

namespace Ui {
class AddPatientForm;
}

class AddPatientForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatientForm(QWidget *parent = 0);
    ~AddPatientForm();
    string isFormValid();
    Patient getPatient();

private slots:
    void on_cancelButton_clicked();
    void on_addButton_clicked();
    void on_addRessourceButton_clicked();

private:
    Ui::AddPatientForm *ui;
    Patient _patient;
    QList<Staff> _affectedStaffs;
    QList<Staff> _availableStaffs;
    QDate _consultationDate;
};

#endif // ADDPATIENT_H
