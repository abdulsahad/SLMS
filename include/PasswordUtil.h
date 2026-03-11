/* Uses XOR cipher to encode passwords so they are not stored
as plain text. The secret key is defined in PasswordUtil.cpp.*/
#ifndef PASSWORD_UTIL_H
#define PASSWORD_UTIL_H

#include <string>
using namespace std;

class PasswordUtil {
private:
    // The secret key used for XOR encoding — kept private for security
    // The actual value is defined in PasswordUtil.cpp
    static const string SECRET_KEY;

public:
    // Encodes a plain text password into a hex string using XOR cipher
    static string encode(const string& password);

    // Decodes an encoded password back to plain text (needs the secret key)
    static string decode(const string& encoded);

    // Checks if a plain text password matches a stored encoded password
    static bool verify(const string& input, const string& storedHash);

    // Returns the secret key (used by admin for password decoding)
    static string getSecretKey();
};

#endif
