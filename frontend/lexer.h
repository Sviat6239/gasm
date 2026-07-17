#ifndef LEXER_H
#endif LEXER_H

/*
 * Token types for the GASM
 * Each token represents a meaningful element of the source code
 */
typedef enum{
    TOKEN_INT,
    TOKEN_ECHO,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_DIV,
    TOKEN_MULT,
    TOKEN_LET,
    TOKEN_EQUAL,
    TOKEN_SEMICOLON,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_MUT,
    TOKEN_UMUT,
    TOKEN_I64,
    TOKEN_UI64,
    TOKEN_I32,
    TOKEN_UI32,
    TOKEN_I16,
    TOKEN_UI16,
    TOKEN_I8,
    TOKEN_UI8,
    TOKEN_F64,
    TOKEN_F32,
    TOKEN_STR,
    TOKEN_CHAR,
    TOKEN_IDENTIFIER
} TokenType;

/*
 * Token structure
 * Holds type and value or name (depending on token)
 */
typedef struct{
    TokenType type;
    int value;
    char name[64];
} Token;

/*
 * Token list structure
 * Contains an array of tokens and a count
 */
typedef struct {
    Token* tokens;
    int count;
} TokenList;

/* Function declarations */

/*
 *   Takes a string containing source code and converts it into a list of tokens.
 *   Each token represents a meaningful element of the language (number, operator, keyword, identifier, etc.).
 */
TokenList lex(const char* source);

/*
 *   Prints all tokens in a TokenList to the console, for debugging and verification purposes.
 */
void print_tokens(TokenList* list);

#endif