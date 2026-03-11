// Admins can manage accounts and set library rules as well.
// Inherits from the User class.

#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
using namespace std;

class Library;  // Forward declaration so we can use Library in the menu function

// Admin inherits from User using "public User"
// This means Admin gets all of User's members (username, name, etc)
class Admin : public User {
public:
    // This is the constructor that calls the User constructor and sets role to "Admin"
    Admin(string u, string encodedPass, string n, string e);

    // Override the pure virtual menu() from User — this is POLYMORPHISM
    // Admin's menu is completely different from Member's or Librarian's menu
    void menu(Library &library) override;
};

#endif