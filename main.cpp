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

static bool isNumberToken(const string& token) {
    if (token.empty()) {
        return false;
    }
    size_t start = 0;
    if (token.front() == '-') {
        if (token.size() == 1) {
            return false;
        }
        start = 1;
    }
    for (size_t i = start; i < token.size(); ++i) {
        if (!isdigit(static_cast<unsigned char>(token[i]))) {
            return false;
        }
    }
    return true;
}

static bool isIdentifierStart(const string& token) {
    return !token.empty() && (isalpha(static_cast<unsigned char>(token.front())) || token.front() == '_');
}

static string toUpper(string value) {
    transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(toupper(ch));
    });
    return value;
}

static string toLowerCopy(string value) {
    transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
        return static_cast<char>(tolower(ch));
    });
    return value;
}

static const unordered_map<string, Tokens::Token>& keywordTokens() {
    static const unordered_map<string, Tokens::Token> kTokens = {
        {"format", Tokens::FORMAT},
        {"win32", Tokens::WIN_32},
        {"win64", Tokens::WIN_64},
        {"elf32", Tokens::ELF32},
        {"elf64", Tokens::ELF64},
        {"bin", Tokens::BIN},
        {"efi", Tokens::EFI},
        {"arch", Tokens::ARCH},
        {"x86", Tokens::X86},
        {"aarch64", Tokens::AARCH64},
        {"entry", Tokens::ENTRY},
        {"declare", Tokens::DECLARE},
        {"identifier", Tokens::IDENTIFIER},
        {"db", Tokens::DB},
        {"dw", Tokens::DW},
        {"dd", Tokens::DD},
        {"dq", Tokens::DQ},
        {"int8", Tokens::INT8},
        {"int16", Tokens::INT16},
        {"int32", Tokens::INT32},
        {"int64", Tokens::INT64},
        {"uint8", Tokens::UINT8},
        {"uint16", Tokens::UINT16},
        {"uint32", Tokens::UINT32},
        {"uint64", Tokens::UINT64},
        {"float", Tokens::FLOAT},
        {"double", Tokens::DOUBLE},
        {"char", Tokens::CHAR},
        {"struct", Tokens::STRUCT},
        {"endstruct", Tokens::ENDSTRUCT},
        {"macro", Tokens::MACRO},
        {"endmacro", Tokens::ENDMACRO},
        {"if", Tokens::IF},
        {"else", Tokens::ELSE},
        {"mov", Tokens::MOV},
        {"add", Tokens::ADD},
        {"sub", Tokens::SUB},
        {"mul", Tokens::MUL},
        {"div", Tokens::DIV},
        {"sqr", Tokens::SQR},
        {"pow", Tokens::POW},
        {"cmp", Tokens::CMP},
        {"jmp", Tokens::JMP},
        {"jnz", Tokens::JNZ},
        {"inc", Tokens::INC},
        {"dec", Tokens::DEC},
        {"xor", Tokens::XOR},
        {"and", Tokens::AND},
        {"or", Tokens::OR},
        {"not", Tokens::NOT},
        {"shl", Tokens::SHL},
        {"shr", Tokens::SHR},
        {"sar", Tokens::SAR},
        {"rol", Tokens::ROL},
        {"ror", Tokens::ROR},
        {"ret", Tokens::RET},
        {"int", Tokens::INT},
        {"syscall", Tokens::SYSCALL},
        {"ldr", Tokens::LDR},
        {"str", Tokens::STR},
        {"orr", Tokens::ORR},
        {"eor", Tokens::EOR},
        {"bic", Tokens::BIC},
        {"lsl", Tokens::LSL},
        {"lsr", Tokens::LSR},
        {"asr", Tokens::ASR},
        {"tst", Tokens::TST},
        {"b", Tokens::B},
        {"bl", Tokens::BL_OP},
        {"bx", Tokens::BX_OP},
        {"adr", Tokens::ADR},
        {"sdiv", Tokens::SDIV},
        {"udiv", Tokens::UDIV},
        {"bfi", Tokens::BFI},
        {"ubfx", Tokens::UBFX},
        {"cbz", Tokens::CBZ},
        {"cbnz", Tokens::CBNZ},
        {"lui", Tokens::LUI},
        {"auipc", Tokens::AUIPC},
        {"lw", Tokens::LW},
        {"sw", Tokens::SW},
        {"ld", Tokens::LD},
        {"sd", Tokens::SD},
        {"addi", Tokens::ADDI},
        {"slt", Tokens::SLT},
        {"slti", Tokens::SLTI},
        {"jal", Tokens::JAL},
        {"jalr", Tokens::JALR},
        {"beq", Tokens::BEQ},
        {"bne", Tokens::BNE},
        {"blt", Tokens::BLT},
        {"bge", Tokens::BGE},
        {"rax", Tokens::RAX},
        {"rbx", Tokens::RBX},
        {"rcx", Tokens::RCX},
        {"rdx", Tokens::RDX},
        {"rsp", Tokens::RSP},
        {"rbp", Tokens::RBP},
        {"rsi", Tokens::RSI},
        {"rdi", Tokens::RDI},
        {"r8", Tokens::R8},
        {"r9", Tokens::R9},
        {"r10", Tokens::R10},
        {"r11", Tokens::R11},
        {"r12", Tokens::R12},
        {"r13", Tokens::R13},
        {"r14", Tokens::R14},
        {"r15", Tokens::R15},
        {"eax", Tokens::EAX},
        {"ebx", Tokens::EBX},
        {"ecx", Tokens::ECX},
        {"edx", Tokens::EDX},
        {"esp", Tokens::ESP},
        {"ebp", Tokens::EBP},
        {"esi", Tokens::ESI},
        {"edi", Tokens::EDI},
        {"r8d", Tokens::R8D},
        {"r9d", Tokens::R9D},
        {"r10d", Tokens::R10D},
        {"r11d", Tokens::R11D},
        {"r12d", Tokens::R12D},
        {"r13d", Tokens::R13D},
        {"r14d", Tokens::R14D},
        {"r15d", Tokens::R15D},
        {"ax", Tokens::AX},
        {"bx", Tokens::BX},
        {"cx", Tokens::CX},
        {"dx", Tokens::DX},
        {"sp", Tokens::SP},
        {"bp", Tokens::BP},
        {"si", Tokens::SI},
        {"di", Tokens::DI},
        {"r8w", Tokens::R8W},
        {"r9w", Tokens::R9W},
        {"r10w", Tokens::R10W},
        {"r11w", Tokens::R11W},
        {"r12w", Tokens::R12W},
        {"r13w", Tokens::R13W},
        {"r14w", Tokens::R14W},
        {"r15w", Tokens::R15W},
        {"al", Tokens::AL},
        {"bl", Tokens::BL},
        {"cl", Tokens::CL},
        {"dl", Tokens::DL},
        {"ah", Tokens::AH},
        {"bh", Tokens::BH},
        {"ch", Tokens::CH},
        {"dh", Tokens::DH},
        {"spl", Tokens::SPL},
        {"bpl", Tokens::BPL},
        {"sil", Tokens::SIL},
        {"dil", Tokens::DIL},
        {"r8b", Tokens::R8B},
        {"r9b", Tokens::R9B},
        {"r10b", Tokens::R10B},
        {"r11b", Tokens::R11B},
        {"r12b", Tokens::R12B},
        {"r13b", Tokens::R13B},
        {"r14b", Tokens::R14B},
        {"r15b", Tokens::R15B},
        {"cs", Tokens::CS},
        {"ds", Tokens::DS},
        {"es", Tokens::ES},
        {"fs", Tokens::FS},
        {"gs", Tokens::GS},
        {"ss", Tokens::SS},
        {"rip", Tokens::RIP},
        {"eip", Tokens::EIP},
        {"ip", Tokens::IP},
        {"rflags", Tokens::RFLAGS},
        {"eflags", Tokens::EFLAGS},
        {"flags", Tokens::FLAGS},
        {"r0", Tokens::R0},
        {"r1", Tokens::R1},
        {"r2", Tokens::R2},
        {"r3", Tokens::R3},
        {"r4", Tokens::R4},
        {"r5", Tokens::R5},
        {"r6", Tokens::R6},
        {"r7", Tokens::R7},
        {"x0", Tokens::X0},
        {"x1", Tokens::X1},
        {"x2", Tokens::X2},
        {"x3", Tokens::X3},
        {"x4", Tokens::X4},
        {"x5", Tokens::X5},
        {"x6", Tokens::X6},
        {"x7", Tokens::X7},
        {"x8", Tokens::X8},
        {"x9", Tokens::X9},
        {"x10", Tokens::X10},
        {"x11", Tokens::X11},
        {"x12", Tokens::X12},
        {"x13", Tokens::X13},
        {"x14", Tokens::X14},
        {"x15", Tokens::X15},
        {"x16", Tokens::X16},
        {"x17", Tokens::X17},
        {"x18", Tokens::X18},
        {"x19", Tokens::X19},
        {"x20", Tokens::X20},
        {"x21", Tokens::X21},
        {"x22", Tokens::X22},
        {"x23", Tokens::X23},
        {"x24", Tokens::X24},
        {"x25", Tokens::X25},
        {"x26", Tokens::X26},
        {"x27", Tokens::X27},
        {"x28", Tokens::X28},
        {"x29", Tokens::X29},
        {"x30", Tokens::X30},
        {"w0", Tokens::W0},
        {"w1", Tokens::W1},
        {"w2", Tokens::W2},
        {"w3", Tokens::W3},
        {"w4", Tokens::W4},
        {"w5", Tokens::W5},
        {"w6", Tokens::W6},
        {"w7", Tokens::W7},
        {"w8", Tokens::W8},
        {"w9", Tokens::W9},
        {"w10", Tokens::W10},
        {"w11", Tokens::W11},
        {"w12", Tokens::W12},
        {"w13", Tokens::W13},
        {"w14", Tokens::W14},
        {"w15", Tokens::W15},
        {"w16", Tokens::W16},
        {"w17", Tokens::W17},
        {"w18", Tokens::W18},
        {"w19", Tokens::W19},
        {"w20", Tokens::W20},
        {"w21", Tokens::W21},
        {"w22", Tokens::W22},
        {"w23", Tokens::W23},
        {"w24", Tokens::W24},
        {"w25", Tokens::W25},
        {"w26", Tokens::W26},
        {"w27", Tokens::W27},
        {"w28", Tokens::W28},
        {"w29", Tokens::W29},
        {"w30", Tokens::W30},
        {"out", Tokens::OUT},
        {"in", Tokens::IN},
        {"cli", Tokens::CLI},
        {"sti", Tokens::STI},
        {"hlt", Tokens::HLT},
        {"lidt", Tokens::LIDT},
        {"lgdt", Tokens::LGDT},
        {"smsw", Tokens::SMSW},
        {"lmsw", Tokens::LMSW},
        {"invlpg", Tokens::INVLPG},
        {"wbinvd", Tokens::WBINVD},
        {"rdmsr", Tokens::RDMSR},
        {"wrmsr", Tokens::WRMSR},
        {"rdtsc", Tokens::RDTSC},
        {"cpuid", Tokens::CPUID},
        {"iret", Tokens::IRET},
        {"pushfd", Tokens::PUSHFD},
        {"popfd", Tokens::POPFD},
        {"lahf", Tokens::LAHF},
        {"sahf", Tokens::SAHF},
        {"stall", Tokens::STALL},
        {"reset", Tokens::RESET},
        {"allocate_pages", Tokens::ALLOCATE_PAGES},
        {"free_pages", Tokens::FREE_PAGES},
        {"get_memory_map", Tokens::GET_MEMORY_MAP},
        {"allocate_pool", Tokens::ALLOCATE_POOL},
        {"free_pool", Tokens::FREE_POOL},
        {"set_watchdog_timer", Tokens::SET_WATCHDOG_TIMER},
        {"connect_controller", Tokens::CONNECT_CONTROLLER},
        {"disconnect_controller", Tokens::DISCONNECT_CONTROLLER},
        {"open_protocol", Tokens::OPEN_PROTOCOL},
        {"close_protocol", Tokens::CLOSE_PROTOCOL},
        {"locate_handle", Tokens::LOCATE_HANDLE},
        {"locate_device_path", Tokens::LOCATE_DEVICE_PATH},
        {"install_protocol_interface", Tokens::INSTALL_PROTOCOL_INTERFACE},
        {"reinstall_protocol_interface", Tokens::REINSTALL_PROTOCOL_INTERFACE},
        {"uninstall_protocol_interface", Tokens::UNINSTALL_PROTOCOL_INTERFACE},
        {"handle_protocol", Tokens::HANDLE_PROTOCOL},
        {"register_protocol_notify", Tokens::REGISTER_PROTOCOL_NOTIFY},
        {"locate_handle_buffer", Tokens::LOCATE_HANDLE_BUFFER},
        {"print", Tokens::PRINT},
        {"call", Tokens::CALL},
    };
    return kTokens;
}

