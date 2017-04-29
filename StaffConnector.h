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
};



StaffConnector::StaffConnector() :  Connector<Staff>("TStaff", "DB") {

}

QList<Staff> StaffConnector::selectAll() {
    // Initialize the result
    QList<Staff> result;

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
    bool queryResult = query.exec("SELECT * FROM " + getTable() + " NATURAL JOIN TType");
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    while (query.next()) {
        Staff staff;

        staff.setLastName(query.value(1).toString().toStdString());
        staff.setFirstName(query.value(2).toString().toStdString());
        staff.setType(query.value(4).toString().toStdString());

        //qDebug() << staff.getFirstName().c_str();

        result << staff;
    }

    _database.close();

    return result;
}






QList<Staff> StaffConnector::selectFromId() {

}

bool StaffConnector::insert(Staff element) {

}


#endif // STAFFCONNECTOR_H
