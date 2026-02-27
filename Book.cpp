#include "Book.h"

Book::Book(string t, string a) {
    title = t;
    author = a;
    status = "Available";
}

string Book::getTitle() { return title; }
string Book::getAuthor() { return author; }
string Book::getStatus() { return status; }
void Book::setStatus(string s) { status = s; }