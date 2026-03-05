#include "Book.h"
#include <ctime>
#include <cmath>

Book::Book(string t, string a) {
    title = t;
    author = a;
    status = "Available";
    borrower = "";
    reservedBy = "";
    dueDate = 0;
    reservationDate = 0;
}

// Getters
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getStatus() const { return status; }
string Book::getBorrower() const { return borrower; }
string Book::getReservedBy() const { return reservedBy; }
time_t Book::getDueDate() const { return dueDate; }
time_t Book::getReservationDate() const { return reservationDate; }

// Setters
void Book::setTitle(string t) { title = t; }
void Book::setAuthor(string a) { author = a; }
void Book::setStatus(string s) { status = s; }
void Book::setBorrower(string b) { borrower = b; }
void Book::setReservedBy(string r) { reservedBy = r; }
void Book::setDueDate(time_t d) { dueDate = d; }
void Book::setReservationDate(time_t d) { reservationDate = d; }

// Utility methods
bool Book::isOverdue() const {
    if (status != "Borrowed" || dueDate == 0) return false;
    return time(nullptr) > dueDate;
}

bool Book::isReservationExpired() const {
    if (status != "Reserved" || reservationDate == 0) return false;
    double days = difftime(time(nullptr), reservationDate) / (60.0 * 60.0 * 24.0);
    return days > 3.0;
}

string Book::getDueDateString() const {
    if (dueDate == 0) return "N/A";
    struct tm* timeinfo = localtime(&dueDate);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return string(buffer);
}