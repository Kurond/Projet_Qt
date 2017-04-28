#ifndef C_INIT_BD_H
#define C_INIT_BD_H

#include <QSqlDatabase>
#include <QStringList>

class c_init_bd
{
public:
    c_init_bd();

    static bool Creation_BD();
    static QStringList getAllTypes();
    //static QSqlDatabase _db;

private:

};

#endif // C_INIT_BD_H
