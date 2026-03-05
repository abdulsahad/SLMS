#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"
using namespace std;

class User;

class Library {
private:
    vector<Book> books;
    vector<User*> users;
    int borrowLimit;
    double latePenalty;  // Penalty per day for late returns

public:
    Library();
    ~Library();

    // Book management
    void addBook(const Book& book);
    void removeBook(const string& title);
    void updateBook(const string& oldTitle, const string& newTitle, const string& newAuthor);
    void searchBook(const string& keyword);
    void showAllBooks();
    Book* findBook(const string& title);

    // Borrow / Return / Reserve
    bool borrowBook(const string& title, const string& username);
    double returnBook(const string& title, const string& username);
    bool reserveBook(const string& title, const string& username);
    void checkReservationExpiry();
    void showReservations();

    // Reports
    void showOverdueReport();

    // Library settings
    void setBorrowLimit(int limit);
    int getBorrowLimit() const;
    void setLatePenalty(double penalty);
    double getLatePenalty() const;

    // User management
    void addUser(User* user);
    void removeUser(const string& username);
    vector<User*>& getUsers();
    User* findUser(const string& username);

    // Notifications
    void checkNotifications(const string& username, const string& email);
    void sendAllOverdueNotifications();
};

#endif