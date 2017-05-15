#ifndef PATIENTCONNECTOR_H
#define PATIENTCONNECTOR_H

#include "Connector.h"
#include "Patient.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDate>

using namespace std;

class PatientConnector : public Connector<Patient>
{
public:
    ~PatientConnector();
    static PatientConnector* getInstance();

    virtual inline QList<Patient> getAll();
    virtual inline Patient getOne(string value, string field);
    virtual inline int insert(Patient element);

    inline QSqlTableModel * getTableModel(QObject * window);
    inline void searchFilterModel(QString value);
    inline void searchDateFilterModel(QDate begin, QDate end);
    inline void refreshModel();
    inline void updateRecord(int index, Patient updatePatient);
    inline void deleteRecord(int index);

protected:
    inline PatientConnector();

private:
    static PatientConnector* _instance;
    QSqlTableModel * _model;

    QDate _beginDateFilter, _endDateFilter;
    QString _searchFilter;

    inline void applyFilter();
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
    if(!openDatabase()) return result;

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
    closeDatabase();
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
    if(!openDatabase()) return -1;

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
    closeDatabase();
    return nextId;
}

QSqlTableModel* PatientConnector::getTableModel(QObject * parent)
{
    // Open the database
    openDatabase();

    _model = new QSqlTableModel(parent, _database);
    _model->setTable(getTable());
    _model->setHeaderData(8, Qt::Horizontal, "Date");
    _model->select();

    closeDatabase();
    return _model;
}

void PatientConnector::searchFilterModel(QString value)
{
    _searchFilter = value;
    applyFilter();
}

void PatientConnector::searchDateFilterModel(QDate begin, QDate end) {
    _beginDateFilter = begin;
    _endDateFilter = end;

   applyFilter();
}

void PatientConnector::refreshModel()
{
    // Open the database
    openDatabase();
    _model->select();
    closeDatabase();
}

void PatientConnector::updateRecord(int index, Patient patient)
{
    QSqlRecord record = _model->record(index);
    record.setValue("Nom", patient.getLastName().c_str());
    record.setValue("Prenom", QString(patient.getFirstName().c_str()));
    record.setValue("Adresse", QString(patient.getAddress().c_str()));
    record.setValue("Ville", QString(patient.getCity().c_str()));
    record.setValue("Commentaire", QString(patient.getComment().c_str()));
    record.setValue("DateConsultation", QString(patient.getConsultationDate().c_str()));
    record.setValue("Tel", patient.getPhone());
    record.setValue("CP", patient.getPostalCode());
    record.setValue("DureeConsultation", patient.getDuration());
    record.setValue("Priorite", patient.getPriority());
    openDatabase();
    _model->setRecord(index, record);
    closeDatabase();
}

void PatientConnector::deleteRecord(int index)
{
    openDatabase();
    _model->removeRow(index);

    qDebug() << _model->lastError();

    closeDatabase();
}

void PatientConnector::applyFilter() {
    // Open the database
    openDatabase();
    _model->setFilter(QString("Nom LIKE '%%1%' OR Prenom LIKE '%%2%' OR Ville LIKE '%%3%'").arg(_searchFilter).arg(_searchFilter).arg(_searchFilter));

    if (_beginDateFilter < _endDateFilter) {
        QString beginDate = QString(_beginDateFilter.day()) + "-" + QString(_beginDateFilter.month()) + "-" + QString(_beginDateFilter.year());
        QString endDate = QString(_endDateFilter.day()) + "-" + QString(_endDateFilter.month()) + "-" + QString(_endDateFilter.year());
        _model->setFilter(QString("DateConsultation < '%1' AND DateConsultation < '%2'").arg(endDate).arg(beginDate));
    }

    closeDatabase();
}


#endif // PATIENTCONNECTOR_H
