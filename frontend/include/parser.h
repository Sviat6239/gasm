#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

/*
 * AST node types
 * Represents different elements of the program syntax
 */
typedef enum {
    AST_NUMBER,
    AST_FLOAT,
    AST_STRING,
    AST_CHARACTER,
    AST_ECHO,
    AST_BINARY_OP,
    AST_VAR,
    AST_ASSIGN,
    AST_IF,
    AST_ELSE,
    AST_FUNC,
    AST_SWITCH,
    AST_CASE,
    AST_FOR,
    AST_RETURN,
    AST_CALL,
    AST_WHILE
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    int value;
    char name[64];
    char literal_value[128];
    const char* data_type;
    int mutability;
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

/* Function declarations */

/*
 *   Takes a list of tokens (produced by the lexer) and builds an Abstract Syntax Tree (AST).
 *   The AST represents the hierarchical structure of the program and the order of operations.
 *   Example: "5 + 3" becomes a node of type AST_BINARY_OP with two children nodes (5 and 3).
 */
ASTNode* parse(TokenList* tokens);

ASTNode* parse_statement(TokenList* tokens, int* pos);
ASTNode* parse_expression(TokenList* tokens, int* pos);
void print_ast(ASTNode* node, int indent);

#endif