#include "User.h"
#include "PasswordUtil.h"

User::User(string u, string encodedPass, string n, string e, string r) {
    username = u;
    passwordHash = encodedPass;
    name = n;
    email = e;
    role = r;
}

bool User::login(string u, string rawPassword) {
    return (username == u && PasswordUtil::verify(rawPassword, passwordHash));
}

string User::getUsername() const { return username; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getRole() const { return role; }
string User::getPasswordHash() const { return passwordHash; }