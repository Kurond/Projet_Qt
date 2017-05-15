#include "AccountConnector.h"


AccountConnector* AccountConnector::_instance = NULL;

AccountConnector* AccountConnector::getInstance() {
    if (_instance == NULL) {
        _instance = new AccountConnector();
    }

    return _instance;
}

AccountConnector::~AccountConnector() {
    delete _instance;
}