static Tokens::Token classifyToken(const string& token) {
    if (token.size() >= 2 && token.front() == '"' && token.back() == '"') {
        return Tokens::STRING;
    }
    if (isNumberToken(token)) {
        return Tokens::NUMBER;
    }

    if (token == ":") {
        return Tokens::COLON;
    }
    if (token == ";") {
        return Tokens::SEMICOLON;
    }
    if (token == ",") {
        return Tokens::COMMA;
    }
    if (token == "=") {
        return Tokens::ASSIGN;
    }
    if (token == "(") {
        return Tokens::LPAREN;
    }
    if (token == ")") {
        return Tokens::RPAREN;
    }
    if (token == "{") {
        return Tokens::LBRACE;
    }
    if (token == "}") {
        return Tokens::RBRACE;
    }
    if (token == "[") {
        return Tokens::LBRACKET;
    }
    if (token == "]") {
        return Tokens::RBRACKET;
    }
    if (token == "<") {
        return Tokens::LESS;
    }
    if (token == ">") {
        return Tokens::GREATER;
    }

    const auto& tokensMap = keywordTokens();
    auto it = tokensMap.find(token);
    if (it != tokensMap.end()) {
        return it->second;
    }

    if (isIdentifierStart(token)) {
        return Tokens::IDENTIFIER;
    }

    return Tokens::ERROR;
}

