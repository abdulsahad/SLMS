#ifndef Librarian_H
#define Librarian_H

#include "User.h"

class Library;

class Librarian : public User {
public:
    Librarian(string u, string p);
    void menu(Library &library);
};

#endif