#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Book.h"
#include "User.h"
#include "Member.h"
#include "Librarian.h"
#include "Admin.h"
#include "Library.h"

using namespace std;

int main() {
    vector<Book> books;
    Library library;

    vector<User*> users;
    users.push_back(new Admin("admin", "admin123"));
    users.push_back(new Librarian("librarian", "lib123"));
    users.push_back(new Member("member1", "mem123"));
    users.push_back(new Member("member2", "mem123"));
    users.push_back(new Member("member3", "mem123"));

    cout << "System initialized...\n";

    int choice;
    string username, password;

    do {
        cout << "\n===== SMART LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Login\n";
        cout << "0. Exit\n";
        cout << "Select option: ";
        cin >> choice;

        if(choice == 1) {
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            bool found = false;
            for(User* user : users) {
                if(user->login(username, password)) {
                    cout << "Login successful!\n";
                    user->menu(library); 
                    found = true; 
                    break;
                }
            }
            if(!found) {
                cout << "Invalid credentials!\n";
            }
        }

    } while(choice != 0);

    return 0;
}