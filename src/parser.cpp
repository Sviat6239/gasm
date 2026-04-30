// parser.cpp
// Converts raw token strings produced by the lexer into typed `Token` values
// used by later compilation stages (parser/IR generation/etc.).
//
// Responsibilities:
// - Classify each raw token text into a `Tokens::Token` kind
// - Normalize token lexemes where appropriate (for example, remove
//   surrounding quotes from string literals)
// - Preserve source location information (line numbers) for diagnostics

#include "parser.h"
#include "lexer.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Transform a list of raw token strings (text + line) into a list of
// typed `Token` objects. `rawTokens` comes from the lexer; each element
// contains the original token text and the source line it came from.
//
// This function does not perform any syntactic checking — it only maps
// lexical token text to the internal token kind and prepares the lexeme
// for downstream stages.
vector<Token> parse(const vector<TokenString> &rawTokens)
{
    vector<Token> parsed;
    // Reserve once to avoid repeated reallocations when pushing tokens.
    parsed.reserve(rawTokens.size());

    for (const auto &raw : rawTokens)
    {
        // Determine the token kind using the lexer helper.
        Tokens::Token type = classifyToken(raw.text);

        // The lexeme is the textual payload carried with the token.
        // For most token kinds we keep the raw text as-is.
        string lexeme = raw.text;

        // For string literals, strip the surrounding quotes so later
        // stages receive the contained value only (no leading/trailing ").
        if (type == Tokens::STRING && raw.text.size() >= 2)
        {
            lexeme = raw.text.substr(1, raw.text.size() - 2);
        }

        // Preserve the original source line for error reporting.
        parsed.push_back({type, lexeme, raw.line});
    }

    return parsed;
}
