#ifndef ADDPATIENT_H
#define ADDPATIENT_H

#include <QDialog>
#include "Patient.h"

using namespace std;

namespace Ui {
class AddPatient;
}

class AddPatient : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatient(QWidget *parent = 0);
    ~AddPatient();
    string isFormValid();
    Patient getPatient();

private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddPatient *ui;
    Patient _patient;
};

#endif // ADDPATIENT_H
