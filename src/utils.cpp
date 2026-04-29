#include "utils.h"
#include <cctype>
#include <algorithm>

using namespace std;

bool isNumberToken(const string& token) {
    if (token.empty()) {
        return false;
    }
    size_t start = 0;
    if (token.front() == '-') {
        if (token.size() == 1) {
            return false;
        }
        start = 1;
    }
    for (size_t i = start; i < token.size(); ++i) {
        if (!isdigit(static_cast<unsigned char>(token[i]))) {
            return false;
        }
    }
    return true;
}

bool isIdentifierStart(const string& token) {
    return !token.empty() && (isalpha(static_cast<unsigned char>(token.front())) || token.front() == '_');
}

string toUpper(string value) {
    transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(toupper(ch));
    });
    return value;
}

string toLowerCopy(string value) {
    transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(tolower(ch));
    });
    return value;
}
