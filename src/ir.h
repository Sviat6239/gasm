#pragma once

#include "tokens.h"
#include <vector>

using namespace std;

static vector<IRNode> buildIR(const vector<Token>& tokens, SymbolTable& symbolTable);
