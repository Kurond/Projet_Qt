#include "Staff.h"

Staff::Staff() : firstName(""), lastName(""), type(""), login(""), password("")
{
}

Staff::~Staff()
{

}

const string &Staff::getFirstName() const {
  return firstName;
}

void Staff::setFirstName(const string &firstName) {
  Staff::firstName = firstName;
}

const string &Staff::getLastName() const {
  return lastName;
}

void Staff::setLastName(const string &lastName) {
  Staff::lastName = lastName;
}

const string &Staff::getType() const {
  return type;
}

void Staff::setType(const string &type) {
  Staff::type = type;
}

const string &Staff::getLogin() const {
  return login;
}

void Staff::setLogin(const string &login) {
  Staff::login = login;
}

const string &Staff::getPassword() const {
  return password;
}

void Staff::setPassword(const string &password) {
  Staff::password = password;
}
