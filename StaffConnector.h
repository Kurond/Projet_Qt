#ifndef STAFFCONNECTOR_H
#define STAFFCONNECTOR_H

#include "Connector.h"
#include "Staff.h"
#include "QSqlError"

#include <QSqlQuery>
#include <QSqlTableModel>
#include <PatientConnector.h>

class StaffConnector  : public Connector<Staff>
{
public:
    ~StaffConnector();
    static StaffConnector* getInstance();

    virtual inline QList<Staff> getAll(int id = 0);
    virtual inline Staff getOne(string value, string field);
    virtual inline int insert(Staff element);

    QList<Staff> inline getNonIt();

    inline QSqlTableModel * getTableModel(QObject * window);

protected:
    inline StaffConnector();

    static StaffConnector* _instance;

private:
    QSqlTableModel * _model;
};



StaffConnector::StaffConnector() : Connector<Staff>("TStaff", "DB")
{

}


QList<Staff> StaffConnector::getAll(int id) {
    // Initialize the result
    QList<Staff> result;

    // Open the database
    if(!openDatabase()) return result;

    // Create the query
    QSqlQuery query(_database);

    bool queryResult = query.exec("SELECT * FROM " + getTable() + ", TType WHERE TType.Id = IdType");
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    // result = setResult(query);       ne marche pas je comprend pas... en attendant :

    while (query.next()) {
        Staff staff(&query);
        result << staff;
    }

    closeDatabase();
    return result;
}


Staff StaffConnector::getOne(string value, string field) {
    Staff result;

    // Open the database
    if(!openDatabase()) return result;

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable() + " NATURAL JOIN TType WHERE " + field.c_str() + " = '" + value.c_str() + "'");
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    if (query.next()) {
        Staff result(&query);
        closeDatabase();
        return result;
    }
    closeDatabase();
}

/**
 * @brief insert : insert a new element into the database.
 * @param element : the element to insert.
 * @return the element id in database if inserted, -1 otherwise.
 */
int StaffConnector::insert(Staff element) {
    bool result = false;
    int nextId = getLastId() + 1;

    // Open the database
    if(!openDatabase()) return result;

    // Create the query
    QSqlQuery query(_database);

    query.prepare("INSERT INTO " + getTable() + " (Id, Nom, Prenom, IdType) "
                  "VALUES (:id, :lastName, :firstName, :idType)");

    query.bindValue(":id", nextId);
    query.bindValue(":lastName", (QString)element.getLastName().c_str());
    query.bindValue(":firstName", (QString)element.getFirstName().c_str());
    query.bindValue(":idType", element.getTypeId());
    result = query.exec();

    if (!result) {
        qDebug() << query.lastError() << "\n";
        return -1;
    }

    closeDatabase();
    return nextId;
}


QList<Staff> StaffConnector::getNonIt() {
    // Initialize the result
    QList<Staff> result;

    // Open the database
    if(!openDatabase()) return result;

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable() + " NATURAL JOIN TType WHERE IdType != 7");

    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    while (query.next()) {
        Staff staff(&query);
        result << staff;
    }
    closeDatabase();
    return result;
}

QSqlTableModel *StaffConnector::getTableModel(QObject *parent)
{
    // Open the database
    openDatabase();

    _model = new QSqlTableModel(parent, _database);
    _model->setTable(getTable());
    _model->select();

    closeDatabase();
    return _model;

}

#endif // STAFFCONNECTOR_H
