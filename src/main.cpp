
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
    // Create the library - this also loads 10 default books 
    Library library;

    // Create default admin and librarian accounts
    // Passwords are encoded using XOR cipher before being stored
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

    // Main program loop - keeps running until user selects 0 (Exit)
    do {
        // Check if any reservations have expired (3-day window) every time the menu shows
        library.checkReservationExpiry();

        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Login\n";
        cout << "2. Sign Up (New Member)\n";
        cout << "0. Exit\n";
        cout << "Select: ";

        // Input validation - handles when user types a letter instead of a number
        if (!(cin >> choice)) {
            cin.clear();  // Clear the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // this will discard the bad input
            cout << "Invalid input. Please enter a number.\n";
            continue;  // Skip to next loop iteration
        }
        cin.ignore();  // Discard the leftover newline character

        // Option 1: Login - checks credentials against all registered users
        if (choice == 1) {
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            bool found = false;
            // Loop through all users and try to match the credentials
            for (User* user : library.getUsers()) {
                if (user->login(username, password)) {
                    cout << "Login successful! Welcome, " << user->getName()
                         << " [" << user->getRole() << "]\n";
                    // POLYMORPHISM in action — user->menu() calls the correct menu
                    // depending on whether the user is Admin, Librarian, or Member
                    user->menu(library);
                    found = true;
                    break;  // Stop searching after a match
                }
            }
            if (!found) {
                cout << "Invalid username or password!\n";
            }
        }
        // Option 2: Sign up — register a new member account
        else if (choice == 2) {
            cout << "\n--- New Member Registration ---\n";
            cout << "Choose a username: ";
            getline(cin, username);

            // Check if the username is already taken
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

            // Encode the password and create a new Member account
            string encoded = PasswordUtil::encode(password);
            library.addUser(new Member(username, encoded, name, email));
            cout << "Registration successful! You can now log in.\n";
        }

    } while (choice != 0);  // Exit when user selects 0

    cout << "\nSystem shutdown. Goodbye!\n";
    return 0;  
}