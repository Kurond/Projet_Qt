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
  int _id;
  string _firstName;
  string _lastName;
  string _address;
  string _city;
  string _comment;

  string _consultationDate;

  int _phone;
  int _postalCode;
  int _duration;
  int _priority;

public:
  Patient();
  Patient(const string &fistName, const string &lastName, const string &address, const string &city,
          const string &comment, int phone, int postalCode, int duration, int priority);

  int getId() const;
  void setId(int id);
  const string &getFirstName() const;
  void setFirstName(const string &firstName);
  const string &getLastName() const;
  void setLastName(const string &lastName);
  const string &getAddress() const;
  void setAddress(const string &address);
  const string &getCity() const;
  void setCity(const string &city);
  const string &getComment() const;
  void setComment(const string &comment);
  int getPhone() const;
  void setPhone(int phone);
  int getPostalCode() const;
  void setPostalCode(int postalCode);
  int getDuration() const;
  void setDuration(int duration);
  int getPriority() const;
  void setPriority(int priority);
  const string &getConsultationDate() const;
  void setConsultationDate(const string &consultationDate);

};


#endif //STL_4_PATIENT_H
