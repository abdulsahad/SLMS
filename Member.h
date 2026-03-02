#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include "Library.h"
#include <vector>
#include <string>
using namespace std;

class Member : public User {
private:
    vector<string> borrowedBooks; 
    static const int MAX_BORROW = 5;

public:
    Member(string u, string p);
    void menu(Library &library);
};

#endif