#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
using namespace std;

class Library;

class Librarian : public User {
public:
    Librarian(string u, string encodedPass, string n, string e);
    void menu(Library &library) override;
};

#endif