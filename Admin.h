#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
using namespace std;

class Library;

class Admin : public User {
public:
    Admin(string u, string encodedPass, string n, string e);
    void menu(Library &library) override;
};

#endif