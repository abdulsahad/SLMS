// Implementation of the Book class

#include "Book.h"
#include <ctime>   
#include <cmath>   // For ceil() — rounds a number UP (e.g. 1.2 becomes 2)

// Constructor - creates a new book with default values
// A new book starts as "Available" with no borrower or reservation
Book::Book(string t, string a) {
    title = t;
    author = a;
    status = "Available";  // New books are always available
    borrower = "";          // No one has borrowed it yet
    reservedBy = "";        // No one has reserved it yet
    dueDate = 0;            // 0 means no due date set
    reservationDate = 0;    // 0 means no reservation date set
}

// Getter functions - return private data 
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getStatus() const { return status; }
string Book::getBorrower() const { return borrower; }
string Book::getReservedBy() const { return reservedBy; }
time_t Book::getDueDate() const { return dueDate; }
time_t Book::getReservationDate() const { return reservationDate; }

// Setter functions - allow controlled changes to private data 
void Book::setTitle(string t) { title = t; }
void Book::setAuthor(string a) { author = a; }
void Book::setStatus(string s) { status = s; }
void Book::setBorrower(string b) { borrower = b; }
void Book::setReservedBy(string r) { reservedBy = r; }
void Book::setDueDate(time_t d) { dueDate = d; }
void Book::setReservationDate(time_t d) { reservationDate = d; }

// Checks if this book is overdue (past its due date)
// Returns true only if the book is currently borrowed and the current time is past the due date
bool Book::isOverdue() const {
    if (status != "Borrowed" || dueDate == 0) return false;  // Not borrowed = can't be overdue
    return time(nullptr) > dueDate;  // This compares current time with due date
}

// Checks if the 3-day reservation pickup window has expired
// If a member reserved a book and didn't collect it within 3 days, it expires
bool Book::isReservationExpired() const {
    if (status != "Reserved" || reservationDate == 0) return false;
    // difftime gives the difference in seconds, so we divide to get days
    double days = difftime(time(nullptr), reservationDate) / (60.0 * 60.0 * 24.0);
    return days > 3.0;  // Expired if more than 3 days have passed
}

// Converts the due date (time_t) into a human-readable string like "2026-03-15"
string Book::getDueDateString() const {
    if (dueDate == 0) return "N/A";  // No due date set
    struct tm* timeinfo = localtime(&dueDate);  // Convert time_t to a time structure
    char buffer[11];  // Buffer to hold the formatted date string
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);  // Format as YYYY-MM-DD
    return string(buffer);
}