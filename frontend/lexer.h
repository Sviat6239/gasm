#ifndef LEXER_H
#endif LEXER_H

typedef enum{
    TOKEN_INT,
    TOKEN_ECHO,
    TOKEN_EOF,

} TokenType;

typedef struct{
    TokenType type;
    char value[64];
} Token;