static vector<TokenString> lex(istream& code) {
    vector<TokenString> tokens;
    string line;
    size_t lineNumber = 0;

    while (getline(code, line)) {
        ++lineNumber;
        string current;
        bool inString = false;

        for (char ch : line) {
            if (inString) {
                current += ch;
                if (ch == '"') {
                    tokens.push_back({current, lineNumber});
                    current.clear();
                    inString = false;
                }
                continue;
            }

            if (ch == '"') {
                if (!current.empty()) {
                    tokens.push_back({current, lineNumber});
                    current.clear();
                }
                current += ch;
                inString = true;
                continue;
            }

            if (ch == '#') {
                if (!current.empty()) {
                    tokens.push_back({current, lineNumber});
                    current.clear();
                }
                break;
            }

            if (isspace(static_cast<unsigned char>(ch))) {
                if (!current.empty()) {
                    tokens.push_back({current, lineNumber});
                    current.clear();
                }
            } else if (ch == ':' || ch == ';' || ch == ',' || ch == '=' || ch == '<' || ch == '>' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}') {
                if (!current.empty()) {
                    tokens.push_back({current, lineNumber});
                    current.clear();
                }
                tokens.push_back({string(1, ch), lineNumber});
            } else {
                current += ch;
            }
        }

        if (!current.empty()) {
            if (inString) {
                cerr << "Unterminated string literal: " << current << endl;
                return {};
            }
            tokens.push_back({current, lineNumber});
        }

        if (inString) {
            cerr << "Unterminated string literal" << endl;
            return {};
        }
    }

    return tokens;
}

