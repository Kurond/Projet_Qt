#ifndef STAFFCONNECTOR_H
#define STAFFCONNECTOR_H

#include "Connector.h"
#include "Staff.h"

#include <QSqlQuery>

class StaffConnector  : public Connector<Staff>
{
public:
    inline StaffConnector();

    virtual inline QList<Staff> getAll();
    virtual inline Staff getOne(string value, string field);
    virtual inline bool insert(Staff element);

    QList<Staff> inline getNonIt();

protected:
    virtual inline QList<Staff> setResult(QSqlQuery query);
};

StaffConnector::StaffConnector() : Connector<Staff>("TStaff", "DB")
{}

QList<Staff> StaffConnector::getAll() {
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
    if(!_database.isOpen())
    {
        //qDebug() << _database.lastError();
        qDebug() << "Impossible to open database\n";
    }

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable() + " NATURAL JOIN TType WHERE" + field.c_str() + " = '" + value.c_str() + "'");
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

bool StaffConnector::insert(Staff element) {
    bool result = false;
    int lastId = getLastId();

    cout << "last id: " << lastId << endl;
    element.display();

    // Open the database
//    _database.open();
//    if(!_database.isOpen())
//    {
//        //qDebug() << _database.lastError();
//        qDebug() << "Impossible to open database\n";
//    }

//    // Create the query
//    QSqlQuery query(_database);
//    result = query.exec("INSERT INTO TStaff VALUES (" + lastId + ",'" + element.getLastName() + "'," + element.getFirstName() + "'," + element.getTypeId() + ")");

    return result;
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
