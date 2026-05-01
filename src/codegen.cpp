#include "codegen.h"
#include "ir.h"

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <limits>
#include <optional>
#include <unordered_map>
#include <vector>

using namespace std;

namespace
{

    // Compact register metadata used by the selector and encoders.
    // `code` is the low 3-bit register index and `rex` marks R8-R15.

    struct X86RegInfo
    {
        uint8_t code = 0;
        bool rex = false;
        uint8_t width = 0;
    };

    enum class X86OperandKind
    {
        Invalid,
        Register,
        Immediate,
        Memory,
    };

    enum class X86SelectionKind
    {
        Invalid,
        RegReg,
        RegImm64,
        RegImm32,
        RegMem,
        MemReg,
    };

    struct X86MemoryAddress
    {
        optional<X86RegInfo> base;
        optional<X86RegInfo> index;
        uint8_t scale = 1;
        int64_t displacement = 0;
        bool hasDisplacement = false;
    };

    struct X86Operand
    {
        X86OperandKind kind = X86OperandKind::Invalid;
        X86RegInfo reg;
        int64_t immediate = 0;
        X86MemoryAddress memory;
        string text;
    };

    struct X86Selection
    {
        X86SelectionKind kind = X86SelectionKind::Invalid;
        X86Operand dst;
        X86Operand src;
    };

    std::optional<X86RegInfo> decodeX86Reg(Tokens::Token token);

    // Split the raw IR operand text on commas while respecting nested
    // brackets, so memory expressions like `[rbp+rsi*4-8]` stay intact.
    string trimCopy(const string &value)
    {
        size_t start = 0;
        while (start < value.size() && isspace(static_cast<unsigned char>(value[start])))
        {
            ++start;
        }

        size_t end = value.size();
        while (end > start && isspace(static_cast<unsigned char>(value[end - 1])))
        {
            --end;
        }

        return value.substr(start, end - start);
    }

    string removeWhitespaceCopy(const string &value)
    {
        string compact;
        compact.reserve(value.size());
        for (char ch : value)
        {
            if (!isspace(static_cast<unsigned char>(ch)))
            {
                compact += ch;
            }
        }
        return compact;
    }

    string toLowerAscii(string value)
    {
        transform(value.begin(), value.end(), value.begin(), [](unsigned char ch)
                  { return static_cast<char>(tolower(ch)); });
        return value;
    }

    bool parseSignedInteger(const string &value, int64_t &parsed)
    {
        if (value.empty())
        {
            return false;
        }

        errno = 0;
        char *end = nullptr;
        long long numeric = strtoll(value.c_str(), &end, 0);
        if (errno != 0 || end == value.c_str() || *end != '\0')
        {
            return false;
        }

        parsed = static_cast<int64_t>(numeric);
        return true;
    }

    bool parseScale(const string &value, uint8_t &scale)
    {
        int64_t numeric = 0;
        if (!parseSignedInteger(value, numeric))
        {
            return false;
        }

        if (numeric != 1 && numeric != 2 && numeric != 4 && numeric != 8)
        {
            return false;
        }

        scale = static_cast<uint8_t>(numeric);
        return true;
    }

    vector<string> splitOperands(const string &text)
    {
        vector<string> operands;
        string current;
        int bracketDepth = 0;
        int parenDepth = 0;
        int braceDepth = 0;

        for (char ch : text)
        {
            if (ch == ',' && bracketDepth == 0 && parenDepth == 0 && braceDepth == 0)
            {
                operands.push_back(trimCopy(current));
                current.clear();
                continue;
            }

            if (ch == '[')
            {
                ++bracketDepth;
            }
            else if (ch == ']' && bracketDepth > 0)
            {
                --bracketDepth;
            }
            else if (ch == '(')
            {
                ++parenDepth;
            }
            else if (ch == ')' && parenDepth > 0)
            {
                --parenDepth;
            }
            else if (ch == '{')
            {
                ++braceDepth;
            }
            else if (ch == '}' && braceDepth > 0)
            {
                --braceDepth;
            }

            current += ch;
        }

        if (!current.empty() || !operands.empty())
        {
            operands.push_back(trimCopy(current));
        }

        return operands;
    }

