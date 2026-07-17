#ifdef PARSER_H
#endif PARSER_H

#include "lexer.h"

typedef enum {
    AST_NUMBER,
    AST_ECHO,
    AST_BINARY_OP,
    AST_VAR,
    AST_ASSIGN
} ASTNodeType;

typedef struct ASTNode{
    ASTNodeType type;
    int value;
    char name[64];
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* parse(TokenList* tokens);

void print_asr(ASTNode* node, int indent);

#endif