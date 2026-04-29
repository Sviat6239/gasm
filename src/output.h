#pragma once

#include "tokens.h"
#include <vector>
#include <string>

using namespace std;

bool writeTextIr(const string& outputPath, const vector<Token>& tokens, const vector<IRNode>& ir, const SymbolTable& symbolTable);
void writeUint32(ostream& out, uint32_t value);
void writeString(ostream& out, const string& value);
bool writeBinaryIrArtifact(const string& outputPath, const vector<IRNode>& ir, const SymbolTable& symbolTable);
