#include "codegen.h"
#include "ir.h"

Instructions generate_x86_64(const IRNode &ir)
{
    Instructions out;
    out.arch = Architecture::X86_64;
    out.mnemonic = ir.lexeme;
    return out;
}