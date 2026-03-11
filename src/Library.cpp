// Implementation of the Library class
#include <iostream>
#include <cmath>       //  used in calculating late penalties
#include "Library.h"
#include "User.h"
#include "Notification.h"
using namespace std;

// Constructor - sets up the library with default settings and sample books
// borrowLimit is set to 5 (members can borrow up to 5 books)
// latePenalty is set to $1.00 per day for overdue returns
Library::Library() : borrowLimit(5), latePenalty(1.0) {
    // Add 10 sample books to the library catalogue
    books.push_back(Book("1984", "George Orwell"));
    books.push_back(Book("Dune", "Frank Herbert"));
    books.push_back(Book("Hamlet", "Shakespeare"));
    books.push_back(Book("Foundation", "Asimov"));
    books.push_back(Book("Clean Code", "Robert Martin"));
    books.push_back(Book("The Hobbit", "Tolkien"));
    books.push_back(Book("Dracula", "Bram Stoker"));
    books.push_back(Book("It", "Stephen King"));
    books.push_back(Book("Sapiens", "Harari"));
    books.push_back(Book("Algorithms", "CLRS"));
}

// Destructor - runs when the Library object is destroyed (at program exit)
// We must delete every User pointer we created with "new" to prevent memory leaks
Library::~Library() {
    for (User* u : users) {
        delete u;  // Free the memory allocated for each user
    }
}

// ==================== Book Management ====================

// Adds a new book to the library's book list
void Library::addBook(const Book& book) {
    books.push_back(book);  // Add the book to the vector
}

// Removes a book from the library by its title
// Uses an iterator to find and erase the book from the vector
void Library::removeBook(const string& title) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getTitle() == title) {
            books.erase(it);  // Remove the book from the vector
            cout << "Book '" << title << "' removed.\n";
            return;  // Stop searching after removing
        }
    }
    cout << "Book not found.\n";  // If we get here, no book matched the title
}

