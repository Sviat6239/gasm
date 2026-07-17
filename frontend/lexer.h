#ifndef LEXER_H
#endif LEXER_H

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

typedef struct{
    TokenType type;
    int value;
    char name[64];
} Token;

typedef struct {
    Token* tokens;
    int count;
} TokenList;

TokenList lex(const char* source);

void print_tokens(TokenList* list);

#endif