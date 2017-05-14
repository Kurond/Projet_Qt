#ifndef STAFFCONNECTOR_H
#define STAFFCONNECTOR_H

#include "Connector.h"
#include "Staff.h"
#include "QSqlError"

#include <QSqlQuery>

class StaffConnector  : public Connector<Staff>
{
public:

    ~StaffConnector();

    virtual inline QList<Staff> getAll();
    virtual inline Staff getOne(string value, string field);
    virtual inline int insert(Staff element);

    QList<Staff> inline getNonIt();

    static StaffConnector* getInstance();

protected:
    inline StaffConnector();
    virtual inline QList<Staff> setResult(QSqlQuery query);

    static StaffConnector* _instance;
};



StaffConnector::StaffConnector() : Connector<Staff>("TStaff", "DB")
{

}


QList<Staff> StaffConnector::getAll() {
    // Initialize the result
    QList<Staff> result;

    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
        return result;
    }

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
        Staff staff;

        staff.setId(query.value(0).toInt());
        staff.setLastName(query.value(1).toString().toStdString());
        staff.setFirstName(query.value(2).toString().toStdString());
        staff.setTypeId(query.value(3).toInt());
        staff.setType(query.value(4).toString().toStdString());

        result << staff;
    }
    _database.close();

    return result;
}

Staff StaffConnector::getOne(string value, string field) {
    Staff result;

    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
        return result;
    }

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable() + " NATURAL JOIN TType WHERE " + field.c_str() + " = '" + value.c_str() + "'");
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    if (query.next()) {
        result.setId(query.value(0).toInt());
        result.setLastName(query.value(1).toString().toStdString());
        result.setFirstName(query.value(2).toString().toStdString());
        result.setTypeId(query.value(3).toInt());
        result.setType(query.value(4).toString().toStdString());
    }
    _database.close();

    return result;
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
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
        return -1;
    }

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
    _database.close();

    return nextId;
}

QList<Staff> StaffConnector::setResult(QSqlQuery query) {
    QList<Staff> result;

    while (query.next()) {
        Staff staff;

        staff.setId(query.value(0).toInt());
        staff.setLastName(query.value(1).toString().toStdString());
        staff.setFirstName(query.value(2).toString().toStdString());
        staff.setTypeId(query.value(3).toInt());
        staff.setType(query.value(4).toString().toStdString());

        result << staff;
    }

    return result;
}


QList<Staff> StaffConnector::getNonIt() {
    // Initialize the result
    QList<Staff> result;

    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
        return result;
    }

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable() + " NATURAL JOIN TType WHERE IdType != 7");

    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    result = setResult(query);

    _database.close();

    return result;
}


#endif // STAFFCONNECTOR_H
