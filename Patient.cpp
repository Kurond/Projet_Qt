//
// Created by Flwrnt on 24/03/2017.
// Copyright (c) 2017 ___FULLUSERNAME___. All rights reserved.
//

#include "Patient.h"

Patient::Patient(const string &_fistName, const string &_lastName, const string &_address, const string &_city,
                  const string &_comment, int _phone, int _postalCode, int _duration, int _priority)
  : _fistName(_fistName),
    _lastName(_lastName),
    _address(_address),
    _city(_city),
    _comment(_comment),
    _phone(_phone),
    _postalCode(_postalCode),
    _duration(_duration),
    _priority(_priority) {

}

const string &Patient::get_fistName() const {
  return _fistName;
}

void Patient::set_fistName(const string &_fistName) {
  Patient::_fistName = _fistName;
}

const string &Patient::get_lastName() const {
  return _lastName;
}

void Patient::set_lastName(const string &_lastName) {
  Patient::_lastName = _lastName;
}

const string &Patient::get_address() const {
  return _address;
}

void Patient::set_address(const string &_address) {
  Patient::_address = _address;
}

const string &Patient::get_city() const {
  return _city;
}

void Patient::set_city(const string &_city) {
  Patient::_city = _city;
}

const string &Patient::get_comment() const {
  return _comment;
}

void Patient::set_comment(const string &_comment) {
  Patient::_comment = _comment;
}

int Patient::get_phone() const {
  return _phone;
}

void Patient::set_phone(int _phone) {
  Patient::_phone = _phone;
}

int Patient::get_postalCode() const {
  return _postalCode;
}

void Patient::set_postalCode(int _postalCode) {
  Patient::_postalCode = _postalCode;
}

int Patient::get_duration() const {
  return _duration;
}

void Patient::set_duration(int _duration) {
  Patient::_duration = _duration;
}

int Patient::get_priority() const {
  return _priority;
}

void Patient::set_priority(int _priority) {
  Patient::_priority = _priority;
}

