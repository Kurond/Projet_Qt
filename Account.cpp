#include "Account.h"

Account::Account() : _id(0), _idStaff(0), _login(""), _password("")
{

}

int Account::getId() const
{
    return _id;
}

void Account::setId(int id)
{
    _id = id;
}

int Account::getStaffId() const
{
    return _idStaff;
}

void Account::setStaffId(int id)
{
    _idStaff = id;
}

void Account::setLogin(const string &login)
{
    _login = login;
}

const string &Account::getLogin() const
{
    return _login;
}

void Account::setPassword(const string &password)
{
    _password = password;
}

const string &Account::getPassword() const
{
    return _password;
}

