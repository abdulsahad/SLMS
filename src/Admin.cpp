// Implementation of the Admin class

#include <iostream>
#include <limits>    
#include "Admin.h"
#include "Library.h"
#include "Member.h"
#include "Librarian.h"
#include "PasswordUtil.h"
using namespace std;

// Constructor - calls the User (parent) constructor with role set to "Admin"
Admin::Admin(string u, string encodedPass, string n, string e)
    : User(u, encodedPass, n, e, "Admin") {}

// Admin menu - this OVERRIDES the pure virtual menu() from User (Polymorphism)
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

        // Input validation - if user types a letter instead of a number, handle it
        if (!(cin >> choice)) {
            cin.clear();  // Clear the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard the bad input
            cout << "Invalid input. Please enter a number.\n";
            continue;  
        }
        cin.ignore();  // Discard the leftover newline character after the number

        // Option 1 or 2: Create a new Member or Librarian account
        if (choice == 1 || choice == 2) {
            cout << "Username: "; getline(cin, input);
            // It check if the username is already taken
            if (library.findUser(input)) {
                cout << "Username already taken!\n";
                continue;
            }
            cout << "Password: "; getline(cin, input2);
            cout << "Full Name: "; getline(cin, input3);
            cout << "Email: "; getline(cin, input4);

            // Encode the password before storing it (for security)
            string encoded = PasswordUtil::encode(input2);
            if (choice == 1) {
                // "new Member" creates a Member on the heap - Library will delete it later
                library.addUser(new Member(input, encoded, input3, input4));
                cout << "Member account created.\n";
            } else {
                library.addUser(new Librarian(input, encoded, input3, input4));
                cout << "Librarian account created.\n";
            }
        }
        // Option 3: Remove a user account
        else if (choice == 3) {
            cout << "Username to remove: "; getline(cin, input);
            library.removeUser(input);  // Library handles the deletion
        }
        // Option 4: View all registered accounts
        else if (choice == 4) {
            cout << "\n--- All Accounts ---\n";
            // Loop through all users and show their details
            // user->getRole() calls the right function via the User pointer (Polymorphism)
            for (User* user : library.getUsers()) {
                cout << "  [" << user->getRole() << "] " << user->getUsername()
                     << " - " << user->getName() << " (" << user->getEmail() << ")\n";
            }
        }
        // Option 5: Change the maximum number of books a member can borrow
        else if (choice == 5) {
            int limit;
            cout << "New borrow limit: ";
            // Validate numeric input
            if (!(cin >> limit)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore();
            library.setBorrowLimit(limit);
            cout << "Borrow limit updated to " << limit << ".\n";
        }
        // Option 6: Change the daily penalty for late returns
        else if (choice == 6) {
            double penalty;
            cout << "New penalty per day ($): ";
            // Validate numeric input
            if (!(cin >> penalty)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }
            cin.ignore();
            library.setLatePenalty(penalty);
            cout << "Late penalty updated to $" << penalty << " per day.\n";
        }
        // Option 7: View all encoded (hashed) passwords
        else if (choice == 7) {
            cout << "\n--- Encoded Passwords ---\n";
            for (User* user : library.getUsers()) {
                cout << "  " << user->getUsername() << ": " << user->getPasswordHash() << "\n";
            }
            cout << "\nNote: To decode, use option 8 with the secret key from PasswordUtil.cpp\n";
        }
        // Option 8: Decode a password (requires the secret key)
        else if (choice == 8) {
            cout << "Enter secret key: "; getline(cin, input);
            // Verify the secret key matches before allowing decoding
            if (input == PasswordUtil::getSecretKey()) {
                cout << "Username to decode: "; getline(cin, input);
                User* user = library.findUser(input);
                if (user) {
                    // Decode the stored encoded password back to plain text
                    cout << "Password: " << PasswordUtil::decode(user->getPasswordHash()) << "\n";
                } else {
                    cout << "User not found.\n";
                }
            } else {
                cout << "Invalid secret key. Access denied.\n";
            }
        }

    } while (choice != 0);  // Keep showing the menu until user chooses 0 
}