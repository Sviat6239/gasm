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
    string line;
    vector<string> tokens;

    while (getline(code, line)) {
        string current;

        for (char ch : line) {
            if (isspace(static_cast<unsigned char>(ch))) {
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
            } else if (ch == ':' || ch == ';' || ch == ',') {
                if (!current.empty()) {
                    tokens.push_back(current);
                    current.clear();
                }
                tokens.push_back(string(1, ch));
            } else {
                current += ch;
            }
        }

        if (!current.empty()) {
            tokens.push_back(current);
        }
    }

    for (const auto& t : tokens) {
        cout << "[" << t << "]";
    }

    return 0;
}