static vector<Token> parse(const vector<TokenString>& rawTokens) {
    vector<Token> parsed;
    parsed.reserve(rawTokens.size());

    for (const auto& raw : rawTokens) {
        Tokens::Token type = classifyToken(raw.text);
        string lexeme = raw.text;
        if (type == Tokens::STRING && raw.text.size() >= 2) {
            lexeme = raw.text.substr(1, raw.text.size() - 2);
        }
        parsed.push_back({type, lexeme, raw.line});
    }

    return parsed;
}

static vector<IRNode> buildIR(const vector<Token>& tokens, SymbolTable& symbolTable) {
    vector<IRNode> ir;
    ir.reserve(tokens.size());

    for (size_t i = 0; i < tokens.size(); ++i) {
        const auto& token = tokens[i];
        ir.push_back({token.type, token.lexeme, token.line});

        if (token.type == Tokens::ENTRY && i + 1 < tokens.size() && tokens[i + 1].type == Tokens::IDENTIFIER) {
            symbolTable.entryLabel = tokens[i + 1].lexeme;
        }

        if (token.type == Tokens::IDENTIFIER && i + 1 < tokens.size() && tokens[i + 1].type == Tokens::COLON) {
            symbolTable.labels[token.lexeme] = static_cast<int>(token.line);
        }
    }

    return ir;
}

