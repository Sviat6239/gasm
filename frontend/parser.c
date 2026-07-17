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

        if (tokens->tokens[*pos].type != TOKEN_E)
    }
}