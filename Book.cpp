#include "Book.h"

// Constructor
Book::Book(string t, string a) {
    title = t;
    author = a;
    status = "Available";
    borrower = "";
    reservedBy = "";
}

// Getters applies here
string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getStatus() const {
    return status;
}

string Book::getBorrower() const {
    return borrower;
}

string Book::getReservedBy() const {
    return reservedBy;
}

// Setters applies heree
void Book::setStatus(string s) {
    status = s;
}

void Book::setBorrower(string b) {
    borrower = b;
}

void Book::setReservedBy(string r) {
    reservedBy = r;
}