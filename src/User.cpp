
#include "User.h"
#include "PasswordUtil.h"

// Constructor - this runs when a new User (or child like Admin/Member) is created
// It stores all the user's details into the protected member variables
User::User(string u, string encodedPass, string n, string e, string r) {
    username = u;           // Store the username
    passwordHash = encodedPass;  // Store the ENCODED password (not plain text)
    name = n;               // Store the user's full name
    email = e;              // Store the user's email address
    role = r;               // Store the role ("Admin", "Librarian", or "Member")
}

// Login function - checks if the entered username and password are correct
// It encodes the entered password and compares it with the stored encoded password
bool User::login(string u, string rawPassword) {
    return (username == u && PasswordUtil::verify(rawPassword, passwordHash));
}

// Getter functions - return private/protected data to outside code
string User::getUsername() const { return username; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
string User::getRole() const { return role; }
string User::getPasswordHash() const { return passwordHash; }