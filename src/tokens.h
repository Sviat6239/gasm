#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <cstdint>

using namespace std;

/**
 * Tokens structure defines the set of all possible signals the lexer can emit.
 */
struct Tokens {
    /**
     * Token enumeration represents the language's grammar elements.
     */
    enum Token {
        // Directives and configuration
        FORMAT,
        WIN_32,
        WIN_64,
        ELF32,
        ELF64,
        BIN,        // Pure binary format
        EFI,        // UEFI executable format
        ARCH,
        X86,
        AARCH64,
        ENTRY,
        DECLARE,

        // Identifiers and literals
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

        // Structural directives
        STRUCT,
        ENDSTRUCT,
        MACRO,
        ENDMACRO,

        // Control flow
        IF,
        ELSE,

        // Operators and punctuation
        ASSIGN,
        COLON,
        SEMICOLON,
        COMMA,
        STRING,
        NUMBER,
        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        LBRACKET,
        RBRACKET,
        LESS,
        GREATER,
        ERROR,

        // x86-64 / ARM64 instructions
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
        XOR,
        AND,
        OR,
        NOT,
        SHL,
        SHR,
        SAR,
        ROL,
        ROR,
        RET,
        INT,
        SYSCALL,
        LDR,
        STR,
        ORR,
        EOR,
        BIC,
        LSL,
        LSR,
        ASR,
        TST,
        B,
        BL_OP,
        BX_OP,
        ADR,
        SDIV,
        UDIV,
        BFI,
        UBFX,
        CBZ,
        CBNZ,
        LUI,
        AUIPC,
        LW,
        SW,
        LD,
        SD,
        ADDI,
        SLT,
        SLTI,
        JAL,
        JALR,
        BEQ,
        BNE,
        BLT,
        BGE,

        // Register names (x86-64 / ARM64)
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

        // RISC-V registers
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

        // Pseudo-instructions for RISC-V
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

        // Low-level / BIOS / UEFI specific operations
        OUT,
        IN,
        CLI,
        STI,
        HLT,
        LIDT,
        LGDT,
        SMSW,
        LMSW,
        INVLPG,
        WBINVD,
        RDMSR,
        WRMSR,
        RDTSC,
        CPUID,
        IRET,
        PUSHFD,
        POPFD,
        LAHF,
        SAHF,

        // UEFI / Protocol helpers
        STALL,
        RESET,
        ALLOCATE_PAGES,
        FREE_PAGES,
        GET_MEMORY_MAP,
        ALLOCATE_POOL,
        FREE_POOL,
        SET_WATCHDOG_TIMER,
        CONNECT_CONTROLLER,
        DISCONNECT_CONTROLLER,
        OPEN_PROTOCOL,
        CLOSE_PROTOCOL,
        LOCATE_HANDLE,
        LOCATE_DEVICE_PATH,
        INSTALL_PROTOCOL_INTERFACE,
        REINSTALL_PROTOCOL_INTERFACE,
        UNINSTALL_PROTOCOL_INTERFACE,
        HANDLE_PROTOCOL,
        REGISTER_PROTOCOL_NOTIFY,
        LOCATE_HANDLE_BUFFER,

        // Additional operations
        PRINT,
        CALL,
    };
};

/**
 * SymbolTable manages user-defined labels and global assembly metadata.
 */
struct SymbolTable {
    map<string, int> labels;    // Map of label names to their line locations
    string entryLabel;          // The name of the defined entry point (e.g., "_start")
};

struct TokenString {
    string text;
    size_t line;
};

struct Token {
    Tokens::Token type;
    string lexeme;
    size_t line;
};

struct IRNode {
    Tokens::Token type;
    string lexeme;
    size_t line;
};

enum class EmitMode {
    Ir,
    Binary,
};

struct CliOptions {
    string inputPath;
    string outputPath;
    EmitMode emitMode = EmitMode::Ir;
    bool showHelp = false;
    bool pickInput = false;
    bool listInputs = false;
};
