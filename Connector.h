#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

using namespace std;


template<typename T>
class Connector<T>
{
public:
    Connector(QString table, QString databaseName);

    virtual QList<T> selectAll() = 0;
    virtual QList<T> selectFromId() = 0;
    virtual bool insert(T element) = 0;

protected:
    QString getTable() const;
    QString getDatabaseName() const;

    QSqlDatabase getDatabase();

private:
    QString _table;
    QString _databaseName;
};

#endif // DATABASE_H
