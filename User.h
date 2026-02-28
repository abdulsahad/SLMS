#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class Library; 

class User {
protected:
    string username;
    string password;

public:
    User(string u, string p);
    bool login(string u, string p);
    string getUsername();
    virtual void menu(Library &library) = 0;
};

#endif