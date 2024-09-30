#ifndef USER_H
#define USER_H

#include <bits/stdc++.h>
using namespace std;

class User
{
protected:
    string name;
    string username;
    string password;
    string contactNumber;

public:
    virtual void registerUser() = 0;
    virtual void login() = 0;
};

#endif // USER_H
