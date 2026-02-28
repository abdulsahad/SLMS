#ifndef Admin_H
#define Admin_H

#include "User.h"

class Admin : public User {
public:
    Admin(string u, string p);
    void menu(Library &library);
};

#endif