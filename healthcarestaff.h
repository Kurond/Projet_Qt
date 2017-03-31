#ifndef HEALTHCARESTAFF_H
#define HEALTHCARESTAFF_H

#include <QDialog>

namespace Ui {
class HealthCareStaff;
}

class HealthCareStaff : public QDialog
{
    Q_OBJECT

public:
    explicit HealthCareStaff(QWidget *parent = 0);
    ~HealthCareStaff();

private slots:
    void on_addPushButton_clicked();

    void on_cancelPushButton_clicked();

    void on_typeComboBox_currentIndexChanged(const QString &arg1);

public slots:
    void displayAddStaff();

private:
    Ui::HealthCareStaff *ui;

    void setVisibleConnexion(bool);
};

#endif // HEALTHCARESTAFF_H
