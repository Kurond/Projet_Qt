#include "PatientConnector.h"

PatientConnector* PatientConnector::_instance = NULL;

PatientConnector* PatientConnector::getInstance() {
    if (_instance == NULL) {
        _instance = new PatientConnector();
    }

    return _instance;
}

PatientConnector::~PatientConnector() {
    delete _instance;
}

