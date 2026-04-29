#include "symbols.h"
#include "utils.h"
#include <iostream>

using namespace std;

string displayName(const Token& token) {
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

void printEntryResolution(const SymbolTable& symbolTable) {
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
