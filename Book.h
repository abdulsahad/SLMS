#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string status;

public:
    Book(string t, string a);
    string getTitle();
    string getAuthor();
    string getStatus();
    void setStatus(string s);
};

#endif