#include "StringFormatter.h"


QString StringFormatter::upperFirst(QString name)
{
    //  only convert if the string is not empty
    if (!name.isEmpty())
    {
        name[0] = name[0].toUpper();
        for (int i = 1; i < name.size(); i++) {
            if (name[i] != ' ') name[i] = name[i].toLower();
            else if (i+1 < name.size()) {
                i++;
                name[i] = name[i].toUpper();
            }
        }
    }

    return name;
}

QString StringFormatter::toEnDate(QDate date)
{
    int month = date.month();
    int day = date.day();
    QString formattedDate = QString::number(date.year()) + "-" +
            (month < 10 ? "0"+QString::number(month) : QString::number(month)) + "-" +
            (day < 10 ? "0"+QString::number(day) : QString::number(day));
    return formattedDate;
}

QString StringFormatter::toFrDate(std::string date)
{
    std::string formattedDate = date.substr(8,2) + "/" +
            date.substr(5,2) + "/" +
            date.substr(0,4);

    return formattedDate.c_str();
}
