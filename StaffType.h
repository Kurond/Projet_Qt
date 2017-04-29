#ifndef STAFFTYPE_H
#define STAFFTYPE_H

#include <string>

using namespace std;

class StaffType
{
public:
    StaffType();

    int getId() const;
    void setId(int id);
private:
    int _id;
    string _name;
};

#endif // STAFFTYPE_H
