#ifdef PARSER_H
#endif PARSER_H

#include "lexer.h"

/*
 * AST node types
 * Represents different elements of the program syntax
 */
typedef enum {
    AST_NUMBER,
    AST_ECHO,
    AST_BINARY_OP,
    AST_VAR,
    AST_ASSIGN
} ASTNodeType;

/*
 * AST node structure
 * Represents one node in the abstract syntax tree
 */
typedef struct ASTNode{
    ASTNodeType type;
    int value;
    char name[64];
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

void print_asr(ASTNode* node, int indent);

#endif