// Updates a book's title and author
// First finds the book by its old title, then changes it
void Library::updateBook(const string& oldTitle, const string& newTitle, const string& newAuthor) {
    Book* book = findBook(oldTitle);  // Find the book by its old title
    if (book) {
        book->setTitle(newTitle);
        book->setAuthor(newAuthor);
        cout << "Book updated successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

// Searches for books by keyword - checks both title and author
// Uses string find() to check if the keyword appears anywhere in the title or author
void Library::searchBook(const string& keyword) {
    bool found = false;
    for (Book& b : books) {
        // string npos means "not found" - so if find() != npos, it was foiund in the string
        if (b.getTitle().find(keyword) != string::npos ||
            b.getAuthor().find(keyword) != string::npos) {
            cout << "  " << b.getTitle() << " by " << b.getAuthor()
                 << " [" << b.getStatus() << "]";
            if (b.getStatus() == "Borrowed") {
                cout << " (Due: " << b.getDueDateString() << ")";
                if (!b.getReservedBy().empty())
                    cout << " [Reserved by: " << b.getReservedBy() << "]";
            }
            cout << "\n";
            found = true;
        }
    }
    if (!found) cout << "No books found matching '" << keyword << "'.\n";
}

// Displays every book in the library with its current status
void Library::showAllBooks() {
    cout << "\n--- All Books (" << books.size() << ") ---\n";
    for (Book& b : books) {
        cout << "  " << b.getTitle() << " by " << b.getAuthor()
             << " [" << b.getStatus() << "]";
        if (b.getStatus() == "Borrowed") {
            cout << " - Borrower: " << b.getBorrower()
                 << " Due: " << b.getDueDateString();
            if (b.isOverdue()) cout << " [OVERDUE]";  // Flag overdue books
        }
        if (!b.getReservedBy().empty())
            cout << " Reserved by: " << b.getReservedBy();
        cout << "\n";
    }
}

// Finds a book by its exact title and returns a pointer to it
// Returns nullptr (null) if no book with that title exists
Book* Library::findBook(const string& title) {
    for (Book& b : books) {
        if (b.getTitle() == title) return &b;  // Return address of the matching book
    }
    return nullptr;  // No match found
}

// ==================== Borrow / Return / Reserve ====================

// Allows a member to borrow a book
// Sets a due date of 3 minutes from now (short for demo/testing purposes for my demostration)
// Returns true if borrow was successful, false otherwise
bool Library::borrowBook(const string& title, const string& username) {
    for (Book& b : books) {
        if (b.getTitle() == title) {
            // Can borrow if Available, or if this user has a reservation on it
            if (b.getStatus() == "Available" ||
                (b.getStatus() == "Reserved" && b.getReservedBy() == username)) {
                b.setStatus("Borrowed");       // Update status to Borrowed
                b.setBorrower(username);        // Record who borrowed it
                b.setReservedBy("");            // Clear any reservation
                // Set due date to 3 minutes from now (for easy demo testing)
                time_t now = time(nullptr);
                b.setDueDate(now + (3 * 60));   // 3 * 60 seconds = 3 minutes
                return true;  // Borrow successful
            }
        }
    }
    return false;  // Book not found or not available
}

// Handles returning a book - calculates any overdue penalty
// If someone has reserved this book, it becomes "Reserved" for them to pick up
// Returns the penalty amount (0 if returned on time, or the calculated fine if late)
double Library::returnBook(const string& title, const string& username) {
    for (Book& b : books) {
        if (b.getTitle() == title && b.getBorrower() == username) {
            double penalty = 0;

            // Check if the book is overdue and calculate the fine
            if (b.isOverdue()) {
                // Calculate how many days late (difftime gives seconds)
                double daysLate = difftime(time(nullptr), b.getDueDate()) / (60.0 * 60.0 * 24.0);
                penalty = ceil(daysLate) * latePenalty;  // Round up days * penalty per day
            }

            // If someone reserved this book while it was borrowed, notify them
            if (!b.getReservedBy().empty()) {
                b.setStatus("Reserved");                  // Book is now reserved for pickup
                b.setReservationDate(time(nullptr));      // Start the 3-day pickup window
                // Send a notification to the person who reserved it
                User* reserver = findUser(b.getReservedBy());
                if (reserver) {
                    Notification::sendConsoleAlert(reserver->getUsername(),
                        "The book '" + title + "' you reserved is now available! You have 3 days to collect it.");
                }
            } else {
                b.setStatus("Available");  // No reservation, book goes back on shelf
            }
            b.setBorrower("");   // Clear the borrower
            b.setDueDate(0);     // Reset the due date
            return penalty;      // Return the penalty amount (0 if on time)
        }
    }
    return 0;  // Book not found or not borrowed by this user
}

// Reserves a book that is currently borrowed by someone else
// Can only reserve a book that is "Borrowed" and not already reserved
// Also cannot reserve a book that is currently borrowing yourself
bool Library::reserveBook(const string& title, const string& username) {
    for (Book& b : books) {
        if (b.getTitle() == title && b.getStatus() == "Borrowed"
            && b.getReservedBy().empty() && b.getBorrower() != username) {
            b.setReservedBy(username);  // Mark this user as the reserver
            return true;
        }
    }
    return false;  // Can't reserve — book may be available, already reserved, or not found
}

// Checks all books for expired reservations (3-day pickup window)
// If someone didn't collect their reserved book in time, the reservation is cancelled
void Library::checkReservationExpiry() {
    for (Book& b : books) {
        if (b.isReservationExpired()) {
            cout << "  Reservation expired: '" << b.getTitle()
                 << "' (was reserved by " << b.getReservedBy() << ")\n";
            b.setReservedBy("");         // Clear the reservation
            b.setStatus("Available");    // Book goes back on shelf
            b.setReservationDate(0);     // Reset the reservation date
        }
    }
}

// Shows all books that currently have a reservation
void Library::showReservations() {
    cout << "\n--- Current Reservations ---\n";
    bool found = false;
    for (Book& b : books) {
        if (!b.getReservedBy().empty()) {
            cout << "  " << b.getTitle() << " - Reserved by: " << b.getReservedBy()
                 << " [Book status: " << b.getStatus() << "]\n";
            found = true;
        }
    }
    if (!found) cout << "No active reservations.\n";
}

// ==================== Reports ====================

// Generates a report showing all overdue books with penalties
// Used by librarians to see who has late books and how much they owe
void Library::showOverdueReport() {
    cout << "\n--- Overdue Books Report ---\n";
    bool found = false;
    for (Book& b : books) {
        if (b.isOverdue()) {
            // Calculate how many days late and the penalty
            double daysLate = difftime(time(nullptr), b.getDueDate()) / (60.0 * 60.0 * 24.0);
            double penalty = ceil(daysLate) * latePenalty;
            cout << "  " << b.getTitle() << " - Borrowed by: " << b.getBorrower()
                 << " | Due: " << b.getDueDateString()
                 << " | Days late: " << (int)ceil(daysLate)
                 << " | Penalty: $" << penalty << "\n";
            found = true;
        }
    }
    if (!found) cout << "No overdue books.\n";
}

// ==================== Settings ====================

// Setter and getter functions for library settings 
// Only admins use these through their menu
void Library::setBorrowLimit(int limit) { borrowLimit = limit; }
int Library::getBorrowLimit() const { return borrowLimit; }
void Library::setLatePenalty(double penalty) { latePenalty = penalty; }
double Library::getLatePenalty() const { return latePenalty; }

// ==================== User Management ====================

// Adds a new user to the system
// Checks for duplicate usernames first - if taken, deletes the user to prevent memory leak
void Library::addUser(User* user) {
    if (findUser(user->getUsername())) {
        cout << "Username already exists!\n";
        delete user;  // Free the memory to prevent a leak
        return;
    }
    users.push_back(user);  // Add the user pointer to our list
}

// Removes a user account by username
// Admin accounts are protected and cannot be removed
void Library::removeUser(const string& username) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getUsername() == username) {
            // Safety check - don't allow removing admin accounts
            if ((*it)->getRole() == "Admin") {
                cout << "Cannot remove admin accounts!\n";
                return;
            }
            delete *it;        // Free the memory for this user
            users.erase(it);   // Remove the pointer from the vector
            cout << "Account '" << username << "' removed.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

// Returns a reference to the full list of users
// Used by admin to view all accounts and by login to check credentials
vector<User*>& Library::getUsers() {
    return users;
}

// Finds a user by their username - returns a pointer to the user or nullptr if not found
User* Library::findUser(const string& username) {
    for (User* u : users) {
        if (u->getUsername() == username) return u;
    }
    return nullptr;
}

// ==================== Notifications ====================

// Checks and displays all notifications for a specific member
// Shows: overdue alerts, due-soon warnings, and reservation pickup notices
void Library::checkNotifications(const string& username, const string& email) {
    cout << "\n--- Notifications for " << username << " ---\n";
    bool hasNotification = false;

    for (Book& b : books) {
        // Check books this user has borrowed
        if (b.getBorrower() == username && b.getStatus() == "Borrowed") {
            if (b.isOverdue()) {
                // OVERDUE - book is past its due date
                double daysLate = difftime(time(nullptr), b.getDueDate()) / (60.0 * 60.0 * 24.0);
                cout << "  [OVERDUE] '" << b.getTitle() << "' was due " << b.getDueDateString()
                     << " (" << (int)ceil(daysLate) << " days late)\n";
                hasNotification = true;
            } else {
                // DUE SOON - book is due within 3 days
                double daysLeft = difftime(b.getDueDate(), time(nullptr)) / (60.0 * 60.0 * 24.0);
                if (daysLeft <= 3) {
                    cout << "  [DUE SOON] '" << b.getTitle() << "' due on "
                         << b.getDueDateString() << " (" << (int)daysLeft << " days left)\n";
                    hasNotification = true;
                }
            }
        }
        // Check if a book this user reserved is ready for pickup
        if (b.getReservedBy() == username && b.getStatus() == "Reserved") {
            cout << "  [PICKUP] '" << b.getTitle() << "' is available for pickup!\n";
            hasNotification = true;
        }
    }

    if (!hasNotification) cout << "  No new notifications.\n";
}

// Sends overdue notifications to all users who have overdue books
// Used by librarians to alert everyone at once
void Library::sendAllOverdueNotifications() {
    cout << "\nSending overdue notifications...\n";
    bool anySent = false;
    for (Book& b : books) {
        if (b.isOverdue()) {
            // Find the user who borrowed this overdue book
            User* borrower = findUser(b.getBorrower());
            if (borrower) {
                double daysLate = difftime(time(nullptr), b.getDueDate()) / (60.0 * 60.0 * 24.0);
                double penalty = ceil(daysLate) * latePenalty;

                // Build a detailed notification message
                string msg = "Dear " + borrower->getName() + ",\n\n"
                    "The book '" + b.getTitle() + "' is overdue.\n"
                    "Due date: " + b.getDueDateString() + "\n"
                    "Days late: " + to_string((int)ceil(daysLate)) + "\n"
                    "Current penalty: $" + to_string(penalty) + "\n\n"
                    "Please return it as soon as possible.\n\nSLMS Library";

                // Send the alert to the console
                Notification::sendConsoleAlert(borrower->getUsername(),
                    "OVERDUE: '" + b.getTitle() + "' - Penalty: $" + to_string(penalty));
                anySent = true;
            }
        }
    }
    if (!anySent) cout << "No overdue books to notify about.\n";
}