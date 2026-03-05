#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
using namespace std;

class Notification {
public:
    static void sendConsoleAlert(const string& username, const string& message);
};

#endif
