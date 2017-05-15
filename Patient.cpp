//
// Created by Flwrnt on 24/03/2017.
// Copyright (c) 2017 ___FULLUSERNAME___. All rights reserved.
//

#include "Patient.h"

Patient::Patient() : _id(0), _firstName(""),
    _lastName(""),
    _address(""),
    _city(""),
    _comment(""),
    _phone(0),
    _postalCode(0),
    _duration(0),
    _priority(0) {

}

Patient::Patient(const string &fistName, const string &lastName, const string &address, const string &city,
                  const string &comment, int phone, int postalCode, int duration, int priority)
  : _id(0),
    _firstName(fistName),
    _lastName(lastName),
    _address(address),
    _city(city),
    _comment(comment),
    _phone(phone),
    _postalCode(postalCode),
    _duration(duration),
    _priority(priority) {

}

Patient::Patient(QSqlRecord record)
    : _id(record.value("Id").toInt()),
      _firstName(record.value("Prenom").toString().toStdString()),
      _lastName(record.value("Nom").toString().toStdString()),
      _address(record.value("Adresse").toString().toStdString()),
      _city(record.value("Ville").toString().toStdString()),
      _comment(record.value("Commentaire").toString().toStdString()),
      _consultationDate(record.value("DateConsultation").toString().toStdString()),
      _phone(record.value("Tel").toInt()),
      _postalCode(record.value("CP").toInt()),
      _duration(record.value("DureeConsultation").toInt()),
      _priority(record.value("Priorite").toInt())
{

}

int Patient::getId() const {
    return _id;
}

void Patient::setId(int id) {
    _id = id;
}

const string &Patient::getFirstName() const {
  return _firstName;
}

void Patient::setFirstName(const string &fistName) {
  Patient::_firstName = fistName;
}

const string &Patient::getLastName() const {
  return _lastName;
}

void Patient::setLastName(const string &lastName) {
  Patient::_lastName = lastName;
}

const string &Patient::getAddress() const {
  return _address;
}

void Patient::setAddress(const string &address) {
  Patient::_address = address;
}

const string &Patient::getCity() const {
  return _city;
}

void Patient::setCity(const string &city) {
  Patient::_city = city;
}

const string &Patient::getComment() const {
  return _comment;
}

void Patient::setComment(const string &comment) {
  Patient::_comment = comment;
}

int Patient::getPhone() const {
  return _phone;
}

void Patient::setPhone(int phone) {
  Patient::_phone = phone;
}

int Patient::getPostalCode() const {
  return _postalCode;
}

void Patient::setPostalCode(int postalCode) {
  Patient::_postalCode = postalCode;
}

int Patient::getDuration() const {
  return _duration;
}

void Patient::setDuration(int duration) {
  Patient::_duration = duration;
}

int Patient::getPriority() const {
  return _priority;
}

void Patient::setPriority(int priority) {
  Patient::_priority = priority;
}

const string &Patient::getConsultationDate() const {
   return _consultationDate;
}

void Patient::setConsultationDate(const string &consultationDate) {
    _consultationDate = consultationDate;
}

void Patient::display()
{
    cout << "Patient { " << endl;
    cout << "\tFirstName: " << getFirstName() << endl;
    cout << "\tLastName: " <<  getLastName() << endl;
    cout << "\tAddress: " <<  getAddress() << endl;
    cout << "\tCity: " <<  getCity() << endl;
    cout << "\tPhone: " <<  getPhone() << endl;
    cout << "\tDate consult: " <<  getConsultationDate() << endl;
    cout << "}" << endl;
}
