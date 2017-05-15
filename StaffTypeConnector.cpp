#include "StaffTypeConnector.h"

StaffTypeConnector* StaffTypeConnector::_instance = NULL;

StaffTypeConnector* StaffTypeConnector::getInstance() {
    if (_instance == NULL) {
        _instance = new StaffTypeConnector();
    }

    return _instance;
}

StaffTypeConnector::~StaffTypeConnector() {
    delete _instance;
}
