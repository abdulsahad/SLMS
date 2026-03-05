#include <iostream>
#include "Admin.h"
#include "Library.h"
#include "Member.h"
#include "Librarian.h"
#include "PasswordUtil.h"
using namespace std;

Admin::Admin(string u, string encodedPass, string n, string e)
    : User(u, encodedPass, n, e, "Admin") {}

void Admin::menu(Library &library) {
    int choice;
    string input, input2, input3, input4;

    do {
        cout << "\n--- ADMIN MENU (" << name << ") ---\n";
        cout << "1. Add Member Account\n";
        cout << "2. Add Librarian Account\n";
        cout << "3. Remove Account\n";
        cout << "4. View All Accounts\n";
        cout << "5. Set Borrow Limit (current: " << library.getBorrowLimit() << ")\n";
        cout << "6. Set Late Return Penalty (current: $" << library.getLatePenalty() << "/day)\n";
        cout << "7. View Encoded Passwords\n";
        cout << "8. Decode Password (Owner Only)\n";
        cout << "0. Logout\n";
        cout << "Select: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1 || choice == 2) {
            cout << "Username: "; getline(cin, input);
            if (library.findUser(input)) {
                cout << "Username already taken!\n";
                continue;
            }
            cout << "Password: "; getline(cin, input2);
            cout << "Full Name: "; getline(cin, input3);
            cout << "Email: "; getline(cin, input4);

            string encoded = PasswordUtil::encode(input2);
            if (choice == 1) {
                library.addUser(new Member(input, encoded, input3, input4));
                cout << "Member account created.\n";
            } else {
                library.addUser(new Librarian(input, encoded, input3, input4));
                cout << "Librarian account created.\n";
            }
        }
        else if (choice == 3) {
            cout << "Username to remove: "; getline(cin, input);
            library.removeUser(input);
        }
        else if (choice == 4) {
            cout << "\n--- All Accounts ---\n";
            for (User* user : library.getUsers()) {
                cout << "  [" << user->getRole() << "] " << user->getUsername()
                     << " - " << user->getName() << " (" << user->getEmail() << ")\n";
            }
        }
        else if (choice == 5) {
            int limit;
            cout << "New borrow limit: ";
            cin >> limit;
            cin.ignore();
            library.setBorrowLimit(limit);
            cout << "Borrow limit updated to " << limit << ".\n";
        }
        else if (choice == 6) {
            double penalty;
            cout << "New penalty per day ($): ";
            cin >> penalty;
            cin.ignore();
            library.setLatePenalty(penalty);
            cout << "Late penalty updated to $" << penalty << " per day.\n";
        }
        else if (choice == 7) {
            cout << "\n--- Encoded Passwords ---\n";
            for (User* user : library.getUsers()) {
                cout << "  " << user->getUsername() << ": " << user->getPasswordHash() << "\n";
            }
            cout << "\nNote: To decode, use option 8 with the secret key from PasswordUtil.cpp\n";
        }
        else if (choice == 8) {
            cout << "Enter secret key: "; getline(cin, input);
            if (input == PasswordUtil::getSecretKey()) {
                cout << "Username to decode: "; getline(cin, input);
                User* user = library.findUser(input);
                if (user) {
                    cout << "Password: " << PasswordUtil::decode(user->getPasswordHash()) << "\n";
                } else {
                    cout << "User not found.\n";
                }
            } else {
                cout << "Invalid secret key. Access denied.\n";
            }
        }

    } while (choice != 0);
}