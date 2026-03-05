#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <vector>
#include <string>
using namespace std;

class Library;

class Member : public User {
private:
    vector<string> borrowedBooks;

public:
    Member(string u, string encodedPass, string n, string e);
    void menu(Library &library) override;
    int getBorrowedCount() const;
    vector<string> getBorrowedBooks() const;
    void addBorrowedBook(const string& title);
    void removeBorrowedBook(const string& title);
};

#endif