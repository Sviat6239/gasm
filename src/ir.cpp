#include "ir.h"

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
