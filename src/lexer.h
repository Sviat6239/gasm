#pragma once

#include "tokens.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

const unordered_map<string, Tokens::Token>& keywordTokens();
Tokens::Token classifyToken(const string& token);
vector<TokenString> lex(istream& code);
