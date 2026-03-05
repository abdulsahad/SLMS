#ifndef PASSWORD_UTIL_H
#define PASSWORD_UTIL_H

#include <string>
using namespace std;

class PasswordUtil {
private:
    // SECRET KEY — Only visible in source code (PasswordUtil.cpp)
    // Only the project owner who reads the source can see it
    static const string SECRET_KEY;

public:
    static string encode(const string& password);
    static string decode(const string& encoded);
    static bool verify(const string& input, const string& storedHash);
    static string getSecretKey();
};

#endif
