#ifndef CONSULTCONNECTOR_H
#define CONSULTCONNECTOR_H

#include <QSqlError>
#include "Connector.h"
#include "Consult.h"

class ConsultConnector : public Connector<Consult>
{
public:
    ~ConsultConnector();

    virtual inline QList<Consult> getAll(int id = 0);
    virtual inline Consult getOne(string value, string field);
    virtual inline int insert(Consult element);

    inline void suppr(int consultId);

    static ConsultConnector* getInstance();

    inline QList<Consult> getPatientConsult(int patientId);

protected:
    inline ConsultConnector();

    static ConsultConnector* _instance;
};


/**
 * @brief ConsultConnector default constructor.
 * works with table TConsult and the database DB.
 */
ConsultConnector::ConsultConnector() : Connector<Consult>("TConsult", "DB") { }


QList<Consult> ConsultConnector::getAll(int id) {
    // Initialize the result
    QList<Consult> result;

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
        Consult consult;

        consult._id = query.value(0).toInt();
        consult._idPatient = query.value(1).toInt();
        consult._idRessource = query.value(2).toInt();

        result << consult;
    }

    // Close database
    closeDatabase();
    return result;
}

Consult ConsultConnector::getOne(string value, string field) {
    Consult result;

    return result;
}

/**
 * @brief insert : insert a new element into the database.
 * @param element : the element to insert.
 * @return the element id in database if inserted, -1 otherwise.
 */
int ConsultConnector::insert(Consult element) {
    bool result = false;

    // Define the next id to use
    int nextId = getLastId() + 1;

    // Open the database
    if(!openDatabase()) return -1;

    // Create the query
    QSqlQuery query(_database);

    query.prepare("INSERT INTO " + getTable() + " (Id, IdPatient, IdRessource) "
                  "VALUES (:id, :idPatient, :idRessource)");
    query.bindValue(":id", nextId);
    query.bindValue(":idPatient", element._idPatient);
    query.bindValue(":idRessource", element._idRessource);
    result = query.exec();

    if (!result) {
        qDebug() << query.lastError() << "\n";
        return -1;
    }

    // Close database and return
    closeDatabase();
    return nextId;
}

void ConsultConnector::suppr(int consultId) {
    // Open the database
    if(!openDatabase()) return;

    // Create the query
    QSqlQuery query(_database);

    query.prepare("DELETE FROM " + getTable() + " WHERE Id=:id");
    query.bindValue(":id", consultId);
    bool queryResult = query.exec();

    if (!queryResult) {
        qDebug() << query.lastError() << "\n";
        return;
    }

    // Close database
    closeDatabase();
}

QList<Consult> ConsultConnector::getPatientConsult(int patientId) {
    // Initialize the result
    QList<Consult> result;

    // Open the database
    if(!openDatabase()) return result;

    // Create the query
    QSqlQuery query(_database);

    query.prepare("SELECT * FROM " + getTable() + " WHERE IdPatient=:id");
    query.bindValue(":id", patientId);
    bool queryResult = query.exec();

    if (!queryResult) {
        qDebug() << query.lastError() << "\n";
        return result;
    }

    // Get all result
    while (query.next()) {
        Consult consult;

        consult._id = query.value(0).toInt();
        consult._idPatient = query.value(1).toInt();
        consult._idRessource = query.value(2).toInt();

        result << consult;
    }

    // Close database
    closeDatabase();
    return result;
}

#endif // CONSULTCONNECTOR_H
