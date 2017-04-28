//
// Created by Flwrnt on 24/03/2017.
// Copyright (c) 2017 ___FULLUSERNAME___. All rights reserved.
//

#include "Patient.h"

Patient::Patient() : _firstName(""),
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
  : _firstName(fistName),
    _lastName(lastName),
    _address(address),
    _city(city),
    _comment(comment),
    _phone(phone),
    _postalCode(postalCode),
    _duration(duration),
    _priority(priority) {

}

const string &Patient::getFistName() const {
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

