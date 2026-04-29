#pragma once

#include "tokens.h"
#include <vector>
#include <string>

using namespace std;

static bool writeTextIr(const string& outputPath, const vector<Token>& tokens, const vector<IRNode>& ir, const SymbolTable& symbolTable);
static void writeUint32(ostream& out, uint32_t value);
static void writeString(ostream& out, const string& value);
static bool writeBinaryIrArtifact(const string& outputPath, const vector<IRNode>& ir, const SymbolTable& symbolTable);
