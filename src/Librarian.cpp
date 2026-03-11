// Implementation of the Librarian class
#include <iostream>
#include <limits>    
#include "Librarian.h"
#include "Library.h"
#include "Book.h"
#include "Member.h"
using namespace std;

// Constructor - calls the User (parent) constructor with role set to "Librarian"
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

        // Input validation — if user types a letter instead of a number, handle it
        if (!(cin >> choice)) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discards the bad input
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();  // Discard the leftover newline character

        // Option 1: Add a new book to the library
        if (choice == 1) {
            cout << "Title: "; getline(cin, input);
            cout << "Author: "; getline(cin, input2);
            library.addBook(Book(input, input2));  // Create a Book and add it
            cout << "Book added successfully.\n";
        }
        // Option 2: Remove a book by title
        else if (choice == 2) {
            cout << "Title to remove: "; getline(cin, input);
            library.removeBook(input);
        }
        // Option 3: Update a book's title and author
        else if (choice == 3) {
            cout << "Current title: "; getline(cin, input);
            cout << "New title: "; getline(cin, input2);
            string newAuthor;
            cout << "New author: "; getline(cin, newAuthor);
            library.updateBook(input, input2, newAuthor);
        }
        // Option 4: Search for books by keyword
        else if (choice == 4) {
            cout << "Search keyword: "; getline(cin, input);
            library.searchBook(input);
        }
        // Option 5: Show all books in the library
        else if (choice == 5) {
            library.showAllBooks();
        }
        // Option 6: View all current reservations
        else if (choice == 6) {
            library.showReservations();
        }
        // Option 7: Generate a report of all overdue books
        else if (choice == 7) {
            library.showOverdueReport();
        }
        // Option 8: Send overdue notifications to all affected members
        else if (choice == 8) {
            library.sendAllOverdueNotifications();
        }

    } while (choice != 0);  // Keep showing the menu until user chooses 0 to logout
}