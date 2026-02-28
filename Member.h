#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"

class Member : public User {
public:
    Member(string u, string p);
    void menu(Library &library);
};

#endif