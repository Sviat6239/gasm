#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

struct Tokens {
    enum Token {
        FORMAT,
        WIN32,
        WIN64,
        ELF32,
        ELF64,
        DECLARE,
        IDENTIFIER,
        DB,
        DW,
        DD,
        DQ,
        ASSIGN,
        COLON,
        SEMICOLON,
        COMMA,
        STRING,
        NUMBER,
        MOV,
        ADD,
        RAX,
        RBX,
        RCX,
        RDX,
        EAX,
        EBX,
        ECX,
        EDX,
        AX,
        BX,
        CX,
        DX,
        PRINT,
    };
};



int main() {

    ifstream code("index.asm");

    if (!code.is_open()) {
        cerr << "Failed to open index.asm" << endl;
        return 1;
    }

    string line;
    vector<vector<string>> tokens;

    while (getline(code, line)) {
        vector<string> lineTokens;
        string current;

        for (char ch : line) {
            if (isspace(static_cast<unsigned char>(ch))) {
                if (!current.empty()) {
                    lineTokens.push_back(current);
                    current.clear();
                }
            } else if (ch == ':' || ch == ';' || ch == ',' || ch == '=') {
                if (!current.empty()) {
                    lineTokens.push_back(current);
                    current.clear();
                }
                lineTokens.emplace_back(1, ch);
            } else {
                current += ch;
            }
        }

        if (!current.empty()) {
            lineTokens.push_back(current);
        }

        tokens.push_back(lineTokens);
    }

    for (const auto& lineTokens : tokens) {
        for (const auto& token : lineTokens) {
            cout << '[' << token << "] ";
        }
        cout << endl;
    }

    return 0;
}