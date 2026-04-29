#pragma once

#include "tokens.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

static const unordered_map<string, Tokens::Token>& keywordTokens();
static Tokens::Token classifyToken(const string& token);
static vector<TokenString> lex(istream& code);
