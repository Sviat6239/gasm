#pragma once

#include "ast.h"
#include "tokens.h"
#include <vector>

using namespace std;

vector<IRNode> buildIR(const AstProgram &program, SymbolTable &symbolTable);
