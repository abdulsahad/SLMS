
#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

// Forward declaration — tells the compiler "Library exists"
// so we can use it as a reference without including Library.h
class Library;

// User is an Abstract class because it has a pure virtual function (menu = 0)
// cannot create a user object directly — you must create Admin/Librarian/Member
class User {
protected:
    // "protected" means only this class and its children can access these
    // This is encapsulation - hiding data from outside classes
    string username;
    string passwordHash;  // XOR-encoded password (not stored as plain text for security)
    string name;
    string email;
    string role;           

public:
    // Constructor - sets up a new user with all their details
    User(string u, string encodedPass, string n, string e, string r);

    // Checks if the username and password match this user
    bool login(string u, string rawPassword);

    // Getter functions - the ONLY way outside code can read private data (Encapsulation)
    string getUsername() const;
    string getName() const;
    string getEmail() const;
    string getRole() const;
    string getPasswordHash() const;

    // Pure virtual function - EVERY child class MUST override this (Polymorphism)
    // Each user type (Admin, Librarian, Member) shows a DIFFERENT menu
    virtual void menu(Library &library) = 0;

    // Virtual destructor - needed so child objects are properly cleaned up
    virtual ~User() {}
};

#endif