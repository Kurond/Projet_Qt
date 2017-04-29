#ifndef PATIENTCONNECTOR_H
#define PATIENTCONNECTOR_H

#include "Connector.h"
#include "Patient.h"

#include <QSqlQuery>


class PatientConnector : public Connector<Patient>
{
public:
    inline PatientConnector();

    virtual inline QList<Patient> selectAll();
    virtual inline QList<Patient> selectFromId();
    virtual inline bool insert(Patient element);
};



PatientConnector::PatientConnector() : Connector<Patient>("TPatient", "DB") {

}

QList<Patient> PatientConnector::selectAll() {
    // Initialize the result
    QList<Patient> result;

    // Get the database
    //QSqlDatabase database = getDatabase();

    // Open the database
    _database.open();
    if(!_database.isOpen())
    {
        //qDebug() << _database.lastError();
        qDebug() << "Impossible to open database\n";
    }

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable());
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    while (query.next()) {
        Patient patient;

        patient.setId(query.value(0).toInt());
        patient.setLastName(query.value(1).toString().toStdString());
        patient.setFirstName(query.value(2).toString().toStdString());
        patient.setAddress(query.value(3).toString().toStdString());
        patient.setCity(query.value(4).toString().toStdString());
        patient.setPostalCode(query.value(5).toInt());
        patient.setComment(query.value(6).toString().toStdString());
        patient.setPhone(query.value(7).toInt());
        patient.setConsultationDate(query.value(8).toString().toStdString());
        patient.setDuration(query.value(9).toInt());
        patient.setPriority(query.value(10).toInt());

        result << patient;
    }

    _database.close();

    return result;
}

QList<Patient> PatientConnector::selectFromId() {

}

bool PatientConnector::insert(Patient element) {

}

#endif // PATIENTCONNECTOR_H
