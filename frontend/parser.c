#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

ASTNode* create_node(ASTNodeType type, int value, const char* name, ASTNode* left, ASTNode* right){
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value;
    if (name != NULL){
        strncpy(node->name, name, 63);
        node->name[63] = '\0';
    } else {
        node->name[0] = '\0';
    } else {
        node->name[0] = '\0';
    }
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* parse_expression(TokenList* tokens, int pos);

ASTNode* parse_statement(TokenList* tokens, init pos){
    Token current = tokens->tokens[*pos];

    if (current.type == TOKEN_LET){
        (*pos)++
        (*pos)++
        (*pos)++
        Token var = tokens->tokens[*pos];
        (*pos)++;

        if (tokens->tokens[*pos].type != TOKEN_EQUAL){
            printf("Syntax error: expected '=' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++;

        ASTNode* expr = parse_expression(tokens, pos);

        if (tokens->tokens[*pos].type != TOKEN_SEMICOLON){
            printf("Syntax error: expected ';' at pos=%d\n", *pos);
        }
        (*pos)++;

        return create_node(AST_ASSIGN, 0, var.name, expr, NULL);
    } else if (current.type == TOKEN_ECHO){
        (*pos)++;

        ASTNode* expr = parse_expression(tokens, pos);

        if (tokens->tokens[*pos].type != TOKEN_SEMICOLON){
            printf("Syntax error: expected ';' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++;

        return create_node(AST_ECHO, 0, NULL, expr, NULL);

    } else if (current.type == TOKEN_LPAREN) {
        (*pos)++;
        ASTNode* expr = parse_expression(tokens, pos);
        if (tokens->tokens[*pos].type != TOKEN_RPAREN){
            printf("Syntax error: expected ')', at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++;
        return expr;
    } else {
        ASTNode* expr = parse_expression(tokens, pos);
        if (tokens->[*pos].type == TOKEN_SEMICOLON) (*pos)++;
        return expr;
    }
  
} 