    // Decode plain x86-64 register names from text.
    optional<X86RegInfo> decodeX86RegName(const string &token)
    {
        static const unordered_map<string, X86RegInfo> registers = {
            {"rax", {0, false, 64}},
            {"rcx", {1, false, 64}},
            {"rdx", {2, false, 64}},
            {"rbx", {3, false, 64}},
            {"rsp", {4, false, 64}},
            {"rbp", {5, false, 64}},
            {"rsi", {6, false, 64}},
            {"rdi", {7, false, 64}},
            {"r8", {0, true, 64}},
            {"r9", {1, true, 64}},
            {"r10", {2, true, 64}},
            {"r11", {3, true, 64}},
            {"r12", {4, true, 64}},
            {"r13", {5, true, 64}},
            {"r14", {6, true, 64}},
            {"r15", {7, true, 64}},
        };

        string normalized = toLowerAscii(trimCopy(token));
        auto it = registers.find(normalized);
        if (it == registers.end())
        {
            return nullopt;
        }

        return it->second;
    }

    // Parse a small memory operand grammar: base, index*scale, and signed
    // displacement. This keeps the backend focused on the common forms.
    bool parseMemoryAddress(const string &text, X86MemoryAddress &address)
    {
        string body = trimCopy(text);
        if (body.size() < 2 || body.front() != '[' || body.back() != ']')
        {
            return false;
        }

        body = removeWhitespaceCopy(body.substr(1, body.size() - 2));
        if (body.empty())
        {
            return false;
        }

        int64_t displacement = 0;
        size_t position = 0;
        while (position < body.size())
        {
            int sign = 1;
            if (body[position] == '+')
            {
                ++position;
            }
            else if (body[position] == '-')
            {
                sign = -1;
                ++position;
            }

            if (position >= body.size())
            {
                return false;
            }

            size_t termStart = position;
            while (position < body.size() && body[position] != '+' && body[position] != '-')
            {
                ++position;
            }

            string term = body.substr(termStart, position - termStart);
            if (term.empty())
            {
                return false;
            }

            size_t star = term.find('*');
            if (star != string::npos)
            {
                string regText = term.substr(0, star);
                string scaleText = term.substr(star + 1);
                auto indexReg = decodeX86RegName(regText);
                uint8_t scale = 1;
                if (!indexReg || !parseScale(scaleText, scale) || indexReg->code == 4)
                {
                    return false;
                }

                if (address.index)
                {
                    return false;
                }

                address.index = indexReg;
                address.scale = scale;
                continue;
            }

            auto reg = decodeX86RegName(term);
            if (reg)
            {
                if (!address.base)
                {
                    address.base = reg;
                }
                else if (!address.index)
                {
                    address.index = reg;
                    address.scale = 1;
                }
                else
                {
                    return false;
                }
                continue;
            }

            int64_t numeric = 0;
            if (!parseSignedInteger(term, numeric))
            {
                return false;
            }

            displacement += sign * numeric;
            address.hasDisplacement = true;
        }

        if (displacement < numeric_limits<int32_t>::min() || displacement > numeric_limits<int32_t>::max())
        {
            return false;
        }

        address.displacement = displacement;
        return true;
    }

    // Reconstruct one operand from the compact IR text and the token hint.
    // The IR stays intentionally small, so the selection layer does the
    // operand classification here.
    optional<X86Operand> decodeOperand(const string &text, Tokens::Token hint)
    {
        X86Operand operand;
        operand.text = trimCopy(text);
        if (operand.text.empty())
        {
            return nullopt;
        }

        auto regFromHint = decodeX86Reg(hint);
        if (!regFromHint)
        {
            regFromHint = decodeX86RegName(operand.text);
        }
        if (regFromHint)
        {
            operand.kind = X86OperandKind::Register;
            operand.reg = *regFromHint;
            return operand;
        }

        if (hint == Tokens::LBRACKET || (operand.text.front() == '[' && operand.text.back() == ']'))
        {
            if (!parseMemoryAddress(operand.text, operand.memory))
            {
                return nullopt;
            }

            operand.kind = X86OperandKind::Memory;
            return operand;
        }

        int64_t immediate = 0;
        if (hint == Tokens::NUMBER || parseSignedInteger(operand.text, immediate))
        {
            operand.kind = X86OperandKind::Immediate;
            operand.immediate = immediate;
            return operand;
        }

        return nullopt;
    }

