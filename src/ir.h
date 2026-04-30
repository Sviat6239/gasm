#pragma once

#include "tokens.h"
#include <vector>

using namespace std;

vector<IRNode> buildIR(const vector<Token>& tokens, SymbolTable& symbolTable);
