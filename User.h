#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class Library;

class User {
protected:
    string username;
    string passwordHash;  // XOR-encoded password (not plain text)
    string name;
    string email;
    string role;           // "Member", "Librarian", "Admin"

public:
    User(string u, string encodedPass, string n, string e, string r);
    bool login(string u, string rawPassword);
    string getUsername() const;
    string getName() const;
    string getEmail() const;
    string getRole() const;
    string getPasswordHash() const;
    virtual void menu(Library &library) = 0;
    virtual ~User() {}
};

#endif