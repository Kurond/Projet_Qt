#ifndef PATIENTCONNECTOR_H
#define PATIENTCONNECTOR_H

#include "Connector.h"
#include "Patient.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>

using namespace std;

class PatientConnector : public Connector<Patient>
{
public:
    ~PatientConnector();


    virtual inline QList<Patient> getAll();
    virtual inline Patient getOne(string value, string field);
    virtual inline int insert(Patient element);
    inline void update(Patient element);

    static PatientConnector* getInstance();

    inline QSqlTableModel * getTableModel(QObject * window);
    inline void searchFilterModel(QString value);
    inline void refreshModel();

protected:
    inline PatientConnector();
    virtual inline QList<Patient> setResult(QSqlQuery query);

private:
    static PatientConnector* _instance;
    QSqlTableModel * _model;
};



/**
 * @brief PatientConnector default constructor.
 * works with table TPatient and the database DB.
 */
PatientConnector::PatientConnector() : Connector<Patient>("TPatient", "DB") { }

QList<Patient> PatientConnector::getAll() {
    // Initialize the result
    QList<Patient> result;

    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
        return result;
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

Patient PatientConnector::getOne(string value, string field) {
    Patient result;

    return result;
}

/**
 * @brief insert : insert a new element into the database.
 * @param element : the element to insert.
 * @return the element id in database if inserted, -1 otherwise.
 */
int PatientConnector::insert(Patient element) {
    bool result = false;
    int nextId = getLastId() + 1;

    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
        return -1;
    }

    // Create the query
    QSqlQuery query(_database);

    query.prepare("INSERT INTO " + getTable() + " (Id, Nom, Prenom, Adresse, Ville, CP, Commentaire, Tel, DateConsultation, DureeConsultation, Priorite) "
                  "VALUES (:id, :nom, :prenom, :adresse, :ville, :cp, :com, :tel, :dateconsult, :dureeconsult, :priorite)");
    query.bindValue(":id", nextId);
    query.bindValue(":nom", (QString)element.getLastName().c_str());
    query.bindValue(":prenom", (QString)element.getFirstName().c_str());
    query.bindValue(":address", (QString)element.getAddress().c_str());
    query.bindValue(":ville", (QString)element.getCity().c_str());
    query.bindValue(":cp", element.getPostalCode());
    query.bindValue(":com", (QString)element.getComment().c_str());
    query.bindValue(":tel", element.getPhone());
    query.bindValue(":dateconsult", (QString)element.getConsultationDate().c_str());
    query.bindValue(":dureeconsult", element.getDuration());
    query.bindValue(":priorite", element.getPriority());
    result = query.exec();

    if (!result) {
        qDebug() << query.lastError() << "\n";
        return -1;
    }
    _database.close();

    return nextId;
}


void PatientConnector::update(Patient element)
{
    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
    }

    // Create the query
    QSqlQuery query(_database);

    element.display();

    query.prepare("UPDATE " + getTable() + " SET Nom=:lastname, Prenom=:firstname, Adresse=:address, Ville=:city, CP=:postalCode, "
                  "Commentaire=:comment, Tel=:phone, DateConsultation=:dateconsult, DureeConsultation=:duration, Priorite=:priority WHERE Id=:id");
    query.bindValue(":id", element.getId());
    query.bindValue(":lastname", (QString)element.getLastName().c_str());
    query.bindValue(":firstname", (QString)element.getFirstName().c_str());
    query.bindValue(":address", (QString)element.getAddress().c_str());
    query.bindValue(":city", (QString)element.getCity().c_str());
    query.bindValue(":postalCode", element.getPostalCode());
    query.bindValue(":comment", (QString)element.getComment().c_str());
    query.bindValue(":phone", element.getPhone());
    query.bindValue(":dateconsult", (QString)element.getConsultationDate().c_str());
    query.bindValue(":duration", element.getDuration());
    query.bindValue(":priority", element.getPriority());
    bool result = query.exec();

    if (!result) {
        qDebug() << query.lastError() << "\n";
    }
    _database.close();
}

QSqlTableModel* PatientConnector::getTableModel(QObject * parent)
{
    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
        return NULL;
    }

    _model = new QSqlTableModel(parent, _database);
    _model->setTable(getTable());
    _model->setHeaderData(8, Qt::Horizontal, "Date");
    _model->select();

    _database.close();

    return _model;
}

void PatientConnector::searchFilterModel(QString value)
{
    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
    }
    _model->setFilter(QString("Nom LIKE '%%1%' OR Prenom LIKE '%%2%' OR Ville LIKE '%%3%'").arg(value).arg(value).arg(value));
    _database.close();
}

void PatientConnector::refreshModel()
{
    _database.open();
    _model->select();
    _database.close();
}

QList<Patient> PatientConnector::setResult(QSqlQuery query) {
    QList<Patient> result;

    return result;
}

#endif // PATIENTCONNECTOR_H
