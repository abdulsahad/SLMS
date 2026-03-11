// Library.h - The main system class that holds all books and users
// This is the "brain" of the program - it manages everything:
// books, users, borrowing, reservations, notifications, reports.

#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>   // For dynamic arrays (lists of books and users)
#include <string>
#include "Book.h"   
using namespace std;

class User;  

class Library {
private:
    // Private data - only Library's own functions can access these (Encapsulation)
    vector<Book> books;       
    vector<User*> users;      
    int borrowLimit;          
    double latePenalty;       

public:
    Library();   // Constructor — sets up the library with default books and settings
    ~Library();  // Destructor — cleans up (deletes) all user pointers to prevent memory leaks

    
    void addBook(const Book& book);       
    void removeBook(const string& title); 
    void updateBook(const string& oldTitle, const string& newTitle, const string& newAuthor);
    void searchBook(const string& keyword);  
    void showAllBooks();                     
    Book* findBook(const string& title);     

   
    bool borrowBook(const string& title, const string& username);    
    double returnBook(const string& title, const string& username);  
    bool reserveBook(const string& title, const string& username);   
    void checkReservationExpiry();  
    void showReservations();        

    
    void showOverdueReport();  

    
    void setBorrowLimit(int limit);
    int getBorrowLimit() const;
    void setLatePenalty(double penalty);
    double getLatePenalty() const;

    
    void addUser(User* user);                
    void removeUser(const string& username); 
    vector<User*>& getUsers();               
    User* findUser(const string& username);  

    
    void checkNotifications(const string& username, const string& email);  
    void sendAllOverdueNotifications();  
};

#endif