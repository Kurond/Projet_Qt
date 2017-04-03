#ifndef STAFF_H
#define STAFF_H

#include <QObject>
#include <string>

using namespace std;

class Staff : public QObject
{
    Q_OBJECT
public:
    explicit Staff(QObject *parent = 0);

    const string &getFirstName() const;

    void setFirstName(const string &firstName);

    const string &getLastName() const;

    void setLastName(const string &lastName);

    const string &getType() const;

    void setType(const string &type);

    const string &getLogin() const;

    void setLogin(const string &login);

    const string &getPassword() const;

    void setPassword(const string &password);


private:
    string firstName;
    string lastName;
    string type;
    string login;
    string password;

signals:

public slots:
};

#endif // STAFF_H
