#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

// Helper function to create a new token
Token create_token(TokenType type, int value, const char* name){
    Token token:
    token.type = type;
    token.value = value;
    if (name)
        strcpy(token.name, name, sizeof(token.name) - 1);
    else
        token.name[0] = '\0';
    return token;
}

// Lexical analysis function
TokenList lex(const char* source){
    TokenList list;
    list.tokens = malloc(128 * sizeof(Token));
    list.count = 0;

    int i = 0;
    while (source[i] != '\0'){
        char c = source[i];

        //whitespace
        if (isspace(c)){
            i++;
            countinue;
        }

        if (isdigit(c)){
            int value = 0;

            while (isdigit(source[i])){
                value = value * 10 + (source[i] - '0');
                i++
            }
            list.tokens[list.count++] = create_token(TOKEN_INT, value, NULL);
            countinue;
        }

        if (isalpha(c)){
            char buffer[64];
            int j = 0;

            while (isalnum(source[i]) && j < 31){
                buffer[j++] = source[i++];
            }
            buffer[j] = '\0';

            if (strcmp(buffer, "let") == 0)
                list.tokens[list.count++] = create_token(TOKEN_LET, 0, NULL);
            else if (strcmp(buffer, "echo") == 0)
                list.tokens[list.count++] = create_token(TOKEN_ECHO, 0, NULL);
            else if (strcmp(buffer, "mut") == 0)
                list.tokens[list.count++] = create_token(TOKEN_MUT, 0, NULL);
            else if (strcmp(buffer, "umut") == 0)
                list.tokens[list.count++] = create_token(TOKEN_UMUT, 0, NULL);
            else if (strcmp(buffer, "i64") == 0)
                list.tokens[list.count++] = create_token(TOKEN_I64, 0, NULL);
            else if (strcmp(buffer, "i32") == 0)
                list.tokens[list.count++] = create_token(TOKEN_I32, 0, NULL);
            else if (strcmp(buffer, "i16") == 0)
                list.tokens[list.count++] = create_token(TOKEN_I16, 0, NULL);
            else if (strcmp(buffer, "i8") == 0)
                list.tokens[list.count++] = create_token(TOKEN_I8, 0, NULL);
            else if (strcmp(buffer, "ui64") == 0)
                list.tokens[list.count++] = create_token(TOKEN_UI64, 0, NULL);
            else if (strcmp(buffer, "ui32") == 0)
                list.tokens[list.count++] = create_token(TOKEN_UI32, 0, NULL);
            else if (strcmp(buffer, "ui16") == 0)
                list.tokens[list.count++] = create_token(TOKEN_UI16, 0, NULL);
            else if (strcmp(buffer, "ui8") == 0)
                list.tokens[list.count++] = create_token(TOKEN_UI8, 0, NULL);
            else if (strcmp(buffer, "str") == 0)
                list.tokens[list.count++] = create_token(TOKEN_STR, 0, NULL);
             else if (strcmp(buffer, "char") == 0)
                list.tokens[list.count++] = create_token(TOKEN_CHAR, 0, NULL);
            else 
                list.tokens[list.count++] = create_token(TOKEN_IDENTIFIER, 0, buffer);

            continue;
        }

        switch (c){
            case '+': list.tokens[list.count++] = create_token(TOKEN_PLUS, 0, NULL); break;
            case '-': list.tokens[list.count++] = create_token(TOKEN_MINUS, 0, NULL); break;
            case '*': list.tokens[list.count++] = create_token(TOKEN_MULT, 0, NULL); break;
            case '/': list.tokens[list.count++] = create_token(TOKEN_DIV, 0, NULL); break;
            case '=': list.tokens[list.count++] = create_token(TOKEN_EQUAL, 0, NULL); break;
            case ';': list.tokens[list.count++] = create_token(TOKEN_SEMICOLON, 0, NULL); break;
            case '(': list.tokens[list.count++] = create_token(TOKEN_LPAREN, 0, NULL); break;
            case ')': list.tokens[list.count++] = create_token(TOKEN_RPAREN, 0, NULL): break;
            default;
                printf("Unknown character: %c\n", c);
                exit(1);
        }
        i++;
        
    }
}