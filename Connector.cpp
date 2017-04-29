#include "Connector.h"

Connector::Connector(QString table, QString databaseName) {
    _table = table;
    _databaseName = databaseName;
}

QString Connector::getTable() const {
    return _table;
}

QString Connector::getDatabaseName() {
    return _databaseName;
}


QSqlDatabase Connector::getDatabase() {
    // Get the database
    QSqlDatabase database  = QSqlDatabase::database(getDatabaseName());

    // Check if database is valid
    if(database.isValid())
    {
        // Connection to database
        database.setHostName("localhost");
        database.setUserName("root");
        database.setPassword("password");
        database.setDatabaseName("base_tmp.sqli");
    } else {
        qDebug() << "database not valid";
    }

    return database;
}
