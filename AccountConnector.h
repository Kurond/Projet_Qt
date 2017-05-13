#ifndef ACCOUNTCONNECTOR_H
#define ACCOUNTCONNECTOR_H

#include "Account.h"
#include "Connector.h"
#include "QSqlError"

class AccountConnector : public Connector<Account>
{
public:
    inline AccountConnector();

    virtual inline QList<Account> getAll();
    virtual inline Account getOne(string value, string field);
    virtual inline int insert(Account element);
protected:
    virtual inline QList<Account> setResult(QSqlQuery query);

};

AccountConnector::AccountConnector() : Connector<Account>("TCompte", "DB")
{

}

QList<Account> AccountConnector::getAll()
{
    // Initialize the result
    QList<Account> result;

    // Open the database
//    _database.open();
//    if(!_database.isOpen()) {
//        qDebug() << "Impossible to open database\n";
//        return result;
//    }

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable());
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    while (query.next()) {
        Account account;

        account.setId(query.value(0).toInt());
        account.setStaffId(query.value(1).toInt());
        account.setLogin(query.value(2).toString().toStdString());
        account.setPassword(query.value(3).toString().toStdString());

        result << account;
    }

//    _database.close();

    return result;
}

Account AccountConnector::getOne(string value, string field)
{
    Account result;

    // Open the database
//    _database.open();
    if(!_database.isOpen())
    {
        //qDebug() << _database.lastError();
        qDebug() << "Impossible to open database\n";
    }

    // Create the query
    QSqlQuery query(_database);
    bool queryResult = query.exec("SELECT * FROM " + getTable() + " WHERE " + field.c_str() + " = '" + value.c_str() + "'");
    if (!queryResult) {
        qDebug() << "Impossible to read database\n";
        return result;
    }

    // Get all result
    if (query.next()) {
        result.setId(query.value(0).toInt());
        result.setStaffId(query.value(1).toInt());
        result.setLogin(query.value(2).toString().toStdString());
        result.setPassword(query.value(3).toString().toStdString());
    }

//    _database.close();

    return result;

}

/**
 * @brief insert : insert a new element into the database.
 * @param element : the element to insert.
 * @return the element id in database if inserted, -1 otherwise.
 */
int AccountConnector::insert(Account element)
{
    bool result = false;
    int nextId = getLastId() + 1;

    // Open the database
//    _database.open();
    if(!_database.isOpen()) {
        qDebug() << _database.lastError() << "\n";
        return -1;
    }

    // Create the query
    QSqlQuery query(_database);

    query.prepare("INSERT INTO " + getTable() + " (Id, IdRessource, Login, MdP) "
                  "VALUES (:id, :idStaff, :login, :password)");

    query.bindValue(":id", nextId);
    query.bindValue(":idStaff", element.getStaffId());
    query.bindValue(":login", element.getLogin().c_str());
    query.bindValue(":password", element.getPassword().c_str());
    result = query.exec();

    if (!result) {
        qDebug() << "error: " << query.lastError();
        return -1;
    }

    // Close database and return
//    _database.close();
    return nextId;
}

QList<Account> AccountConnector::setResult(QSqlQuery query)
{
    QList<Account> result;

    return result;
}



#endif // ACCOUNTCONNECTOR_H
