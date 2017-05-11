#include "c_init_bd.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QSqlResult>

c_init_bd::c_init_bd() {
}

bool c_init_bd::Creation_BD()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "DB");

    if(db.isValid())
    {
        db.setHostName("localhost");
        db.setUserName("root");
        db.setPassword("password");

        db.setDatabaseName("base_tmp.sqli");
        return true;

    }
    else
    {
        qDebug() << db.lastError().text();
        qDebug() << "Erreur à création de la base !\n";
        return false;
    }
}