static string displayName(const Token& token) {
    switch (token.type) {
        case Tokens::STRING:
            return "STRING";
        case Tokens::NUMBER:
            return "NUMBER";
        case Tokens::IDENTIFIER:
            return "IDENTIFIER";
        case Tokens::COLON:
            return "COLON";
        case Tokens::SEMICOLON:
            return "SEMICOLON";
        case Tokens::COMMA:
            return "COMMA";
        case Tokens::ASSIGN:
            return "ASSIGN";
        case Tokens::LPAREN:
            return "PARENTHESE";
        case Tokens::RPAREN:
            return "RIGHTHESE";
        case Tokens::LBRACE:
            return "LEFTHESE";
        case Tokens::RBRACE:
            return "RIGHTHESE";
        case Tokens::LBRACKET:
            return "LEFTHESE";
        case Tokens::RBRACKET:
            return "RIGHTHESE";
        case Tokens::LESS:
            return "LESS";
        case Tokens::GREATER:
            return "GREATER";
        case Tokens::BL_OP:
            return "BL_OP";
        case Tokens::BX_OP:
            return "BX_OP";
        case Tokens::ERROR:
            return "ERROR";
        default:
            return toUpper(token.lexeme);
    }
}


static string emitModeName(EmitMode mode) {
    return mode == EmitMode::Ir ? "ir" : "bin";
}

static bool parseEmitMode(const string& value, EmitMode& mode) {
    string normalized = toLowerCopy(value);
    if (normalized == "ir") {
        mode = EmitMode::Ir;
        return true;
    }
    if (normalized == "bin" || normalized == "binary") {
        mode = EmitMode::Binary;
        return true;
    }
    return false;
}

static filesystem::path projectRoot() {
    filesystem::path current = filesystem::current_path();
    for (int depth = 0; depth < 6; ++depth) {
        if (filesystem::exists(current / "index.asm") || filesystem::exists(current / "examples")) {
            return current;
        }
        if (!current.has_parent_path()) {
            break;
        }
        current = current.parent_path();
    }
    return filesystem::current_path();
}

