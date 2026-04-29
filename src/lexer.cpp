#include "lexer.h"
#include "utils.h"
#include <iostream>
#include <cctype>

using namespace std;

const unordered_map<string, Tokens::Token>& keywordTokens() {
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

Tokens::Token classifyToken(const string& token) {
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

vector<TokenString> lex(istream& code) {
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
