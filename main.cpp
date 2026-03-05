#include <iostream>
#include <string>
#include <limits>
#include "Library.h"
#include "User.h"
#include "Member.h"
#include "Librarian.h"
#include "Admin.h"
#include "PasswordUtil.h"

using namespace std;

int main() {
    Library library;

    // Create default admin and librarian accounts (passwords are XOR-encoded)
    library.addUser(new Admin("admin",
        PasswordUtil::encode("admin123"), "System Admin", "admin@slms.com"));
    library.addUser(new Librarian("librarian",
        PasswordUtil::encode("lib123"), "Head Librarian", "librarian@slms.com"));

    cout << "=============================================\n";
    cout << "   SMART LIBRARY MANAGEMENT SYSTEM (SLMS)\n";
    cout << "=============================================\n";
    cout << "System initialised with 10 books in the catalogue.\n";
    cout << "Default accounts: admin/admin123, librarian/lib123\n";
    cout << "Members must sign up before logging in.\n\n";

    int choice;
    string username, password, name, email;

    do {
        // Check for expired reservations each cycle
        library.checkReservationExpiry();

        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Login\n";
        cout << "2. Sign Up (New Member)\n";
        cout << "0. Exit\n";
        cout << "Select: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            bool found = false;
            for (User* user : library.getUsers()) {
                if (user->login(username, password)) {
                    cout << "Login successful! Welcome, " << user->getName()
                         << " [" << user->getRole() << "]\n";
                    user->menu(library);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid username or password!\n";
            }
        }
        else if (choice == 2) {
            cout << "\n--- New Member Registration ---\n";
            cout << "Choose a username: ";
            getline(cin, username);

            if (library.findUser(username)) {
                cout << "Username already taken! Try a different one.\n";
                continue;
            }

            cout << "Choose a password: ";
            getline(cin, password);
            cout << "Your full name: ";
            getline(cin, name);
            cout << "Your email (for notifications): ";
            getline(cin, email);

            string encoded = PasswordUtil::encode(password);
            library.addUser(new Member(username, encoded, name, email));
            cout << "Registration successful! You can now log in.\n";
        }

    } while (choice != 0);

    cout << "\nSystem shutdown. Goodbye!\n";
    return 0;
}