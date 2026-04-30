#pragma once

#include "tokens.h"
#include <vector>

using namespace std;

vector<Token> parse(const vector<TokenString>& rawTokens);
