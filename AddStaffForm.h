#ifndef HEALTHCARESTAFF_H
#define HEALTHCARESTAFF_H

#include <QDialog>
#include "Staff.h"

namespace Ui {
class AddStaffForm;
}

class AddStaffForm : public QDialog
{
    Q_OBJECT

public:
    explicit AddStaffForm(QWidget *parent = 0);
    ~AddStaffForm();
    Staff getStaff() const;
    string isFormValid() const;

private slots:
    void on_addPushButton_clicked();

    void on_cancelPushButton_clicked();

    void on_typeComboBox_currentIndexChanged(const QString &arg1);

public slots:
    void displayAddStaff();

private:
    Ui::AddStaffForm *ui;
    void setVisibleConnexion(bool);
    Staff _staff;
};

#endif // HEALTHCARESTAFF_H
