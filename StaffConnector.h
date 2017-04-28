#ifndef STAFFCONNECTOR_H
#define STAFFCONNECTOR_H

#include "Connector.h"
#include "Staff.h"

class StaffConnector  : public Connector<Staff>
{
public:
    StaffConnector();

    virtual QList<Staff> selectAll();
    virtual QList<Staff> selectFromId();
    virtual bool insert(Staff element);
};

#endif // STAFFCONNECTOR_H
