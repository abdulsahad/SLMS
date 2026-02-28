#include <iostream>
#include "Librarian.h"
using namespace std;

Librarian::Librarian(string u, string p) : User(u, p) {}

void Librarian::menu(Library &library) {
    cout << "\nLibrarian menu\n";
}