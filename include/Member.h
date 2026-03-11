#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <vector>   // For storing the list of borrowed book titles
#include <string>
using namespace std;

class Library;  // Forward declaration

// Member inherits from User — gets all user functionality plus borrowing features
class Member : public User {
private:
    // Private vector - only Member's own functions can touch this (Encapsulation)
    vector<string> borrowedBooks;

public:
    Member(string u, string encodedPass, string n, string e);

    // Overrides the virtual menu() — Member sees borrow/return/reserve options (Polymorphism)
    void menu(Library &library) override;

    int getBorrowedCount() const;

    vector<string> getBorrowedBooks() const;

    void addBorrowedBook(const string& title);

    void removeBorrowedBook(const string& title);
};

#endif