#include "parser.h"
#include "lexer.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<Token> parse(const vector<TokenString>& rawTokens) {
    vector<Token> parsed;
    parsed.reserve(rawTokens.size());

    for (const auto& raw : rawTokens) {
        Tokens::Token type = classifyToken(raw.text);
        string lexeme = raw.text;
        if (type == Tokens::STRING && raw.text.size() >= 2) {
            lexeme = raw.text.substr(1, raw.text.size() - 2);
        }
        parsed.push_back({type, lexeme, raw.line});
    }

    return parsed;
}
