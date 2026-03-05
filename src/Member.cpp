#include <iostream>
#include <algorithm>
#include "Member.h"
#include "Library.h"
#include "Book.h"
using namespace std;

Member::Member(string u, string encodedPass, string n, string e)
    : User(u, encodedPass, n, e, "Member") {}

int Member::getBorrowedCount() const { return borrowedBooks.size(); }
vector<string> Member::getBorrowedBooks() const { return borrowedBooks; }
void Member::addBorrowedBook(const string& title) { borrowedBooks.push_back(title); }
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
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "\n--- My Borrowing Info ---\n";
            cout << "Name: " << name << "\n";
            cout << "Email: " << email << "\n";
            cout << "Books borrowed: " << borrowedBooks.size()
                 << "/" << library.getBorrowLimit() << "\n";
            if (borrowedBooks.empty()) {
                cout << "No books currently borrowed.\n";
            } else {
                for (const string& title : borrowedBooks) {
                    Book* book = library.findBook(title);
                    if (book) {
                        cout << "  - " << title
                             << " (Due: " << book->getDueDateString() << ")";
                        if (book->isOverdue()) cout << " [OVERDUE]";
                        cout << "\n";
                    }
                }
            }
        }
        else if (choice == 2) {
            cout << "Search keyword: ";
            getline(cin, input);
            library.searchBook(input);
        }
        else if (choice == 3) {
            if ((int)borrowedBooks.size() >= library.getBorrowLimit()) {
                cout << "Borrow limit reached! Max " << library.getBorrowLimit() << " books.\n";
                continue;
            }
            cout << "Title to borrow: ";
            getline(cin, input);
            if (library.borrowBook(input, username)) {
                borrowedBooks.push_back(input);
                Book* book = library.findBook(input);
                if (book)
                    cout << "Borrowed successfully! Due date: " << book->getDueDateString() << "\n";
            } else {
                cout << "Book not available for borrowing. Try reserving it.\n";
            }
        }
        else if (choice == 4) {
            cout << "Title to return: ";
            getline(cin, input);
            auto it = find(borrowedBooks.begin(), borrowedBooks.end(), input);
            if (it != borrowedBooks.end()) {
                double penalty = library.returnBook(input, username);
                borrowedBooks.erase(it);
                if (penalty > 0) {
                    cout << "Book returned. Late penalty: $" << penalty << "\n";
                } else {
                    cout << "Book returned successfully.\n";
                }
            } else {
                cout << "You haven't borrowed this book.\n";
            }
        }
        else if (choice == 5) {
            cout << "Title to reserve: ";
            getline(cin, input);
            if (library.reserveBook(input, username)) {
                cout << "Book reserved! You'll be notified when it's available.\n";
            } else {
                cout << "Cannot reserve this book (may be available to borrow or already reserved).\n";
            }
        }
        else if (choice == 6) {
            library.checkNotifications(username, email);
        }

    } while (choice != 0);
}