// Book.h - Represents a single book in the library
// Each book tracks its title, author, status, borrower,
// reservation info, and due dates.
// Demonstrates ENCAPSULATION - all data is private,
#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ctime>   
using namespace std;

class Book {
private:
    // All data is PRIVATE - can only be accessed through getters/setters below
    // This is ENCAPSULATION - protects the data from being changed incorrectly
    string title;            
    string author;           
    string status;           
    string borrower;         
    string reservedBy;       
    time_t dueDate;          
    time_t reservationDate;  
public:
    // Constructor - creates a new book with "Available" status
    Book(string t, string a);

    // Getter functions - the ONLY way to Read private data from outside the class
    string getTitle() const;
    string getAuthor() const;
    string getStatus() const;
    string getBorrower() const;
    string getReservedBy() const;
    time_t getDueDate() const;
    time_t getReservationDate() const;

    // Setter functions - the ONLY way to Change private data from outside the class
    void setTitle(string t);
    void setAuthor(string a);
    void setStatus(string s);
    void setBorrower(string b);
    void setReservedBy(string r);
    void setDueDate(time_t d);
    void setReservationDate(time_t d);

    // Utility functions
    bool isOverdue() const;            // Checks if the book is past its due date
    bool isReservationExpired() const; // Checks if the 3-day pickup window has passed
    string getDueDateString() const;   // Returns the due date as a readable string
};

#endif