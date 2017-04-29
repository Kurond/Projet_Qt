#include "StaffConnector.h"



StaffConnector::StaffConnector() : Connector<Staff>("TStaff", "DB") {

}

QList<Staff> StaffConnector::selectAll() {
    // Initialize the result
    QList<T> result;

    // Get the database
    QSqlDatabase database = getDatabase();

    // Open the database
    database.open();
    if(!database.isOpen())
    {
        qDebug() << db.lastError().text();
        qDebug() << "Impossible to open database\n";
    }

    // Create the query
    QSqlQuery query(db);
    bool queryResult = query.exec("SELECT * FROM " + _table + " NATURAL JOIN TType");
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    while (query.next()) {
        Staff staff;

        staff.setName(query.value(1).toString());
        staff.setFirstName(query.value(2).toString());
        staff.setType(query.value(4).toString());

        result << staff;
        qDebug() << query.value(4).toString() << "\n";
    }

    db.close();

    return result;
}

QList<Staff> StaffConnector::selectFromId() {

}

bool StaffConnector::insert(Staff element) {

}
