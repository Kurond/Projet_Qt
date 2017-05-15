#include "StaffConnector.h"

StaffConnector* StaffConnector::_instance = NULL;

StaffConnector* StaffConnector::getInstance() {
    if (_instance == NULL) {
        _instance = new StaffConnector();
    }

    return _instance;
}

StaffConnector::~StaffConnector() {
    delete _instance;
}
