#ifndef ADDPATIENT_H
#define ADDPATIENT_H

#include <QDialog>
#include "Patient.h"
#include "Staff.h"
#include "Consult.h"

#include "PatientConnector.h"
#include "StaffConnector.h"

namespace Ui {
class PatientForm;
}

class PatientForm : public QDialog
{
    Q_OBJECT

public:
    explicit PatientForm(QWidget *parent = 0);
    ~PatientForm();
    string isFormValid();
    Patient getPatient();
    QList<Staff> getAffectedStaff();
    void setPatient(Patient * patient);

private slots:
    void on_cancelButton_clicked();
    void on_addButton_clicked();
    void on_addRessourceButton_clicked();

private:
    Ui::PatientForm *ui;
    Patient _patient;

    QList<Staff> _affectedStaffs;
    QList<Staff> _availableStaffs;

    StaffConnector* _staffConnector;
};

#endif // ADDPATIENT_H