static vector<filesystem::path> discoverInputs(const filesystem::path& root) {
    vector<filesystem::path> inputs;
    if (filesystem::exists(root / "index.asm")) {
        inputs.push_back(root / "index.asm");
    }

    filesystem::path examplesDir = root / "examples";
    if (!filesystem::exists(examplesDir)) {
        return inputs;
    }

    error_code ec;
    for (filesystem::recursive_directory_iterator it(examplesDir, ec), end; it != end && !ec; it.increment(ec)) {
        if (it->is_regular_file() && toLowerCopy(it->path().extension().string()) == ".asm") {
            inputs.push_back(it->path());
        }
    }

    sort(inputs.begin(), inputs.end());
    return inputs;
}

static void printUsage(const string& exeName, const filesystem::path& root) {
    cout << "Usage:\n"
         << "  " << exeName << " [input.asm] [--emit ir|bin] [--output FILE]\n"
         << "  " << exeName << " --input input.asm --emit ir|bin --output FILE\n"
         << "  " << exeName << " --pick\n"
         << "  " << exeName << " --list-inputs\n\n"
         << "Options:\n"
         << "  -h, --help           Show this help\n"
         << "  -i, --input PATH     Source file to compile\n"
         << "  -e, --emit MODE      Output mode: ir or bin\n"
         << "  -o, --output FILE    Output file path\n"
         << "      --pick           Choose input file interactively\n"
         << "      --list-inputs    List discovered .asm files\n\n"
         << "Defaults:\n"
         << "  input  -> index.asm if present\n"
         << "  emit   -> ir\n"
         << "  output -> input file with .ir or .bin extension\n\n"
         << "Detected project root: " << root.string() << endl;
}

static void printInputList(const vector<filesystem::path>& inputs) {
    if (inputs.empty()) {
        cout << "No .asm files found.\n";
        return;
    }

    cout << "Available inputs:\n";
    for (size_t i = 0; i < inputs.size(); ++i) {
        cout << "  [" << (i + 1) << "] " << inputs[i].string() << '\n';
    }
}

static bool parseArguments(int argc, char* argv[], CliOptions& options, string& error) {
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            options.showHelp = true;
            continue;
        }
        if (arg == "-i" || arg == "--input") {
            if (i + 1 >= argc) {
                error = "Missing value for --input";
                return false;
            }
            options.inputPath = argv[++i];
            continue;
        }
        if (arg == "-e" || arg == "--emit") {
            if (i + 1 >= argc) {
                error = "Missing value for --emit";
                return false;
            }
            if (!parseEmitMode(argv[++i], options.emitMode)) {
                error = "Unsupported --emit value. Use 'ir' or 'bin'.";
                return false;
            }
            continue;
        }
        if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                error = "Missing value for --output";
                return false;
            }
            options.outputPath = argv[++i];
            continue;
        }
        if (arg == "--pick") {
            options.pickInput = true;
            continue;
        }
        if (arg == "--list-inputs") {
            options.listInputs = true;
            continue;
        }
        if (!arg.empty() && arg.front() != '-') {
            if (options.inputPath.empty()) {
                options.inputPath = arg;
                continue;
            }
            error = "Unexpected extra positional argument: " + arg;
            return false;
        }

        error = "Unknown argument: " + arg;
        return false;
    }

    return true;
}

static bool resolveInput(const filesystem::path& root, const string& requested, string& resolved) {
    filesystem::path direct(requested);
    if (filesystem::exists(direct)) {
        resolved = direct.string();
        return true;
    }

    filesystem::path fromRoot = root / direct;
    if (filesystem::exists(fromRoot)) {
        resolved = fromRoot.string();
        return true;
    }

    return false;
}

