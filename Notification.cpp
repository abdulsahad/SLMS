#include <iostream>
#include "Notification.h"
using namespace std;

void Notification::sendConsoleAlert(const string& username, const string& message) {
    cout << "  [ALERT -> " << username << "] " << message << "\n";
}
