#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    string status;      
    string borrower;
    string reservedBy;

public:
    // Constructor
    Book(string t, string a);

    // Getters
    string getTitle() const;
    string getAuthor() const;
    string getStatus() const;
    string getBorrower() const;
    string getReservedBy() const;

    // Setters
    void setStatus(string s);
    void setBorrower(string b);
    void setReservedBy(string r);
};

#endif