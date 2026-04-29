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
        R0,
        R1,
        R2,
        R3,
        R4,
        R5,
        R6,
        R7,
        X0,
        X1,
        X2,
        X3,
        X4,
        X5,
        X6,
        X7,
        X8,
        X9,
        X10,
        X11,
        X12,
        X13,
        X14,
        X15,
        X16,
        X17,
        X18,
        X19,
        X20,
        X21,
        X22,
        X23,
        X24,
        X25,
        X26,
        X27,
        X28,
        X29,
        X30,
        W0,
        W1,
        W2,
        W3,
        W4,
        W5,
        W6,
        W7,
        W8,
        W9,
        W10,
        W11,
        W12,
        W13,
        W14,
        W15,
        W16,
        W17,
        W18,
        W19,
        W20,
        W21,
        W22,
        W23,
        W24,
        W25,
        W26,
        W27,
        W28,
        W29,
        W30,
        PRINT,
        CALL,
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
        bool inString = false;

        for (char ch : line) {
            if (inString) {
                current += ch;
                if (ch == '"') {
                    lineTokens.push_back(current);
                    current.clear();
                    inString = false;
                }
                continue;
            }

            if (ch == '"') {
                if (!current.empty()) {
                    lineTokens.push_back(current);
                    current.clear();
                }
                current += ch;
                inString = true;
                continue;
            }

            if (ch == '#') {
                if (!current.empty()) {
                    lineTokens.push_back(current);
                    current.clear();
                }
                break;
            }

            if (isspace(static_cast<unsigned char>(ch))) {
                if (!current.empty()) {
                    lineTokens.push_back(current);
                    current.clear();
                }
            } else if (ch == ':' || ch == ';' || ch == ',' || ch == '=' || ch == '<' || ch == '>' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}') {
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
            if (inString) {
                cerr << "Unterminated string literal: " << current << endl;
                return 1;
            }

            lineTokens.push_back(current);
        }

        if (inString) {
            cerr << "Unterminated string literal" << endl;
            return 1;
        }

        tokens.push_back(lineTokens);
    }

    for (const auto& lineTokens : tokens) {
        for (const auto& token : lineTokens) {
            if (token.front() == '"' && token.back() == '"') {
                cout << "STRING(" << token.substr(1, token.size() - 2) << ") ";
            } else if (isdigit(static_cast<unsigned char>(token.front())) || (token.front() == '-' && token.size() > 1 && isdigit(static_cast<unsigned char>(token[1])))) {
                cout << "NUMBER(" << token << ") ";
            }  else if (token.front() == '(') {
                cout << "PARENTHESE(" << token << ") ";
            } else if (token.front() == ')') {
                cout << "RIGHTHESE(" << token << ") ";
            } else if (token.front() == '{') {
                cout << "LEFTHESE(" << token << ") ";
            } else if (token.front() == '}') {
                cout << "RIGHTHESE(" << token << ") ";
            } else if (token.front() == '[') {
                cout << "LEFTHESE(" << token << ") ";
            } else if (token.front() == ']') {
                cout << "RIGHTHESE(" << token << ") ";
            } else if (token.front() == ':') {
                cout << "COLON(" << token << ") ";
            } else if (token.front() == ';') {
                cout << "SEMICOLON(" << token << ") ";
            } else if (token.front() == ',') {
                cout << "COMMA(" << token << ") ";
            } else if (token.front() == '=') {
                cout << "ASSIGN(" << token << ") ";
            } else if (token.front() == '<') {
                cout << "LESS(" << token << ") ";
            } else if (token.front() == '>') {
                cout << "GREATER(" << token << ") ";
            } else if (token == "format") {
                cout << "FORMAT(" << token << ") ";
            } else if (token == "print") {
                cout << "PRINT(" << token << ") ";
            } else if (token == "win32") {
                cout << "WIN32(" << token << ") ";
            } else if (token == "win64") {
                cout << "WIN64(" << token << ") ";
            } else if (token == "elf32") {
                cout << "ELF32(" << token << ") ";
            } else if (token == "elf64") {
                cout << "ELF64(" << token << ") ";
            } else if (token == "arch") {
                cout << "ARCH(" << token << ") ";
            } else if (token == "x86") {
                cout << "X86(" << token << ") ";
            } else if (token == "aarch64") {
                cout << "AARCH64(" << token << ") ";
            } else if (token == "entry") {
                cout << "ENTRY(" << token << ") ";
            } else if (token == "declare") {
                cout << "DECLARE(" << token << ") ";
            } else if (token == "rax") {
                cout << "RAX(" << token << ") ";
            } else if (token == "rbx") {
                cout << "RBX(" << token << ") ";
            } else if (token == "rcx") {
                cout << "RCX(" << token << ") ";
            } else if (token == "rdx") {
                cout << "RDX(" << token << ") ";
            } else if (token == "rsp") {
                cout << "RSP(" << token << ") ";
            } else if (token == "rbp") {
                cout << "RBP(" << token << ") ";
            } else if (token == "rsi") {
                cout << "RSI(" << token << ") ";
            } else if (token == "rdi") {
                cout << "RDI(" << token << ") ";
            } else if (token == "r8") {
                cout << "R8(" << token << ") ";
            } else if (token == "r9") {
                cout << "R9(" << token << ") ";
            } else if (token == "r10") {
                cout << "R10(" << token << ") ";
            } else if (token == "r11") {
                cout << "R11(" << token << ") ";
            } else if (token == "r12") {
                cout << "R12(" << token << ") ";
            } else if (token == "r13") {
                cout << "R13(" << token << ") ";
            } else if (token == "r14") {
                cout << "R14(" << token << ") ";
            } else if (token == "r15") {
                cout << "R15(" << token << ") ";
            } else if (token == "rip") {
                cout << "RIP(" << token << ") ";
            } else if (token == "rflags") {
                cout << "RFLAGS(" << token << ") ";
            } else if (token == "eflags") {
                cout << "EFLAGS(" << token << ") ";
            } else if (token == "flags") {
                cout << "FLAGS(" << token << ") ";
            } else if (token  == "mov") {
                cout << "MOV(" << token << ") ";
            } else if (token == "add") {
                cout << "ADD(" << token << ") ";
            } else if (token == "sub") {
                cout << "SUB(" << token << ") ";
            } else if (token == "mul") {
                cout << "MUL(" << token << ") ";
            } else if (token == "div") {
                cout << "DIV(" << token << ") ";
            } else if (token == "sqr") {
                cout << "SQR(" << token << ") ";
            } else if (token == "pow") {
                cout << "POW(" << token << ") ";
            } else if (token == "cmp") {
                cout << "CMP(" << token << ") ";
            } else if (token == "jmp") {
                cout << "JMP(" << token << ") ";
            } else if (token == "jnz") {
                cout << "JNZ(" << token << ") ";
            } else if (token == "inc") {
                cout << "INC(" << token << ") ";
            } else if (token == "dec") {
                cout << "DEC(" << token << ") ";
            } else if (token == "call") {
                cout << "CALL(" << token << ") ";
            } else if (token == "else") {
                cout << "ELSE(" << token << ") ";
            } else if (token == "if") {
                cout << "IF(" << token << ") ";
            } else if (token == "macro") {
                cout << "MACRO(" << token << ") ";
            } else if (token == "endmacro") {
                cout << "ENDMACRO(" << token << ") ";
            } else if (token == "struct") {
                cout << "STRUCT(" << token << ") ";
            } else if (token == "endstruct") {
                cout << "ENDSTRUCT(" << token << ") ";
            } else if (token == "db") {
                cout << "DB(" << token << ") ";
            } else if (token == "dw") {
                cout << "DW(" << token << ") ";
            } else if (token == "dd") {
                cout << "DD(" << token << ") ";
            } else if (token == "dq") {
                cout << "DQ(" << token << ") ";
            } else if (token == "int8") {
                cout << "INT8(" << token << ") ";
            } else if (token == "int16") {
                cout << "INT16(" << token << ") ";
            } else if (token == "int32") {
                cout << "INT32(" << token << ") ";
            } else if (token == "int64") {
                cout << "INT64(" << token << ") ";
            } else if (token == "uint8") {
                cout << "UINT8(" << token << ") ";
            } else if (token == "uint16") {
                cout << "UINT16(" << token << ") ";
            } else if (token == "uint32") {
                cout << "UINT32(" << token << ") ";
            } else if (token == "uint64") {
                cout << "UINT64(" << token << ") ";
            } else if (token == "float") {
                cout << "FLOAT(" << token << ") ";
            } else if (token == "double") {
                cout << "DOUBLE(" << token << ") ";
            } else if (token == "char") {
                cout << "CHAR(" << token << ") ";
            } else if (token == "w0") {
                cout << "W0(" << token << ") ";
            } else if (token == "w1") {
                cout << "W1(" << token << ") ";
            } else if (token == "w2") {
                cout << "W2(" << token << ") ";
            } else if (token == "w3") {
                cout << "W3(" << token << ") ";
            } else if (token == "w4") {
                cout << "W4(" << token << ") ";
            } else if (token == "w5") {
                cout << "W5(" << token << ") ";
            } else if (token == "w6") {
                cout << "W6(" << token << ") ";
            } else if (token == "w7") {
                cout << "W7(" << token << ") ";
            } else if (token == "w8") {
                cout << "W8(" << token << ") ";
            } else if (token == "w9") {
                cout << "W9(" << token << ") ";
            } else if (token == "w10") {
                cout << "W10(" << token << ") ";
            } else if (token == "w11") {
                cout << "W11(" << token << ") ";
            } else if (token == "w12") {
                cout << "W12(" << token << ") ";
            } else if (token == "w13") {
                cout << "W13(" << token << ") ";
            } else if (token == "w14") {
                cout << "W14(" << token << ") ";
            } else if (token == "w15") {
                cout << "W15(" << token << ") ";
            } else if (token == "w16") {
                cout << "W16(" << token << ") ";
            } else if (token == "w17") {
                cout << "W17(" << token << ") ";
            } else if (token == "w18") {
                cout << "W18(" << token << ") ";
            } else if (token == "w19") {
                cout << "W19(" << token << ") ";
            } else if (token == "w20") {
                cout << "W20(" << token << ") ";
            } else if (token == "w21") {
                cout << "W21(" << token << ") ";
            } else if (token == "w22") {
                cout << "W22(" << token << ") ";
            } else if (token == "w23") {
                cout << "W23(" << token << ") ";
            } else if (token == "w24") {
                cout << "W24(" << token << ") ";
            } else if (token == "w25") {
                cout << "W25(" << token << ") ";
            } else if (token == "w26") {
                cout << "W26(" << token << ") ";
            } else if (token == "w27") {
                cout << "W27(" << token << ") ";
            } else if (token == "w28") {
                cout << "W28(" << token << ") ";
            } else if (token == "w29") {
                cout << "W29(" << token << ") ";
            } else if (token == "w30") {
                cout << "W30(" << token << ") ";
            } else if (token == "x0") {
                cout << "X0(" << token << ") ";
            } else if (token == "x1") {
                cout << "X1(" << token << ") ";
            } else if (token == "x2") {
                cout << "X2(" << token << ") ";
            } else if (token == "x3") {
                cout << "X3(" << token << ") ";
            } else if (token == "x4") {
                cout << "X4(" << token << ") ";
            } else if (token == "x5") {
                cout << "X5(" << token << ") ";
            } else if (token == "x6") {
                cout << "X6(" << token << ") ";
            } else if (token == "x7") {
                cout << "X7(" << token << ") ";
            } else if (token == "x8") {
                cout << "X8(" << token << ") ";
            } else if (token == "x9") {
                cout << "X9(" << token << ") ";
            } else if (token == "x10") {
                cout << "X10(" << token << ") ";
            } else if (token == "x11") {
                cout << "X11(" << token << ") ";
            } else if (token == "x12") {
                cout << "X12(" << token << ") ";
            } else if (token == "x13") {
                cout << "X13(" << token << ") ";
            } else if (token == "x14") {
                cout << "X14(" << token << ") ";
            } else if (token == "x15") {
                cout << "X15(" << token << ") ";
            } else if (token == "x16") {
                cout << "X16(" << token << ") ";
            } else if (token == "x17") {
                cout << "X17(" << token << ") ";
            } else if (token == "x18") {
                cout << "X18(" << token << ") ";
            } else if (token == "x19") {
                cout << "X19(" << token << ") ";
            } else if (token == "x20") {
                cout << "X20(" << token << ") ";
            } else if (token == "x21") {
                cout << "X21(" << token << ") ";
            } else if (token == "x22") {
                cout << "X22(" << token << ") ";
            } else if (token == "x23") {
                cout << "X23(" << token << ") ";
            } else if (token == "x24") {
                cout << "X24(" << token << ") ";
            } else if (token == "x25") {
                cout << "X25(" << token << ") ";
            } else if (token == "x26") {
                cout << "X26(" << token << ") ";
            } else if (token == "x27") {
                cout << "X27(" << token << ") ";
            } else if (token == "x28") {
                cout << "X28(" << token << ") ";
            } else if (token == "x29") {
                cout << "X29(" << token << ") ";
            } else if (token == "x30") {
                cout << "X30(" << token << ") ";
            } else if (token == "r0") {
                cout << "R0(" << token << ") ";
            } else if (token == "r1") {
                cout << "R1(" << token << ") ";
            } else if (token == "r2") {
                cout << "R2(" << token << ") ";
            } else if (token == "r3") {
                cout << "R3(" << token << ") ";
            } else if (token == "r4") {
                cout << "R4(" << token << ") ";
            } else if (token == "r5") {
                cout << "R5(" << token << ") ";
            } else if (token == "r6") {
                cout << "R6(" << token << ") ";
            } else if (token == "r7") {
                cout << "R7(" << token << ") ";
            } else if (isalpha(static_cast<unsigned char>(token.front())) || token.front() == '_') {
                cout << "IDENTIFIER(" << token << ") ";
            } else {
                cout << "ERROR(" << token << ") ";
            }
        }
        cout << endl;
    }

    return 0;
}