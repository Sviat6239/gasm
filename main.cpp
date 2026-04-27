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
        if (t == "format") {
            return Tokens::FORMAT;
        } else if (t == "win32") {
            return Tokens::WIN32;
        } else if (t == "win64") {
            return Tokens::WIN64;
        } else if (t == "elf32") {
            return Tokens::ELF32;
        } else if (t == "elf64") {
            return Tokens::ELF64;
        } else if (t == "declare") {
            return Tokens::DECLARE;
        } else if (t == "identifier") {
            return Tokens::IDENTIFIER;
        } else if (t == "db") {
            return Tokens::DB;
        } else if (t == "dw") {
            return Tokens::DW;
        } else if (t == "dd") {
            return Tokens::DD;
        } else if (t == "dq") {
            return Tokens::DQ;
        } else if (t == "=") {
            return Tokens::ASSIGN;
        } else if (t == ";") {
            return Tokens::COLON;
        } else if (t == ":") {
            return Tokens::SEMICOLON;
        } else if (t == ",") {
            return Tokens::COMMA;
        } else if (t == "string") {
            return Tokens::STRING;
        } else if (t == "number") {
            return Tokens::NUMBER;
        } else if (t == "mov") {
            return Tokens::MOV;
        } else if (t == "add") {
            return Tokens::ADD;
        } else if (t == "rax") {
            return Tokens::RAX;
        } else if (t == "rbx") {
            return Tokens::RBX;
        } else if (t == "rcx") {
            return Tokens::RCX;
        } else if (t == "rdx") {
            return Tokens::RDX;
        } else if (t == "eax") {
            return Tokens::EAX;
        } else if (t == "ebx") {
            return Tokens::EBX;
        } else if (t == "ecx") {
            return Tokens::ECX;
        } else if (t == "edx") {
            return Tokens::EDX;
        } else if (t == "ax") {
            return Tokens::AX;
        } else if (t == "bx") {
            return Tokens::BX;
        } else if (t == "cx") {
            return Tokens::CX;
        } else if (t == "dx") {
            return Tokens::DX;
        } else if (t == "print") {
            return Tokens::PRINT;
        }
    }

    return 0;
}