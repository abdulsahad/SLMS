#include <iostream>
#include "Admin.h"
using namespace std;

Admin::Admin(string u, string p) : User(u, p) {}

void Admin::menu(Library &library) {
    cout << "\nAdmin menu\n";
}