    // Build a full x86-64 REX prefix (0100WRXB). The backend always emits it
    // so the encoding stays explicit and easy to extend later.
    uint8_t buildRex(bool w, bool r, bool x, bool b)
    {
        uint8_t rex = 0x40;
        if (w)
        {
            rex |= 0x08;
        }
        if (r)
        {
            rex |= 0x04;
        }
        if (x)
        {
            rex |= 0x02;
        }
        if (b)
        {
            rex |= 0x01;
        }
        return rex;
    }

    void appendUint32(vector<uint8_t> &bytes, uint32_t value)
    {
        bytes.push_back(static_cast<uint8_t>(value & 0xFF));
        bytes.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
        bytes.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
        bytes.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
    }

    void appendUint64(vector<uint8_t> &bytes, uint64_t value)
    {
        for (int shift = 0; shift < 64; shift += 8)
        {
            bytes.push_back(static_cast<uint8_t>((value >> shift) & 0xFF));
        }
    }

    void appendInt8(vector<uint8_t> &bytes, int8_t value)
    {
        bytes.push_back(static_cast<uint8_t>(value));
    }

    void appendInt32(vector<uint8_t> &bytes, int32_t value)
    {
        appendUint32(bytes, static_cast<uint32_t>(value));
    }

    struct AddressEncoding
    {
        bool valid = false;
        bool usesSib = false;
        bool rexX = false;
        bool rexB = false;
        uint8_t modrm = 0;
        uint8_t sib = 0;
        vector<uint8_t> displacement;
    };

    // Encode the addressing part for a ModRM/SIB memory operand.
    AddressEncoding encodeAddress(const X86MemoryAddress &address, uint8_t regField)
    {
        AddressEncoding encoding;
        if (!address.base && !address.index && !address.hasDisplacement)
        {
            return encoding;
        }

        bool basePresent = address.base.has_value();
        bool indexPresent = address.index.has_value();
        bool usesSib = indexPresent || !basePresent || (basePresent && address.base->code == 4);
        encoding.usesSib = usesSib;
        encoding.rexX = indexPresent ? address.index->rex : false;
        encoding.rexB = basePresent ? address.base->rex : false;

        uint8_t scaleBits = 0;
        switch (address.scale)
        {
        case 1:
            scaleBits = 0;
            break;
        case 2:
            scaleBits = 1;
            break;
        case 4:
            scaleBits = 2;
            break;
        case 8:
            scaleBits = 3;
            break;
        default:
            return encoding;
        }

        uint8_t mod = 0;
        int64_t disp = address.displacement;

        if (!basePresent)
        {
            mod = 0;
            disp = address.hasDisplacement ? disp : 0;
        }
        else if (address.base->code == 5 && disp == 0)
        {
            mod = 1;
            disp = 0;
        }
        else if (!address.hasDisplacement || disp == 0)
        {
            mod = 0;
        }
        else if (disp >= -128 && disp <= 127)
        {
            mod = 1;
        }
        else
        {
            mod = 2;
        }

        uint8_t rm = 0;
        if (usesSib)
        {
            rm = 4;
            uint8_t indexCode = indexPresent ? address.index->code : 4;
            if (indexCode == 4 && indexPresent)
            {
                return encoding;
            }

            uint8_t baseCode = basePresent ? address.base->code : 5;
            encoding.sib = static_cast<uint8_t>((scaleBits << 6) | (indexCode << 3) | baseCode);
        }
        else
        {
            rm = basePresent ? address.base->code : 5;
        }

        encoding.modrm = static_cast<uint8_t>((mod << 6) | (regField << 3) | rm);

        if (mod == 1)
        {
            appendInt8(encoding.displacement, static_cast<int8_t>(disp));
        }
        else if (mod == 2 || !basePresent)
        {
            appendInt32(encoding.displacement, static_cast<int32_t>(disp));
        }

        encoding.valid = true;
        return encoding;
    }

