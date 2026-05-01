#pragma once

#include "tokens.h"
#include <ostream>

using namespace std;

AstProgram buildAst(const vector<Token> &tokens);
void writeAst(ostream &out, const AstProgram &program);