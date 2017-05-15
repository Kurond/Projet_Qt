#include "Staff.h"

Staff::Staff() :_id(0), _firstName(""), _lastName(""), _type(""), _idType(0), _login(""), _password("")
{
}

Staff::Staff(QSqlQuery *query) :
    _id(query->value(0).toInt()),
    _lastName(query->value(1).toString().toStdString()),
    _firstName(query->value(2).toString().toStdString()),
    _idType(query->value(3).toInt())
{
    if (query->size() > 4) setType(query->value(4).toString().toStdString());
}

Staff::Staff(const string &firstName, const string &lastName, const int idType, const string &type) :
  _firstName(firstName), _lastName(lastName), _type(type), _idType(idType)
{
}

Staff::~Staff()
{
}

int Staff::getId() const
{
    return _id;
}

void Staff::setId(int id)
{
    Staff::_id = id;
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

int Staff::getTypeId() const
{
    return _idType;
}

void Staff::setTypeId(int id)
{
    Staff::_idType = id;
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

void Staff::display()
{
    cout << "Staff { " << endl;
    cout << "\tId: " << getId() << endl;
    cout << "\tFirstName: " << getFirstName() << endl;
    cout << "\tLastName: " <<  getLastName() << endl;
    cout << "\tType: " <<  getType() << endl;
    cout << "\tidType: " <<  getTypeId() << endl;
    cout << "\tLogin: " <<  getLogin() << endl;
    cout << "\tPassword: " <<  getPassword() << endl;
    cout << "\tconsultSize: " <<  _patientsConsult.size() << endl;
    for (int i = 0; i < _patientsConsult.size(); i++) {
        Patient patient = _patientsConsult.at(i);
        patient.display();
    }
    cout << "}" << endl;
}

QList<Patient> Staff::getPatientsConsult() const
{
    return _patientsConsult;
}

void Staff::setPatientsConsult(const QList<Patient> &patientsConsult)
{
    _patientsConsult = patientsConsult;
}

ostream& operator<<(ostream& os, const Staff& staff)
{
    os << "staff: {: " << endl;
    os << "\tfirst name: " << staff.getFirstName() << endl;
    os << "\tlast name: " << staff.getLastName() << endl;
    os << "\ttype: " << staff.getType() << endl;
    os << "\ttype id: " << staff.getTypeId() << endl;
    os << "}: " << endl;

    return os;
}
