// symbols.cpp
// Helpers for inspecting and reporting on symbol resolution during
// assembly/IR processing.

#include "symbols.h"
#include "utils.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Human-readable display name for a token. Used in diagnostics and
// debugging output; returns a fixed name for punctuation/literals and
// uppercased lexeme for identifiers/other tokens.
string displayName(const Token &token)
{
    switch (token.type)
    {
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

// Print information about entry point resolution. If an `entryLabel` was
// declared, look it up in the symbol table and report whether it was
// resolved to a known label with a source line, or left unresolved.
void printEntryResolution(const SymbolTable &symbolTable)
{
    if (symbolTable.entryLabel.empty())
    {
        return;
    }

    cout << "\nEntry point resolution:\n";
    cout << "Target: " << symbolTable.entryLabel << '\n';
    auto entryIt = symbolTable.labels.find(symbolTable.entryLabel);
    if (entryIt != symbolTable.labels.end())
    {
        cout << "Status: RESOLVED at line " << entryIt->second << '\n';
    }
    else
    {
        cout << "Status: UNRESOLVED (Error: Label not found)" << endl;
    }
}
