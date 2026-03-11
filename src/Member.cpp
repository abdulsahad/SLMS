
#include <iostream>
#include <algorithm>  
#include <limits>     
#include "Member.h"
#include "Library.h"
#include "Book.h"
using namespace std;

// Constructor - calls the User (parent) constructor with role set to "Member"
Member::Member(string u, string encodedPass, string n, string e)
    : User(u, encodedPass, n, e, "Member") {}

// Returns how many books this member currently has borrowed
int Member::getBorrowedCount() const { return borrowedBooks.size(); }

// Returns a copy of the borrowedBooks vector
vector<string> Member::getBorrowedBooks() const { return borrowedBooks; }

// Adds a book title to this member's borrowed list
void Member::addBorrowedBook(const string& title) { borrowedBooks.push_back(title); }

// Removes a book title from this member's borrowed list
// Uses the erase-remove idiom - a common C++ pattern to remove items from the vectors
void Member::removeBorrowedBook(const string& title) {
    borrowedBooks.erase(
        remove(borrowedBooks.begin(), borrowedBooks.end(), title),  
        borrowedBooks.end()  
    );
}


void Member::menu(Library &library) {
    int choice;
    string input;

    do {
        cout << "\n--- MEMBER MENU (" << name << ") ---\n";
        cout << "Borrowed: " << borrowedBooks.size() << "/" << library.getBorrowLimit() << "\n";
        cout << "1. View My Borrowing Info\n";
        cout << "2. Search Book\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Reserve Book\n";
        cout << "6. Check Notifications\n";
        cout << "0. Logout\n";
        cout << "Select: ";

        // Input validation - if user types a letter instead of a number, handle it
        if (!(cin >> choice)) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard bad input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();  // Discard the leftover newline character

        // Option 1: View personal borrowing information
        if (choice == 1) {
            cout << "\n--- My Borrowing Info ---\n";
            cout << "Name: " << name << "\n";
            cout << "Email: " << email << "\n";
            cout << "Books borrowed: " << borrowedBooks.size()
                 << "/" << library.getBorrowLimit() << "\n";
            if (borrowedBooks.empty()) {
                cout << "No books currently borrowed.\n";
            } else {
                // Show each borrowed book with its due date
                for (const string& title : borrowedBooks) {
                    Book* book = library.findBook(title);
                    if (book) {
                        cout << "  - " << title
                             << " (Due: " << book->getDueDateString() << ")";
                        if (book->isOverdue()) cout << " [OVERDUE]";  // Flag overdue books
                        cout << "\n";
                    }
                }
            }
        }
        // Option 2: Search for books by keyword
        else if (choice == 2) {
            cout << "Search keyword: ";
            getline(cin, input);
            library.searchBook(input);
        }
        // Option 3: Borrow a book
        else if (choice == 3) {
            // Check if the member has reached their borrow limit (default: 5)
            if ((int)borrowedBooks.size() >= library.getBorrowLimit()) {
                cout << "Borrow limit reached! Max " << library.getBorrowLimit() << " books.\n";
                continue;  // Go back to menu
            }
            cout << "Title to borrow: ";
            getline(cin, input);
            // Try to borrow - returns true if successful
            if (library.borrowBook(input, username)) {
                borrowedBooks.push_back(input);  // Add to member's personal borrowed list
                Book* book = library.findBook(input);
                if (book)
                    cout << "Borrowed successfully! Due date: " << book->getDueDateString() << "\n";
            } else {
                cout << "Book not available for borrowing. Try reserving it.\n";
            }
        }
        // Option 4: Return a book
        else if (choice == 4) {
            cout << "Title to return: ";
            getline(cin, input);
            // Check if this member actually has this book
            auto it = find(borrowedBooks.begin(), borrowedBooks.end(), input);
            if (it != borrowedBooks.end()) {
                // Return the book and get any penalty amount
                double penalty = library.returnBook(input, username);
                borrowedBooks.erase(it);  // Remove from member's personal list
                if (penalty > 0) {
                    cout << "Book returned. Late penalty: $" << penalty << "\n";
                } else {
                    cout << "Book returned successfully.\n";
                }
            } else {
                cout << "You haven't borrowed this book.\n";
            }
        }
        // Option 5: Reserve a book that is currently borrowed by someone else
        else if (choice == 5) {
            cout << "Title to reserve: ";
            getline(cin, input);
            if (library.reserveBook(input, username)) {
                cout << "Book reserved! You'll be notified when it's available.\n";
            } else {
                cout << "Cannot reserve this book (may be available to borrow or already reserved).\n";
            }
        }
        // Option 6: Check notifications (overdue alerts, due-soon warnings, pickup notices)
        else if (choice == 6) {
            library.checkNotifications(username, email);
        }

    } while (choice != 0);  // Keep showing the menu until user chooses 0 
}