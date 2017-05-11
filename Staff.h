#ifndef STAFF_H
#define STAFF_H

#include <QObject>
#include <string>
#include <iostream>

using namespace std;

class Staff
{
public:
    Staff();
    Staff(const string &fistName, const string &_lastName, const int idType, const string &type);
    ~Staff();

    int getId() const;
    void setId(int id);
    const string &getFirstName() const;
    void setFirstName(const string &firstName);
    const string &getLastName() const;
    void setLastName(const string &lastName);
    int getTypeId() const;
    void setTypeId(int id);
    const string &getType() const;
    void setType(const string &type);
    const string &getLogin() const;
    void setLogin(const string &login);
    const string &getPassword() const;
    void setPassword(const string &password);

    void display();

private:
    int _id;
    string _firstName;
    string _lastName;
    string _type;
    int _idType;
    string _login;
    string _password;

signals:

public slots:
};

#endif // STAFF_H
