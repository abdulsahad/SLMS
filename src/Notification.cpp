
#include <iostream>
#include "Notification.h"
using namespace std;

// Static function - displays an alert message in the console
void Notification::sendConsoleAlert(const string& username, const string& message) {
    cout << "  [ALERT -> " << username << "] " << message << "\n";
}
