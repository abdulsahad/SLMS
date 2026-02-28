#include "User.h"

User::User(string u, string p) {
    username = u;
    password = p;
}

bool User::login(string u, string p) {
    return (username == u && password == p);
}

string User::getUsername() {
    return username;
}