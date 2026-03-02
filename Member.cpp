#include <iostream>
#include "Member.h"
#include "Library.h"
#include <algorithm>
using namespace std;

Member::Member(string u, string p) : User(u,p) {}

void Member::menu(Library &library) {
    int choice;
    string input;

    do {
        cout << "\n--- MEMBER MENU ---\n";
        cout << "Borrowed Books: " << borrowedBooks.size() << "/" << MAX_BORROW << "\n";
        cout << "1. Search Book\n";
        cout << "2. Borrow Book\n";
        cout << "3. Return Book\n";
        cout << "0. Logout\n";
        cin >> choice;
        cin.ignore();

        if(choice == 1) {
            cout << "Keyword: ";
            getline(cin, input);
            library.searchBook(input);
        }
        else if(choice == 2) {
            if(borrowedBooks.size() >= MAX_BORROW) {
                cout << "Borrow limit reached!\n";
                continue;
            }
            cout << "Title: ";
            getline(cin, input);
            if(library.borrowBook(input, username)) {
                borrowedBooks.push_back(input);
                cout << "Borrowed successfully!\n";
            } else {
                cout << "Book not available.\n";
            }
        }
        else if(choice == 3) {
            cout << "Title to return: ";
            getline(cin, input);
            library.returnBook(input);
            borrowedBooks.erase(
                remove(borrowedBooks.begin(), borrowedBooks.end(), input),
                borrowedBooks.end()
            );
            cout << "Book returned successfully.\n";
        }

    } while(choice != 0);
}