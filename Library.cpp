#include <iostream>
#include "Library.h"
using namespace std;

Library::Library() {
    books.push_back(Book("1984", "George Orwell"));
    books.push_back(Book("Dune", "Frank Herbert"));
    books.push_back(Book("Hamlet", "Shakespeare"));
    books.push_back(Book("Foundation", "Asimov"));
    books.push_back(Book("Clean Code", "Robert Martin"));
    books.push_back(Book("The Hobbit", "Tolkien"));
    books.push_back(Book("Dracula", "Bram Stoker"));
    books.push_back(Book("It", "Stephen King"));
    books.push_back(Book("Sapiens", "Harari"));
    books.push_back(Book("Algorithms", "CLRS"));
}

void Library::searchBook(string keyword) {
    for(Book &b : books) {
        if(b.getTitle().find(keyword) != string::npos ||
           b.getAuthor().find(keyword) != string::npos) {
            cout << b.getTitle() << " - " << b.getStatus() << endl;
        }
    }
}

bool Library::borrowBook(string title, string user) {
    for(Book &b : books) {
        if(b.getTitle() == title && b.getStatus() == "Available") {
            b.setStatus("Borrowed");
            b.setBorrower(user);
            return true;
        }
    }
    return false;
}

void Library::returnBook(string title) {
    for(Book &b : books) {
        if(b.getTitle() == title) {
            b.setStatus("Available");
            b.setBorrower("");
        }
    }
}