// Librarians manage books, handle reservations and reports.
#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
using namespace std;

class Library;  // Forward declaration

class Librarian : public User {
public:
    // Constructor - passes details up to the User constructor
    Librarian(string u, string encodedPass, string n, string e);

    // Overrides the virtual menu() - Librarian sees book management options (Polymorphism)
    void menu(Library &library) override;
};

#endif