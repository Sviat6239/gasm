#pragma once

#include "tokens.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Lexer public interface
// - `keywordTokens()` returns the mapping of language keywords to token kinds
// - `classifyToken()` maps a single lexeme string to a `Tokens::Token` enum
// - `lex()` tokenizes an input stream into `TokenString` items
const unordered_map<string, Tokens::Token> &keywordTokens();
Tokens::Token classifyToken(const string &token);
vector<TokenString> lex(istream &code);
