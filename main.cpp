#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

    vector<string> codeParts;
    vector<string> codeLines;

    string codeLine;

    ifstream code("index.asm");

    while (getline(code, codeLine, ' ')) {
        codeParts.push_back(codeLine);
    }

    for (int i = 0; i < codeParts.size(); i++) {
        cout << codeParts[i] << endl;
    }

    return 0;
}