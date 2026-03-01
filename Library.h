#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "Book.h"
using namespace std;

class Library {
private:
    vector<Book> books;

public:
    Library();

    void searchBook(string keyword);
    bool borrowBook(string title, string user);
    void returnBook(string title);
};

#endif