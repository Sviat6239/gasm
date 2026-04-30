#include "ir.h"

// Build a simple linear IR from the token stream. The IR in this project
// is a lightweight sequence of `IRNode` entries mirroring tokens with
// preserved lexemes and source lines. This function also extracts a few
// global symbols while scanning:
// - `entryLabel` when an `ENTRY` directive is followed by an identifier
// - label definitions: `identifier:` entries are recorded in `SymbolTable`
vector<IRNode> buildIR(const vector<Token> &tokens, SymbolTable &symbolTable)
{
    vector<IRNode> ir;
    ir.reserve(tokens.size());

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        const auto &token = tokens[i];
        // Mirror the token into an IR node (no transformation here)
        ir.push_back({token.type, token.lexeme, token.line});

        // If we see an `ENTRY` directive followed by an identifier,
        // record the entry point name in the symbol table.
        if (token.type == Tokens::ENTRY && i + 1 < tokens.size() && tokens[i + 1].type == Tokens::IDENTIFIER)
        {
            symbolTable.entryLabel = tokens[i + 1].lexeme;
        }

        // If we encounter a label definition (`IDENTIFIER :`), store the
        // label name and its source line for later resolution.
        if (token.type == Tokens::IDENTIFIER && i + 1 < tokens.size() && tokens[i + 1].type == Tokens::COLON)
        {
            symbolTable.labels[token.lexeme] = static_cast<int>(token.line);
        }
    }

    return ir;
}
