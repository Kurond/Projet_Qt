//
// Created by Flwrnt on 24/03/2017.
// Copyright (c) 2017 ___FULLUSERNAME___. All rights reserved.
//

#ifndef STL_4_PATIENT_H
#define STL_4_PATIENT_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

using namespace std;


class Patient {
private:
  string _fistName;
  string _lastName;
  string _address;
  string _city;
  string _comment;

  int _phone;
  int _postalCode;
  int _duration;
  int _priority;

public:
  Patient(const string &_fistName, const string &_lastName, const string &_address, const string &_city,
          const string &_comment, int _phone, int _postalCode, int _duration, int _priority);

  const string &get_fistName() const;
  void set_fistName(const string &_fistName);
  const string &get_lastName() const;
  void set_lastName(const string &_lastName);
  const string &get_address() const;
  void set_address(const string &_address);
  const string &get_city() const;
  void set_city(const string &_city);
  const string &get_comment() const;
  void set_comment(const string &_comment);
  int get_phone() const;
  void set_phone(int _phone);
  int get_postalCode() const;
  void set_postalCode(int _postalCode);
  int get_duration() const;
  void set_duration(int _duration);
  int get_priority() const;
  void set_priority(int _priority);
};


#endif //STL_4_PATIENT_H
