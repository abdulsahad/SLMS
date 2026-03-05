#include "PasswordUtil.h"
#include <sstream>
#include <iomanip>
#include <cstdlib>

// ============================================================
// SECRET KEY for XOR cipher — Only the project owner who has
// access to this source file can decode stored passwords.
// Key: "SLMS_SecretKey_2026"
// ============================================================
const string PasswordUtil::SECRET_KEY = "SLMS_SecretKey_2026";

string PasswordUtil::encode(const string& password) {
    string xored = password;
    for (size_t i = 0; i < xored.size(); i++) {
        xored[i] = xored[i] ^ SECRET_KEY[i % SECRET_KEY.size()];
    }
    // Convert to hex string for safe storage and display
    stringstream ss;
    for (unsigned char c : xored) {
        ss << hex << setfill('0') << setw(2) << (int)c;
    }
    return ss.str();
}

string PasswordUtil::decode(const string& encoded) {
    // Convert hex back to bytes
    string raw = "";
    for (size_t i = 0; i < encoded.size(); i += 2) {
        string byteStr = encoded.substr(i, 2);
        char c = (char)strtol(byteStr.c_str(), nullptr, 16);
        raw += c;
    }
    // XOR with key to recover original password
    for (size_t i = 0; i < raw.size(); i++) {
        raw[i] = raw[i] ^ SECRET_KEY[i % SECRET_KEY.size()];
    }
    return raw;
}

bool PasswordUtil::verify(const string& input, const string& storedHash) {
    return encode(input) == storedHash;
}

string PasswordUtil::getSecretKey() {
    return SECRET_KEY;
}
