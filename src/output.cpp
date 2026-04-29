#include "output.h"
#include "symbols.h"
#include <iostream>
#include <fstream>

using namespace std;

static bool writeTextIr(const string& outputPath, const vector<Token>& tokens, const vector<IRNode>& ir, const SymbolTable& symbolTable) {
    ofstream out(outputPath);
    if (!out.is_open()) {
        cerr << "Failed to open output file: " << outputPath << endl;
        return false;
    }

    out << "; GASM intermediate representation\n";
    out << "; mode: textual ir\n\n";

    out << "[tokens]\n";
    for (const auto& token : tokens) {
        out << token.line << '\t' << displayName(token) << '\t' << token.lexeme << '\n';
    }

    out << "\n[ir]\n";
    for (const auto& node : ir) {
        Token temp{node.type, node.lexeme, node.line};
        out << node.line << '\t' << displayName(temp) << '\t' << node.lexeme << '\n';
    }

    out << "\n[symbols]\n";
    if (!symbolTable.entryLabel.empty()) {
        out << "entry\t" << symbolTable.entryLabel << '\n';
    }
    for (const auto& pair : symbolTable.labels) {
        out << "label\t" << pair.first << '\t' << pair.second << '\n';
    }

    return true;
}

static void writeUint32(ostream& out, uint32_t value) {
    out.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

static void writeString(ostream& out, const string& value) {
    writeUint32(out, static_cast<uint32_t>(value.size()));
    out.write(value.data(), static_cast<streamsize>(value.size()));
}

static bool writeBinaryIrArtifact(const string& outputPath, const vector<IRNode>& ir, const SymbolTable& symbolTable) {
    ofstream out(outputPath, ios::binary);
    if (!out.is_open()) {
        cerr << "Failed to open output file: " << outputPath << endl;
        return false;
    }

    const char magic[4] = {'G', 'A', 'S', 'M'};
    out.write(magic, sizeof(magic));
    writeUint32(out, 1);
    writeUint32(out, static_cast<uint32_t>(ir.size()));
    writeUint32(out, static_cast<uint32_t>(symbolTable.labels.size()));
    writeString(out, symbolTable.entryLabel);

    for (const auto& node : ir) {
        writeUint32(out, static_cast<uint32_t>(node.type));
        writeUint32(out, static_cast<uint32_t>(node.line));
        writeString(out, node.lexeme);
    }

    for (const auto& pair : symbolTable.labels) {
        writeString(out, pair.first);
        writeUint32(out, static_cast<uint32_t>(pair.second));
    }

    return true;
}