    std::optional<X86RegInfo> decodeX86Reg(Tokens::Token token)
    {
        switch (token)
        {
        case Tokens::RAX:
            return X86RegInfo{0, false, 64};
        case Tokens::RCX:
            return X86RegInfo{1, false, 64};
        case Tokens::RDX:
            return X86RegInfo{2, false, 64};
        case Tokens::RBX:
            return X86RegInfo{3, false, 64};
        case Tokens::RSP:
            return X86RegInfo{4, false, 64};
        case Tokens::RBP:
            return X86RegInfo{5, false, 64};
        case Tokens::RSI:
            return X86RegInfo{6, false, 64};
        case Tokens::RDI:
            return X86RegInfo{7, false, 64};
        case Tokens::R8:
            return X86RegInfo{0, true, 64};
        case Tokens::R9:
            return X86RegInfo{1, true, 64};
        case Tokens::R10:
            return X86RegInfo{2, true, 64};
        case Tokens::R11:
            return X86RegInfo{3, true, 64};
        case Tokens::R12:
            return X86RegInfo{4, true, 64};
        case Tokens::R13:
            return X86RegInfo{5, true, 64};
        case Tokens::R14:
            return X86RegInfo{6, true, 64};
        case Tokens::R15:
            return X86RegInfo{7, true, 64};
        default:
            return std::nullopt;
        }
    }

    // Instruction selection layer: classify the IR node into the minimal
    // backend forms this encoder currently knows how to emit.
    std::optional<X86Selection> selectX86Selection(const IRNode &ir)
    {
        vector<string> operands = splitOperands(ir.lexeme);
        if (operands.size() < 2)
        {
            return std::nullopt;
        }

        auto dst = decodeOperand(operands[0], ir.dst);
        auto src = decodeOperand(operands[1], ir.src);
        if (!dst || !src)
        {
            return std::nullopt;
        }

        X86Selection selection;
        selection.dst = *dst;
        selection.src = *src;

        switch (ir.type)
        {
        case Tokens::MOV:
            if (selection.dst.kind == X86OperandKind::Register && selection.src.kind == X86OperandKind::Register)
            {
                selection.kind = X86SelectionKind::RegReg;
            }
            else if (selection.dst.kind == X86OperandKind::Register && selection.src.kind == X86OperandKind::Immediate)
            {
                selection.kind = X86SelectionKind::RegImm64;
            }
            else if (selection.dst.kind == X86OperandKind::Register && selection.src.kind == X86OperandKind::Memory)
            {
                selection.kind = X86SelectionKind::RegMem;
            }
            else if (selection.dst.kind == X86OperandKind::Memory && selection.src.kind == X86OperandKind::Register)
            {
                selection.kind = X86SelectionKind::MemReg;
            }
            break;

        case Tokens::ADD:
        case Tokens::SUB:
            if (selection.dst.kind == X86OperandKind::Register && selection.src.kind == X86OperandKind::Register)
            {
                selection.kind = X86SelectionKind::RegReg;
            }
            else if (selection.dst.kind == X86OperandKind::Register && selection.src.kind == X86OperandKind::Immediate)
            {
                selection.kind = X86SelectionKind::RegImm32;
            }
            else if (selection.dst.kind == X86OperandKind::Register && selection.src.kind == X86OperandKind::Memory)
            {
                selection.kind = X86SelectionKind::RegMem;
            }
            else if (selection.dst.kind == X86OperandKind::Memory && selection.src.kind == X86OperandKind::Register)
            {
                selection.kind = X86SelectionKind::MemReg;
            }
            break;

        default:
            break;
        }

        if (selection.kind == X86SelectionKind::Invalid)
        {
            return std::nullopt;
        }

        return selection;
    }

    // Reg/reg encoder shared by MOV, ADD, and SUB.
    bool encodeRegReg(Instructions &out, uint8_t opcode, Tokens::Token dstToken, Tokens::Token srcToken)
    {
        auto dst = decodeX86Reg(dstToken);
        auto src = decodeX86Reg(srcToken);
        if (!dst || !src)
        {
            return false;
        }

        uint8_t opWidth = 64;

        uint8_t rex = buildRex(opWidth == 64, src->rex, false, dst->rex);

        uint8_t modrm = static_cast<uint8_t>(0xC0 | (src->code << 3) | dst->code);
        out.bytes = {rex, opcode, modrm};
        return true;
    }

