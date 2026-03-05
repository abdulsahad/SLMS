#include <iostream>
#include "Librarian.h"
#include "Library.h"
#include "Book.h"
#include "Member.h"
using namespace std;

Librarian::Librarian(string u, string encodedPass, string n, string e)
    : User(u, encodedPass, n, e, "Librarian") {}

void Librarian::menu(Library &library) {
    int choice;
    string input, input2;

    do {
        cout << "\n--- LIBRARIAN MENU (" << name << ") ---\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Update Book\n";
        cout << "4. Search Book\n";
        cout << "5. View All Books\n";
        cout << "6. Process Borrow Request\n";
        cout << "7. Process Return\n";
        cout << "8. View Reservations\n";
        cout << "9. Generate Overdue Report\n";
        cout << "10. Send Overdue Notifications\n";
        cout << "0. Logout\n";
        cout << "Select: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Title: "; getline(cin, input);
            cout << "Author: "; getline(cin, input2);
            library.addBook(Book(input, input2));
            cout << "Book added successfully.\n";
        }
        else if (choice == 2) {
            cout << "Title to remove: "; getline(cin, input);
            library.removeBook(input);
        }
        else if (choice == 3) {
            cout << "Current title: "; getline(cin, input);
            cout << "New title: "; getline(cin, input2);
            string newAuthor;
            cout << "New author: "; getline(cin, newAuthor);
            library.updateBook(input, input2, newAuthor);
        }
        else if (choice == 4) {
            cout << "Search keyword: "; getline(cin, input);
            library.searchBook(input);
        }
        else if (choice == 5) {
            library.showAllBooks();
        }
        else if (choice == 6) {
            cout << "Member username: "; getline(cin, input);
            User* memberUser = library.findUser(input);
            if (memberUser && memberUser->getRole() == "Member") {
                Member* member = dynamic_cast<Member*>(memberUser);
                if (member && member->getBorrowedCount() >= library.getBorrowLimit()) {
                    cout << "Member has reached the borrow limit.\n";
                } else {
                    cout << "Book title: "; getline(cin, input2);
                    if (library.borrowBook(input2, input)) {
                        if (member) member->addBorrowedBook(input2);
                        Book* book = library.findBook(input2);
                        if (book)
                            cout << "Borrow processed. Due: " << book->getDueDateString() << "\n";
                    } else {
                        cout << "Book not available for borrowing.\n";
                    }
                }
            } else {
                cout << "Member not found.\n";
            }
        }
        else if (choice == 7) {
            cout << "Member username: "; getline(cin, input);
            User* memberUser = library.findUser(input);
            if (memberUser && memberUser->getRole() == "Member") {
                cout << "Book title: "; getline(cin, input2);
                Member* member = dynamic_cast<Member*>(memberUser);
                double penalty = library.returnBook(input2, input);
                if (member) member->removeBorrowedBook(input2);
                if (penalty > 0) {
                    cout << "Return processed. Late penalty: $" << penalty << "\n";
                } else {
                    cout << "Return processed successfully.\n";
                }
            } else {
                cout << "Member not found.\n";
            }
        }
        else if (choice == 8) {
            library.showReservations();
        }
        else if (choice == 9) {
            library.showOverdueReport();
        }
        else if (choice == 10) {
            library.sendAllOverdueNotifications();
        }

    } while (choice != 0);
}