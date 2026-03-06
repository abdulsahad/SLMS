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
        cout << "6. View Reservations\n";
        cout << "7. Generate Overdue Report\n";
        cout << "8. Send Overdue Notifications\n";
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
            library.showReservations();
        }
        else if (choice == 7) {
            library.showOverdueReport();
        }
        else if (choice == 8) {
            library.sendAllOverdueNotifications();
        }

    } while (choice != 0);
}