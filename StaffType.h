#ifndef STAFFTYPE_H
#define STAFFTYPE_H


class StaffType
{
public:
    StaffType();

    int getId() const;
    void setId(int id);
private:
    int id;
    string _name;
};

#endif // STAFFTYPE_H
