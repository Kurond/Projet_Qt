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
};

StaffTypeConnector::StaffTypeConnector() :  Connector<StaffType>("TType", "DB")
{}

QList<StaffType> StaffTypeConnector::selectAll() {
    // Initialize the result
    QList<StaffType> result;

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
        StaffType staffType;

        staffType.setId(query.value(0).toInt());
        staffType.setName(query.value(1).toString().toStdString());

        qDebug() << query.value(0).toString();
        qDebug() << query.value(1).toString();

        result << staffType;
    }

    _database.close();

    return result;
}


QList<StaffType> StaffTypeConnector::selectFromId() {

}

bool StaffTypeConnector::insert(StaffType element) {

}

#endif // STAFFTYPECONNECTOR_H
