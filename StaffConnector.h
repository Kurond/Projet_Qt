#ifndef STAFFCONNECTOR_H
#define STAFFCONNECTOR_H

#include "Connector.h"
#include "Staff.h"

#include <QSqlQuery>

class StaffConnector  : public Connector<Staff>
{
public:
    inline StaffConnector();

    virtual inline QList<Staff> selectAll();
    virtual inline QList<Staff> selectFromId();
    virtual inline bool insert(Staff element);

    QList<Staff> inline getNonIt();

protected:
    virtual inline QList<Staff> setResult(QSqlQuery query);
};

StaffConnector::StaffConnector() : Connector<Staff>("TStaff", "DB")
{}

QList<Staff> StaffConnector::selectAll() {
    // Initialize the result
    QList<Staff> result;

    // Open the database
    _database.open();
    if(!_database.isOpen())
    {
        //qDebug() << _database.lastError();
        qDebug() << "Impossible to open database\n";
    }

    // Create the query
    QSqlQuery query(_database);

    bool queryResult = query.exec("SELECT * FROM " + getTable() + " NATURAL JOIN TType");
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    result = setResult(query);

    _database.close();

    return result;
}

QList<Staff> StaffConnector::selectFromId() {
    QList<Staff> result;

    return result;
}

bool StaffConnector::insert(Staff element) {
    return false;
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

    if(!_database.isOpen())
    {
        qDebug() << "Impossible to open database\n";
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
