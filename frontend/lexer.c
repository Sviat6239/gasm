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
    list.tokens[list.count++] = create_token(TOKEN_EOF, 0, NULL);
    return list;
}

void print_tokens(TokenList* list){
    for (int i = 0; i < list->count; i++){
        Token t = list->tokens[i];
        switch (t.type){
            case TOKEN_CHAR: printf("CHAR\n"); break;
            case TOKEN_DIV: printf("DIV\n"); break;
            case TOKEN_ECHO: printf("ECHO\n"); break;
            case TOKEN_EOF: printf("EOF\n"); break;
            case TOKEN_EQUAL: printf("EQUAL\n"); break;
            case TOKEN_I16: printf("I16\n"); break;
            case TOKEN_I32: printf("I32\n"); break;
            case TOKEN_I64: printf("I64\n"); break;
            case TOKEN_I8: printf("I8\n"); break;
            case TOKEN_IDENTIFIER: printf("IDENT(%s)\n", t.name); break;
            case TOKEN_INT: printf("NUMBER(%d)\n", t.value); break;
            case TOKEN_LET: printf("LET\n"); break;
            case TOKEN_MINUS: printf("MINUS\n"); break;
            case TOKEN_MULT: printf("MULT\n"); break;
            case TOKEN_MUT: printf("MUT\n"); break;
            case TOKEN_PLUS: printf("PLUS\n"); break;
            case TOKEN_SEMICOLON: printf("SEMI\n"); break;
            case TOKEN_STR: printf("STR\n"); break;
            case TOKEN_UI16: printf("UI16\n"); break;
            case TOKEN_UI32: printf("UI32\n"); break;
            case TOKEN_UI64: printf("UI64\n"); break;
            case TOKEN_UI8: printf("UI8\n"); break;
            case TOKEN_UMUT: printf("UMUT\n"); break;
        }
    }
}