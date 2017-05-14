#ifndef STAFFTYPECONNECTOR_H
#define STAFFTYPECONNECTOR_H

#include "StaffType.h"
#include "Connector.h"

#include <QDebug>
#include <QSqlQuery>

class StaffTypeConnector: public Connector<StaffType>
{
public:
       ~StaffTypeConnector();

    virtual inline QList<StaffType> getAll();
    virtual inline StaffType getOne(string value, string field);
    virtual inline int insert(StaffType element);

    static StaffTypeConnector* getInstance();

protected:
    inline StaffTypeConnector();
    virtual inline QList<StaffType> setResult(QSqlQuery query);

private:
    static StaffTypeConnector* _instance;
};

StaffTypeConnector::StaffTypeConnector() :  Connector<StaffType>("TType", "DB")
{}

QList<StaffType> StaffTypeConnector::getAll() {
    // Initialize the result
    QList<StaffType> result;

    // Open the database
    _database.open();
    if(!_database.isOpen()) {
        qDebug() << "Impossible to open database\n";
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
    result = setResult(query);

    _database.close();

    return result;
}

QList<StaffType> StaffTypeConnector::setResult(QSqlQuery query) {
     QList<StaffType> result;

    // Get all result
    while (query.next()) {
        StaffType staffType;

        staffType.setId(query.value(0).toInt());
        staffType.setName(query.value(1).toString().toStdString());

        result << staffType;
    }

    return result;
}


StaffType StaffTypeConnector::getOne(string value, string field) {
    StaffType result;

    // Open the database
    _database.open();
    if(!_database.isOpen())
    {
        //qDebug() << _database.lastError();
        qDebug() << "Impossible to open database\n";
    }

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable() + " WHERE " + field.c_str() + " = '" + value.c_str() + "'");
    if (!queryResult) {
        qDebug() << "Impossible to reaad database\n";
        return result;
    }

    // Get all result
    if (query.next()) {
        result.setId(query.value(0).toInt());
        result.setName(query.value(1).toString().toStdString());
    }

    _database.close();

    return result;
}


int StaffTypeConnector::insert(StaffType element) {
    return -1;
}

#endif // STAFFTYPECONNECTOR_H
