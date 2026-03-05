#include <iostream>
#include "Admin.h"
#include "Library.h"
using namespace std;

Admin::Admin(string u, string p) : User(u, p) {}

void Admin::menu(Library &library) {
    int choice;
    int limit;
    do {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. Set Borrow Limit\n";
        cout << "0. Logout\n";
        cin >> choice;

        if(choice == 1) {
            cout << "New borrow limit: ";
            cin >> limit;
            library.setBorrowLimit(limit);
            cout << "Borrow limit updated.\n";
        }

    } while(choice != 0);
}