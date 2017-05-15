#ifndef ACCOUNTCONNECTOR_H
#define ACCOUNTCONNECTOR_H

#include "Account.h"
#include "Connector.h"
#include "QSqlError"

class AccountConnector : public Connector<Account>
{
public:
    ~AccountConnector();

    virtual inline QList<Account> getAll();
    virtual inline Account getOne(string value, string field);
    virtual inline int insert(Account element);

    static AccountConnector* getInstance();
protected:
    inline AccountConnector();

private:
    static AccountConnector* _instance;

};

AccountConnector::AccountConnector() : Connector<Account>("TCompte", "DB")
{

}

QList<Account> AccountConnector::getAll()
{
    // Initialize the result
    QList<Account> result;

    // Open the database
    if(!openDatabase()) return result;

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

    closeDatabase();

    return result;
}

Account AccountConnector::getOne(string value, string field)
{
    Account result;

    // Open the database
    if(!openDatabase()) return result;

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

    closeDatabase();

    return result;
}

/**
 * @brief insert : insert a new element into the database.
 * @param element : the element to insert.
 * @return the element id in database if inserted, -1 otherwise.
 */
int AccountConnector::insert(Account element)
{
    int nextId = getLastId() + 1;

    // Open the database
    if(!openDatabase()) return -1;

    // Create the query
    QSqlQuery query(_database);

    query.prepare("INSERT INTO " + getTable() + " (Id, IdRessource, Login, MdP) "
                  "VALUES (:id, :idStaff, :login, :password)");

    query.bindValue(":id", nextId);
    query.bindValue(":idStaff", element.getStaffId());
    query.bindValue(":login", element.getLogin().c_str());
    query.bindValue(":password", element.getPassword().c_str());
    bool queryRes = query.exec();

    if (!queryRes) {
        qDebug() << "error: " << query.lastError();
        return -1;
    }

    // Close database and return
    closeDatabase();
    return nextId;
}


#endif // ACCOUNTCONNECTOR_H
