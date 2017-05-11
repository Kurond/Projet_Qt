#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

class Account
{
public:
    Account();

    int getId() const;
    void setId(int id);
    int getStaffId() const;
    void setStaffId(int id);
    void setLogin(const string &name);
    const string &getLogin() const;
    void setPassword(const string &name);
    const string &getPassword() const;

private:
    int _id;
    int _idStaff;
    string _login;
    string _password;
};

#endif // ACCOUNT_H
