#include <iostream>
#include <cmath>
#include "Library.h"
#include "User.h"
#include "Notification.h"
using namespace std;

Library::Library() : borrowLimit(5), latePenalty(1.0) {
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

Library::~Library() {
    for (User* u : users) {
        delete u;
    }
}

// ==================== Book Management ====================

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::removeBook(const string& title) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getTitle() == title) {
            books.erase(it);
            cout << "Book '" << title << "' removed.\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void Library::updateBook(const string& oldTitle, const string& newTitle, const string& newAuthor) {
    Book* book = findBook(oldTitle);
    if (book) {
        book->setTitle(newTitle);
        book->setAuthor(newAuthor);
        cout << "Book updated successfully.\n";
    } else {
        cout << "Book not found.\n";
    }
}

void Library::searchBook(const string& keyword) {
    bool found = false;
    for (Book& b : books) {
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

void Library::showAllBooks() {
    cout << "\n--- All Books (" << books.size() << ") ---\n";
    for (Book& b : books) {
        cout << "  " << b.getTitle() << " by " << b.getAuthor()
             << " [" << b.getStatus() << "]";
        if (b.getStatus() == "Borrowed") {
            cout << " - Borrower: " << b.getBorrower()
                 << " Due: " << b.getDueDateString();
            if (b.isOverdue()) cout << " [OVERDUE]";
        }
        if (!b.getReservedBy().empty())
            cout << " Reserved by: " << b.getReservedBy();
        cout << "\n";
    }
}

Book* Library::findBook(const string& title) {
    for (Book& b : books) {
        if (b.getTitle() == title) return &b;
    }
    return nullptr;
}

// ==================== Borrow / Return / Reserve ====================

bool Library::borrowBook(const string& title, const string& username) {
    for (Book& b : books) {
        if (b.getTitle() == title) {
            // Can borrow if Available, or if Reserved by this user
            if (b.getStatus() == "Available" ||
                (b.getStatus() == "Reserved" && b.getReservedBy() == username)) {
                b.setStatus("Borrowed");
                b.setBorrower(username);
                b.setReservedBy("");
                // Due date = 3 minutes from now
                time_t now = time(nullptr);
                b.setDueDate(now + (3 * 60));
                return true;
            }
        }
    }
    return false;
}

double Library::returnBook(const string& title, const string& username) {
    for (Book& b : books) {
        if (b.getTitle() == title && b.getBorrower() == username) {
            double penalty = 0;
            // Calculate overdue penalty
            if (b.isOverdue()) {
                double daysLate = difftime(time(nullptr), b.getDueDate()) / (60.0 * 60.0 * 24.0);
                penalty = ceil(daysLate) * latePenalty;
            }

            // If someone reserved this book, make it available for pickup
            if (!b.getReservedBy().empty()) {
                b.setStatus("Reserved");
                b.setReservationDate(time(nullptr)); // Start 3-day pickup window
                // Notify the reserver
                User* reserver = findUser(b.getReservedBy());
                if (reserver) {
                    Notification::sendConsoleAlert(reserver->getUsername(),
                        "The book '" + title + "' you reserved is now available! You have 3 days to collect it.");
                }
            } else {
                b.setStatus("Available");
            }
            b.setBorrower("");
            b.setDueDate(0);
            return penalty;
        }
    }
    return 0;
}

bool Library::reserveBook(const string& title, const string& username) {
    for (Book& b : books) {
        if (b.getTitle() == title && b.getStatus() == "Borrowed" && b.getReservedBy().empty()) {
            b.setReservedBy(username);
            return true;
        }
    }
    return false;
}

void Library::checkReservationExpiry() {
    for (Book& b : books) {
        if (b.isReservationExpired()) {
            cout << "  Reservation expired: '" << b.getTitle()
                 << "' (was reserved by " << b.getReservedBy() << ")\n";
            b.setReservedBy("");
            b.setStatus("Available");
            b.setReservationDate(0);
        }
    }
}

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

void Library::showOverdueReport() {
    cout << "\n--- Overdue Books Report ---\n";
    bool found = false;
    for (Book& b : books) {
        if (b.isOverdue()) {
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

void Library::setBorrowLimit(int limit) { borrowLimit = limit; }
int Library::getBorrowLimit() const { return borrowLimit; }
void Library::setLatePenalty(double penalty) { latePenalty = penalty; }
double Library::getLatePenalty() const { return latePenalty; }

// ==================== User Management ====================

void Library::addUser(User* user) {
    if (findUser(user->getUsername())) {
        cout << "Username already exists!\n";
        delete user;
        return;
    }
    users.push_back(user);
}

void Library::removeUser(const string& username) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getUsername() == username) {
            if ((*it)->getRole() == "Admin") {
                cout << "Cannot remove admin accounts!\n";
                return;
            }
            delete *it;
            users.erase(it);
            cout << "Account '" << username << "' removed.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

vector<User*>& Library::getUsers() {
    return users;
}

User* Library::findUser(const string& username) {
    for (User* u : users) {
        if (u->getUsername() == username) return u;
    }
    return nullptr;
}

// ==================== Notifications ====================

void Library::checkNotifications(const string& username, const string& email) {
    cout << "\n--- Notifications for " << username << " ---\n";
    bool hasNotification = false;

    for (Book& b : books) {
        // Due date warnings and overdue alerts
        if (b.getBorrower() == username && b.getStatus() == "Borrowed") {
            if (b.isOverdue()) {
                double daysLate = difftime(time(nullptr), b.getDueDate()) / (60.0 * 60.0 * 24.0);
                cout << "  [OVERDUE] '" << b.getTitle() << "' was due " << b.getDueDateString()
                     << " (" << (int)ceil(daysLate) << " days late)\n";
                hasNotification = true;
            } else {
                double daysLeft = difftime(b.getDueDate(), time(nullptr)) / (60.0 * 60.0 * 24.0);
                if (daysLeft <= 3) {
                    cout << "  [DUE SOON] '" << b.getTitle() << "' due on "
                         << b.getDueDateString() << " (" << (int)daysLeft << " days left)\n";
                    hasNotification = true;
                }
            }
        }
        // Reservation pickup ready
        if (b.getReservedBy() == username && b.getStatus() == "Reserved") {
            cout << "  [PICKUP] '" << b.getTitle() << "' is available for pickup!\n";
            hasNotification = true;
        }
    }

    if (!hasNotification) cout << "  No new notifications.\n";
}

void Library::sendAllOverdueNotifications() {
    cout << "\nSending overdue notifications...\n";
    bool anySent = false;
    for (Book& b : books) {
        if (b.isOverdue()) {
            User* borrower = findUser(b.getBorrower());
            if (borrower) {
                double daysLate = difftime(time(nullptr), b.getDueDate()) / (60.0 * 60.0 * 24.0);
                double penalty = ceil(daysLate) * latePenalty;

                string msg = "Dear " + borrower->getName() + ",\n\n"
                    "The book '" + b.getTitle() + "' is overdue.\n"
                    "Due date: " + b.getDueDateString() + "\n"
                    "Days late: " + to_string((int)ceil(daysLate)) + "\n"
                    "Current penalty: $" + to_string(penalty) + "\n\n"
                    "Please return it as soon as possible.\n\nSLMS Library";

                Notification::sendConsoleAlert(borrower->getUsername(),
                    "OVERDUE: '" + b.getTitle() + "' - Penalty: $" + to_string(penalty));
                anySent = true;
            }
        }
    }
    if (!anySent) cout << "No overdue books to notify about.\n";
}