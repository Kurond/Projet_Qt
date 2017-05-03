#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>
#include <QDebug>

using namespace std;


template<typename T>
class Connector
{
public:
    inline Connector(QString table, QString databaseName);

    virtual inline QList<T> selectAll() = 0;
    virtual inline QList<T> selectFromId() = 0;
    virtual inline bool insert(T element) = 0;

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
