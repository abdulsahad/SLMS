#include <iostream>
#include "Member.h"
using namespace std;

Member::Member(string u, string p) : User(u, p) {}

void Member::menu(Library &library) {
    cout << "\nMember menu (placeholder)\n";
}