static bool chooseInputInteractively(const vector<filesystem::path>& inputs, string& chosen) {
    if (inputs.empty()) {
        cout << "Enter path to an .asm file: ";
        getline(cin, chosen);
        return !chosen.empty();
    }

    cout << "Select input file:\n";
    for (size_t i = 0; i < inputs.size(); ++i) {
        cout << "  [" << (i + 1) << "] " << inputs[i].string() << '\n';
    }
    cout << "  [0] Enter a custom path\n";
    cout << "Choice: ";

    string choiceText;
    getline(cin, choiceText);
    if (choiceText.empty()) {
        return false;
    }

    try {
        int choice = stoi(choiceText);
        if (choice == 0) {
            cout << "Path: ";
            getline(cin, chosen);
            return !chosen.empty();
        }
        if (choice < 1 || static_cast<size_t>(choice) > inputs.size()) {
            return false;
        }
        chosen = inputs[static_cast<size_t>(choice - 1)].string();
        return true;
    } catch (...) {
        return false;
    }
}

static string defaultOutputPath(const string& inputPath, EmitMode mode) {
    filesystem::path output(inputPath);
    output.replace_extension(mode == EmitMode::Ir ? ".ir" : ".bin");
    return output.string();
}

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

static void printEntryResolution(const SymbolTable& symbolTable) {
    if (symbolTable.entryLabel.empty()) {
        return;
    }

    cout << "\nEntry point resolution:\n";
    cout << "Target: " << symbolTable.entryLabel << '\n';
    auto entryIt = symbolTable.labels.find(symbolTable.entryLabel);
    if (entryIt != symbolTable.labels.end()) {
        cout << "Status: RESOLVED at line " << entryIt->second << '\n';
    } else {
        cout << "Status: UNRESOLVED (Error: Label not found)" << endl;
    }
}

int main(int argc, char* argv[]) {
    SymbolTable symbolTable;

    CliOptions options;
    string cliError;
    if (!parseArguments(argc, argv, options, cliError)) {
        cerr << cliError << endl;
        printUsage(argc > 0 ? argv[0] : "gasm", projectRoot());
        return 1;
    }

    filesystem::path root = projectRoot();
    vector<filesystem::path> inputs = discoverInputs(root);

    if (options.showHelp) {
        printUsage(argc > 0 ? argv[0] : "gasm", root);
        if (!inputs.empty()) {
            cout << '\n';
            printInputList(inputs);
        }
        return 0;
    }

    if (options.listInputs) {
        printInputList(inputs);
        return 0;
    }

    if (options.pickInput || options.inputPath.empty()) {
        if (!chooseInputInteractively(inputs, options.inputPath)) {
            cerr << "No input file selected." << endl;
            return 1;
        }
    }

    string resolvedInput;
    if (!resolveInput(root, options.inputPath, resolvedInput)) {
        cerr << "Failed to open source file: " << options.inputPath << endl;
        return 1;
    }

    ifstream code(resolvedInput);

    if (!code.is_open()) {
        cerr << "Failed to open source file: " << resolvedInput << endl;
        return 1;
    }

    // Phase 1: Lexer
    vector<TokenString> rawTokens = lex(code);
    if (rawTokens.empty()) {
        return 1;
    }

    // Phase 2: Parser
    vector<Token> parsedTokens = parse(rawTokens);

    // Phase 3: IR
    vector<IRNode> ir = buildIR(parsedTokens, symbolTable);

    string outputPath = options.outputPath.empty() ? defaultOutputPath(resolvedInput, options.emitMode) : options.outputPath;
    bool writeOk = false;
    if (options.emitMode == EmitMode::Ir) {
        writeOk = writeTextIr(outputPath, parsedTokens, ir, symbolTable);
    } else {
        writeOk = writeBinaryIrArtifact(outputPath, ir, symbolTable);
    }

    if (!writeOk) {
        return 1;
    }

    cout << "Compiled: " << resolvedInput << '\n';
    cout << "Emit mode: " << emitModeName(options.emitMode) << '\n';
    cout << "Output: " << outputPath << endl;
    printEntryResolution(symbolTable);

    return 0;
}
