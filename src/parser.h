#pragma once

#include "tokens.h"
#include <vector>

using namespace std;

// Parser front-end: convert raw token strings from the lexer into typed
// `Token` objects that carry a token kind, lexeme, and source line.
// This module performs lightweight normalization only and does not
// perform full syntactic parsing — that is done later by IR/emit stages.
vector<Token> parse(const vector<TokenString> &rawTokens);
