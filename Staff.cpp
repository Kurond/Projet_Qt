#include "Staff.h"

Staff::Staff() :_id(0), _firstName(""), _lastName(""), type(""), login(""), password("")
{
}

Staff::Staff(const string &fistName, const string &lastName, const string &type) :
  _firstName(_firstName), _lastName(lastName), type(type)
{
}

Staff::~Staff()
{
}

int Staff::getId() const
{
    return _id;
}

const string &Staff::getFirstName() const {
  return _firstName;
}

void Staff::setFirstName(const string &firstName) {
  Staff::_firstName = firstName;
}

const string &Staff::getLastName() const {
  return _lastName;
}

void Staff::setLastName(const string &lastName) {
  Staff::_lastName = lastName;
}

const string &Staff::getType() const {
  return _type;
}

void Staff::setType(const string &type) {
  Staff::_type = type;
}

const string &Staff::getLogin() const {
  return _login;
}

void Staff::setLogin(const string &login) {
  Staff::_login = login;
}

const string &Staff::getPassword() const {
  return _password;
}

void Staff::setPassword(const string &password) {
  Staff::_password = password;
}
