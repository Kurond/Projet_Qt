#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

using namespace std;


template<typename T>
class Connector
{
public:
    inline Connector(QString table, QString databaseName);

    virtual inline QList<T> getAll() = 0;
    virtual inline T getOne(string value, string field) = 0;
    virtual inline bool insert(T element) = 0;
    virtual inline int getLastId();

protected:
    QString getTable() const;
    QString getDatabaseName() const;

    virtual inline QList<T> setResult(QSqlQuery query) = 0;

    void getDatabase();
    QSqlDatabase _database;

private:
    QString _table;
    QString _databaseName;
};



template<typename T>
Connector<T>::Connector(QString table, QString databaseName) {
    _table = table;
    _databaseName = databaseName;

    getDatabase();
}

template<typename T>
int Connector<T>::getLastId()
{
    int result = 0;

    // Open the database
    _database.open();
    if(!_database.isOpen())
    {
        //qDebug() << _database.lastError();
        qDebug() << "Impossible to open database\n";
    }

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT max(Id) FROM " + getTable());
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    if (query.next()) {
        result = query.value(0).toInt();
    }

    _database.close();

    return result;
}

template<typename T>
QString Connector<T>::getTable() const {
    return _table;
}

template<typename T>
QString Connector<T>::getDatabaseName() const {
    return _databaseName;
}


template<typename T>
void Connector<T>::getDatabase() {
    // Get the database
//    _database = QSqlDatabase::addDatabase("QSQLITE", "DB");
    _database  = QSqlDatabase::database(getDatabaseName());

    // Check if database is valid
    if(_database.isValid())
    {
        // Connection to database
        _database.setHostName("localhost");
        _database.setUserName("root");
        _database.setPassword("password");
        _database.setDatabaseName("base_tmp.sqli");
    } else {
        qDebug() << "database not valid";
    }

    //return _database;
}

#endif // DATABASE_H
