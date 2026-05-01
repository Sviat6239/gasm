#include "output.h"
#include "symbols.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

namespace
{

    string irKindName(Tokens::Token type)
    {
        switch (type)
        {
        case Tokens::FORMAT:
            return "FORMAT";
        case Tokens::ARCH:
            return "ARCH";
        case Tokens::ENTRY:
            return "ENTRY";
        case Tokens::DECLARE:
            return "DECLARE";
        case Tokens::IF:
            return "IF";
        case Tokens::ELSE:
            return "ELSE";
        case Tokens::MOV:
            return "MOV";
        case Tokens::ADD:
            return "ADD";
        case Tokens::SUB:
            return "SUB";
        case Tokens::MUL:
            return "MUL";
        case Tokens::DIV:
            return "DIV";
        case Tokens::SQR:
            return "SQR";
        case Tokens::POW:
            return "POW";
        case Tokens::CMP:
            return "CMP";
        case Tokens::JMP:
            return "JMP";
        case Tokens::JNZ:
            return "JNZ";
        case Tokens::INC:
            return "INC";
        case Tokens::DEC:
            return "DEC";
        case Tokens::XOR:
            return "XOR";
        case Tokens::AND:
            return "AND";
        case Tokens::OR:
            return "OR";
        case Tokens::NOT:
            return "NOT";
        case Tokens::SHL:
            return "SHL";
        case Tokens::SHR:
            return "SHR";
        case Tokens::SAR:
            return "SAR";
        case Tokens::ROL:
            return "ROL";
        case Tokens::ROR:
            return "ROR";
        case Tokens::RET:
            return "RET";
        case Tokens::INT:
            return "INT";
        case Tokens::SYSCALL:
            return "SYSCALL";
        case Tokens::LDR:
            return "LDR";
        case Tokens::STR:
            return "STR";
        case Tokens::ORR:
            return "ORR";
        case Tokens::EOR:
            return "EOR";
        case Tokens::BIC:
            return "BIC";
        case Tokens::LSL:
            return "LSL";
        case Tokens::LSR:
            return "LSR";
        case Tokens::ASR:
            return "ASR";
        case Tokens::TST:
            return "TST";
        case Tokens::B:
            return "B";
        case Tokens::BL_OP:
            return "BL";
        case Tokens::BX_OP:
            return "BX";
        case Tokens::ADR:
            return "ADR";
        case Tokens::SDIV:
            return "SDIV";
        case Tokens::UDIV:
            return "UDIV";
        case Tokens::BFI:
            return "BFI";
        case Tokens::UBFX:
            return "UBFX";
        case Tokens::CBZ:
            return "CBZ";
        case Tokens::CBNZ:
            return "CBNZ";
        case Tokens::LUI:
            return "LUI";
        case Tokens::AUIPC:
            return "AUIPC";
        case Tokens::LW:
            return "LW";
        case Tokens::SW:
            return "SW";
        case Tokens::LD:
            return "LD";
        case Tokens::SD:
            return "SD";
        case Tokens::ADDI:
            return "ADDI";
        case Tokens::SLT:
            return "SLT";
        case Tokens::SLTI:
            return "SLTI";
        case Tokens::JAL:
            return "JAL";
        case Tokens::JALR:
            return "JALR";
        case Tokens::BEQ:
            return "BEQ";
        case Tokens::BNE:
            return "BNE";
        case Tokens::BLT:
            return "BLT";
        case Tokens::BGE:
            return "BGE";
        case Tokens::PRINT:
            return "PRINT";
        case Tokens::CALL:
            return "CALL";
        default:
            return "UNKNOWN";
        }
    }

} // namespace

bool writeTextIr(const string &outputPath, const vector<Token> &tokens, const AstProgram &ast, const vector<IRNode> &ir, const SymbolTable &symbolTable)
{
    ofstream out(outputPath);
    if (!out.is_open())
    {
        cerr << "Failed to open output file: " << outputPath << endl;
        return false;
    }

    out << "; GASM intermediate representation\n";
    out << "; mode: textual ir\n\n";

    out << "[tokens]\n";
    for (const auto &token : tokens)
    {
        out << token.line << '\t' << displayName(token) << '\t' << token.lexeme << '\n';
    }

    out << "\n";
    writeAst(out, ast);

    out << "\n[ir]\n";
    for (const auto &node : ir)
    {
        out << node.line << '\t' << irKindName(node.type) << '\t' << node.lexeme << '\n';
    }

    out << "\n[symbols]\n";
    if (!symbolTable.entryLabel.empty())
    {
        out << "entry\t" << symbolTable.entryLabel << '\n';
    }
    for (const auto &pair : symbolTable.labels)
    {
        out << "label\t" << pair.first << '\t' << pair.second << '\n';
    }

    return true;
}

void writeUint32(ostream &out, uint32_t value)
{
    out.write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void writeString(ostream &out, const string &value)
{
    writeUint32(out, static_cast<uint32_t>(value.size()));
    out.write(value.data(), static_cast<streamsize>(value.size()));
}

bool writeBinaryIrArtifact(const string &outputPath, const vector<IRNode> &ir, const SymbolTable &symbolTable)
{
    ofstream out(outputPath, ios::binary);
    if (!out.is_open())
    {
        cerr << "Failed to open output file: " << outputPath << endl;
        return false;
    }

    const char magic[4] = {'G', 'A', 'S', 'M'};
    out.write(magic, sizeof(magic));
    writeUint32(out, 1);
    writeUint32(out, static_cast<uint32_t>(ir.size()));
    writeUint32(out, static_cast<uint32_t>(symbolTable.labels.size()));
    writeString(out, symbolTable.entryLabel);

    for (const auto &node : ir)
    {
        writeUint32(out, static_cast<uint32_t>(node.type));
        writeUint32(out, static_cast<uint32_t>(node.line));
        writeString(out, node.lexeme);
    }

    for (const auto &pair : symbolTable.labels)
    {
        writeString(out, pair.first);
        writeUint32(out, static_cast<uint32_t>(pair.second));
    }

    return true;
}
