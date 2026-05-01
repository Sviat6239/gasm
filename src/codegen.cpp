#include "codegen.h"
#include "ir.h"

#include <optional>

namespace
{

    struct X86RegInfo
    {
        uint8_t code = 0;
        bool rex = false;
        uint8_t width = 0;
    };

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

    bool encodeRegReg(Instructions &out, uint8_t opcode, Tokens::Token dstToken, Tokens::Token srcToken)
    {
        auto dst = decodeX86Reg(dstToken);
        auto src = decodeX86Reg(srcToken);
        if (!dst || !src)
        {
            return false;
        }

        uint8_t opWidth = 64;

        uint8_t rex = 0x40; // 0100 W R X B
        if (opWidth == 64)
        {
            rex |= 0x08;
        }
        if (src->rex)
        {
            rex |= 0x04;
        }
        if (dst->rex)
        {
            rex |= 0x01;
        }

        uint8_t modrm = static_cast<uint8_t>(0xC0 | (src->code << 3) | dst->code);
        out.bytes = {rex, opcode, modrm};
        return true;
    }

} // namespace

Instructions generate_x86_64(const IRNode &ir)
{
    Instructions out;
    out.arch = Architecture::X86_64;
    out.mnemonic = ir.lexeme;

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

    return out;
}