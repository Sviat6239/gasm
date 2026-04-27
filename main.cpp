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
        ARCH,
        X86,
        AARCH64,
        ENTRY,
        DECLARE,
        IDENTIFIER,
        DB,
        DW,
        DD,
        DQ,
        INT8,
        INT16,
        INT32,
        INT64,
        UINT8,
        UINT16,
        UINT32,
        UINT64,
        FLOAT,
        DOUBLE,
        CHAR,
        STRUCT,
        ENDSTRUCT,
        MACRO,
        ENDMACRO,
        IF,
        ELSE,
        ASSIGN,
        COLON,
        SEMICOLON,
        COMMA,
        STRING,
        NUMBER,
        MOV,
        ADD,
        SUB,
        MUL,
        DIV,
        SQR,
        POW,
        CMP,
        JMP,
        JNZ,
        INC,
        DEC,
        RAX,
        RBX,
        RCX,
        RDX,
        RSP,
        RBP,
        RSI,
        RDI,
        R8,
        R9,
        R10,
        R11,
        R12,
        R13,
        R14,
        R15,
        EAX,
        EBX,
        ECX,
        EDX,
        ESP,
        EBP,
        ESI,
        EDI,
        R8D,
        R9D,
        R10D,
        R11D,
        R12D,
        R13D,
        R14D,
        R15D,
        AX,
        BX,
        CX,
        DX,
        SP,
        BP,
        SI,
        DI,
        R8W,
        R9W,
        R10W,
        R11W,
        R12W,
        R13W,
        R14W,
        R15W,
        AL,
        BL,
        CL,
        DL,
        AH,
        BH,
        CH,
        DH,
        SPL,
        BPL,
        SIL,
        DIL,
        R8B,
        R9B,
        R10B,
        R11B,
        R12B,
        R13B,
        R14B,
        R15B,
        CS,
        DS,
        ES,
        FS,
        GS,
        SS,
        RIP,
        EIP,
        IP,
        RFLAGS,
        EFLAGS,
        FLAGS,
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
            } else if (ch == ':' || ch == ';' || ch == ',' || ch == '=' || ch == '"' || ch == '<' || ch == '>' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}') {
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