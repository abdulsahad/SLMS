#include <iostream>
#include <vector>
#include "Book.h"
using namespace std;

int main() {
    vector<Book> books;
    books.push_back(Book("1984", "George Orwell"));

    cout << "Books initialized: " << books.size() << endl;

    int choice;
    do {
        cout << "\n===== SMART LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Member Login\n";
        cout << "2. Librarian Login\n";
        cout << "3. Admin Login\n";
        cout << "0. Exit\n";
        cout << "Select option: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Member login coming soon...\n";
                break;
            case 2:
                cout << "Librarian login coming soon...\n";
                break;
            case 3:
                cout << "Admin login coming soon...\n";
                break;
        }

    } while(choice != 0);

    return 0;
}