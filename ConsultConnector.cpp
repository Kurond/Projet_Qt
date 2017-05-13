#include "ConsultConnector.h"


ConsultConnector* ConsultConnector::_instance = NULL;

ConsultConnector* ConsultConnector::getInstance() {
    if (_instance == NULL) {
        _instance = new ConsultConnector();
    }

    return _instance;
}

ConsultConnector::~ConsultConnector() {
    delete _instance;
}

