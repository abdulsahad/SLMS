
// Uses XOR cipher to encode passwords into hex strings.
// XOR cipher: each character is XOR'd with a key character.
// XOR is reversible - XOR the encoded text with the same key
// to get the original password back.
#include "PasswordUtil.h"
#include <sstream>   
#include <iomanip>   
#include <cstdlib>   

// Anyone with this key and the encoded password can decode it
const string PasswordUtil::SECRET_KEY = "SLMS_SecretKey_2026";


string PasswordUtil::encode(const string& password) {
    string xored = password;
    for (size_t i = 0; i < xored.size(); i++) {
        xored[i] = xored[i] ^ SECRET_KEY[i % SECRET_KEY.size()];
    }
    stringstream ss;
    for (unsigned char c : xored) {
        ss << hex << setfill('0') << setw(2) << (int)c;
    }
    return ss.str();
}


string PasswordUtil::decode(const string& encoded) {
    string raw = "";
    for (size_t i = 0; i < encoded.size(); i += 2) {
        string byteStr = encoded.substr(i, 2);  
        char c = (char)strtol(byteStr.c_str(), nullptr, 16);  // Convert hex to a number
        raw += c;
    }
    for (size_t i = 0; i < raw.size(); i++) {
        raw[i] = raw[i] ^ SECRET_KEY[i % SECRET_KEY.size()];
    }
    return raw;
}

// Verifies a password by encoding the input and comparing with the stored hash
// Returns true if they match
bool PasswordUtil::verify(const string& input, const string& storedHash) {
    return encode(input) == storedHash;
}

// Returns the secret key - used by the admin's decode feature
string PasswordUtil::getSecretKey() {
    return SECRET_KEY;
}
