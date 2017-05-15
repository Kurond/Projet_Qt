#ifndef STRINGFORMATTER_H
#define STRINGFORMATTER_H

#include <iostream>
#include <string>
#include <QString>
#include <QDate>

class StringFormatter
{
public:
    static QString upperFirst(QString name);
    static QString toEnDate(QDate date);
    static QString toFrDate(std::string date);
};

#endif // STRINGFORMATTER_H
