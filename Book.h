#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <ctime>
using namespace std;

class Book {
private:
    string title;
    string author;
    string status;          // "Available", "Borrowed", "Reserved"
    string borrower;
    string reservedBy;
    time_t dueDate;          // When the borrowed book must be returned
    time_t reservationDate;  // When reservation pickup window started

public:
    Book(string t, string a);

    // Getters
    string getTitle() const;
    string getAuthor() const;
    string getStatus() const;
    string getBorrower() const;
    string getReservedBy() const;
    time_t getDueDate() const;
    time_t getReservationDate() const;

    // Setters
    void setTitle(string t);
    void setAuthor(string a);
    void setStatus(string s);
    void setBorrower(string b);
    void setReservedBy(string r);
    void setDueDate(time_t d);
    void setReservationDate(time_t d);

    // Utility
    bool isOverdue() const;
    bool isReservationExpired() const;
    string getDueDateString() const;
};

#endif