    // MOV reg, imm64 uses the B8+rd opcode family.
    bool encodeRegImm64(Instructions &out, Tokens::Token dstToken, int64_t immediate)
    {
        auto dst = decodeX86Reg(dstToken);
        if (!dst)
        {
            return false;
        }

        uint8_t rex = buildRex(true, false, false, dst->rex);
        uint8_t opcode = static_cast<uint8_t>(0xB8 + dst->code);

        out.bytes = {rex, opcode};
        appendUint64(out.bytes, static_cast<uint64_t>(immediate));
        return true;
    }

    // ADD/SUB reg, imm32 use the 81 /n form.
    bool encodeRegImm32(Instructions &out, Tokens::Token dstToken, int64_t immediate, uint8_t opcodeExtension)
    {
        auto dst = decodeX86Reg(dstToken);
        if (!dst)
        {
            return false;
        }

        if (immediate < numeric_limits<int32_t>::min() || immediate > numeric_limits<int32_t>::max())
        {
            return false;
        }

        uint8_t rex = buildRex(true, false, false, dst->rex);
        uint8_t modrm = static_cast<uint8_t>(0xC0 | (opcodeExtension << 3) | dst->code);

        out.bytes = {rex, 0x81, modrm};
        appendInt32(out.bytes, static_cast<int32_t>(immediate));
        return true;
    }

    // Encode register/memory forms with ModRM + optional SIB + displacement.
    bool encodeRegMem(Instructions &out, uint8_t opcode, const X86Operand &regOperand, const X86MemoryAddress &memory)
    {
        auto address = encodeAddress(memory, regOperand.reg.code);
        if (!address.valid)
        {
            return false;
        }

        uint8_t rex = buildRex(true, regOperand.reg.rex, address.rexX, address.rexB);
        out.bytes = {rex, opcode, address.modrm};
        if (address.usesSib)
        {
            out.bytes.push_back(address.sib);
        }
        out.bytes.insert(out.bytes.end(), address.displacement.begin(), address.displacement.end());
        return true;
    }

} // namespace

Instructions generate_x86_64(const IRNode &ir)
{
    Instructions out;
    out.arch = Architecture::X86_64;
    out.mnemonic = ir.lexeme;

    auto selection = selectX86Selection(ir);
    if (!selection)
    {
        return out;
    }

    switch (selection->kind)
    {
    case X86SelectionKind::RegReg:
        switch (ir.type)
        {
        case Tokens::MOV:
            if (!encodeRegReg(out, 0x89, ir.dst, ir.src))
            {
                out.bytes.clear();
            }
            break;
        case Tokens::ADD:
            if (!encodeRegReg(out, 0x01, ir.dst, ir.src))
            {
                out.bytes.clear();
            }
            break;
        case Tokens::SUB:
            if (!encodeRegReg(out, 0x29, ir.dst, ir.src))
            {
                out.bytes.clear();
            }
            break;
        default:
            break;
        }
        break;

    case X86SelectionKind::RegImm64:
        if (!encodeRegImm64(out, ir.dst, selection->src.immediate))
        {
            out.bytes.clear();
        }
        break;

    case X86SelectionKind::RegImm32:
        if (!encodeRegImm32(out, ir.dst, selection->src.immediate, ir.type == Tokens::SUB ? 5 : 0))
        {
            out.bytes.clear();
        }
        break;

    case X86SelectionKind::RegMem:
        if (!encodeRegMem(out, ir.type == Tokens::MOV ? 0x8B : (ir.type == Tokens::ADD ? 0x03 : 0x2B), selection->dst, selection->src.memory))
        {
            out.bytes.clear();
        }
        break;

    case X86SelectionKind::MemReg:
        if (!encodeRegMem(out, ir.type == Tokens::MOV ? 0x89 : (ir.type == Tokens::ADD ? 0x01 : 0x29), selection->src, selection->dst.memory))
        {
            out.bytes.clear();
        }
        break;

    case X86SelectionKind::Invalid:
    default:
        out.bytes.clear();
        break;
    }

    return out;
}