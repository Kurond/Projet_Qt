#include "StaffType.h"

StaffType::StaffType() : _id(0), _name("")
{}

int StaffType::getId() const
{
    return _id;
}

void StaffType::setId(int id)
{
    StaffType::_id = id;
}

void StaffType::setName(const string &name)
{
    _name = name;
}

const string &StaffType::getName() const
{
    return _name;
}
