#include <iostream>
#include "Librarian.h"
#include "Library.h"
#include "Book.h"
using namespace std;

Librarian::Librarian(string u, string p) : User(u, p) {}

void Librarian::menu(Library &library) {
    int choice;
    string input, author;
    do {
        cout << "\n--- LIBRARIAN MENU ---\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Overdue Report (placeholder)\n";
        cout << "0. Logout\n";
        cin >> choice;
        cin.ignore();

        if(choice == 1) {
            cout << "Title: "; getline(cin, input);
            cout << "Author: "; getline(cin, author);
            library.addBook(Book(input, author));
            cout << "Book added successfully.\n";
        }
        else if(choice == 2) {
            cout << "Title to remove: "; getline(cin, input);
            library.removeBook(input);
            cout << "Book removed successfully.\n";
        }
        else if(choice == 3) {
            library.showOverdueReport();
        }

    } while(choice != 0);
}