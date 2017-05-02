#ifndef STAFFTYPECONNECTOR_H
#define STAFFTYPECONNECTOR_H

#include "StaffType.h"
#include "Connector.h"

#include <QDebug>
#include <QSqlQuery>

class StaffTypeConnector: public Connector<StaffType>
{
public:
    inline StaffTypeConnector();

    virtual inline QList<StaffType> selectAll();
    virtual inline QList<StaffType> selectFromId();
    virtual inline bool insert(StaffType element);

protected:
    virtual inline QList<StaffType> setResult(QSqlQuery query);
};

StaffTypeConnector::StaffTypeConnector() :  Connector<StaffType>("TType", "DB")
{}

QList<StaffType> StaffTypeConnector::selectAll() {
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


QList<StaffType> StaffTypeConnector::selectFromId() {
    QList<StaffType> result;

    return result;
}

bool StaffTypeConnector::insert(StaffType element) {
    return false;
}

#endif // STAFFTYPECONNECTOR_H
