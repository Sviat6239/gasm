#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/parser.h"

ASTNode* create_node(ASTNodeType type, int value, const char* name, const char* literal_value, const char* data_type, int mutability, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value;
    node->data_type = data_type;
    node->mutability = mutability;
    
    if (name != NULL) {
        strncpy(node->name, name, 63);
        node->name[63] = '\0';
    } else {
        node->name[0] = '\0';
    }

    if (literal_value != NULL) {
        strncpy(node->literal_value, literal_value, 63);
        node->literal_value[63] = '\0';
    } else {
        node->literal_value[0] = '\0';
    }
    
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* parse_statement(TokenList* tokens, int* pos) {
    Token current = tokens->tokens[*pos];

    if (current.type == TOKEN_LET) {
        (*pos)++;

        int mutability = 0;
        if (tokens->tokens[*pos].type == TOKEN_MUT || tokens->tokens[*pos].type == TOKEN_UMUT) {
            mutability = (tokens->tokens[*pos].type == TOKEN_MUT) ? 1 : 0;
            (*pos)++;
        }

        const char* d_type = "i32";
        TokenType t_type = tokens->tokens[*pos].type;
        
        if (t_type >= TOKEN_I64 && t_type <= TOKEN_CHAR) {
            d_type = tokens->tokens[*pos].data_type;
            (*pos)++;
        }

        if (tokens->tokens[*pos].type != TOKEN_IDENTIFIER) {
            printf("Syntax error: expected identifier at pos=%d\n", *pos);
            exit(1);
        }
        Token var = tokens->tokens[*pos];
        (*pos)++;

        if (tokens->tokens[*pos].type != TOKEN_EQUAL) {
            printf("Syntax error: expected '=' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++;

        ASTNode* expr = parse_expression(tokens, pos);

        if (tokens->tokens[*pos].type != TOKEN_SEMICOLON) {
            printf("Syntax error: expected ';' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++;

        return create_node(AST_ASSIGN, 0, var.name, NULL, d_type, mutability, expr, NULL);
    } 
    
    else if (current.type == TOKEN_ECHO) {
        (*pos)++;
        ASTNode* expr = parse_expression(tokens, pos);

        if (tokens->tokens[*pos].type != TOKEN_SEMICOLON) {
            printf("Syntax error: expected ';' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++;
        return create_node(AST_ECHO, 0, NULL, NULL, NULL, 0, expr, NULL);
    } 
    
    else if (current.type == TOKEN_LPAREN) {
        (*pos)++;
        ASTNode* expr = parse_expression(tokens, pos);
        if (tokens->tokens[*pos].type != TOKEN_RPAREN) {
            printf("Syntax error: expected ')' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++;
        return expr;
    } 
    
    else {
        ASTNode* expr = parse_expression(tokens, pos);
        if (tokens->tokens[*pos].type == TOKEN_SEMICOLON) (*pos)++;
        return expr;
    }
}

ASTNode* parse_expression(TokenList* tokens, int* pos) {
    Token current = tokens->tokens[*pos];
    ASTNode* left = NULL;

    if (current.type == TOKEN_INT) {
        left = create_node(AST_NUMBER, current.value, NULL, NULL, current.data_type, 0, NULL, NULL);
        (*pos)++;
    } 
    else if (current.type == TOKEN_F32 || current.type == TOKEN_F64) {
        left = create_node(AST_FLOAT, 0, NULL, current.name, current.data_type, 0, NULL, NULL);
        (*pos)++;
    } 
    else if (current.type == TOKEN_STR) {
        left = create_node(AST_STRING, 0, NULL, current.name, "str", 0, NULL, NULL);
        (*pos)++;
    } 
    else if (current.type == TOKEN_CHAR) {
        left = create_node(AST_CHARACTER, current.value, NULL, NULL, "char", 0, NULL, NULL);
        (*pos)++;
    } 
    else if (current.type == TOKEN_IDENTIFIER) {
        left = create_node(AST_VAR, 0, current.name, NULL, current.data_type, 0, NULL, NULL);
        (*pos)++;
    } 
    else if (current.type == TOKEN_LPAREN) {
        (*pos)++;
        left = parse_expression(tokens, pos);
        if (tokens->tokens[*pos].type != TOKEN_RPAREN) {
            printf("Syntax error: expected ')' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++;
    } 
    else {
        printf("Syntax error: unexpected token at pos=%d, type=%d\n", *pos, current.type);
        exit(1);
    }

    current = tokens->tokens[*pos]; 
    while (current.type == TOKEN_PLUS || current.type == TOKEN_MINUS ||
           current.type == TOKEN_MULT || current.type == TOKEN_DIV) {
        char op = 0;
        switch (current.type) {
            case TOKEN_PLUS:  op = '+'; break;
            case TOKEN_MINUS: op = '-'; break;
            case TOKEN_MULT:  op = '*'; break;
            case TOKEN_DIV:   op = '/'; break;
            default: break;
        }
        (*pos)++;
        ASTNode* right = parse_expression(tokens, pos);
        left = create_node(AST_BINARY_OP, op, NULL, NULL, current.data_type, 0, left, right);
        current = tokens->tokens[*pos];
    }
    return left;
}

ASTNode* parse(TokenList* tokens) {
    int pos = 0;
    ASTNode* root = NULL;

    while (tokens->tokens[pos].type != TOKEN_EOF) {
        ASTNode* stmt = parse_statement(tokens, &pos);

        if (root == NULL) {
            root = stmt;
        } else {
            ASTNode* temp = root;
            while (temp->right != NULL) temp = temp->right;
            temp->right = stmt;
        }
    }

    return root;
}

void print_ast(ASTNode* node, int indent) {
    if (node == NULL) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case AST_NUMBER:
            printf("AST_NUMBER(%d, type: %s)\n", node->value, node->data_type ? node->data_type : "i32");
            break;
        case AST_FLOAT:
            printf("AST_FLOAT(%s, type: %s)\n", node->literal_value, node->data_type);
            break;
        case AST_STRING:
            printf("AST_STRING(\"%s\")\n", node->literal_value);
            break;
        case AST_CHARACTER:
            printf("AST_CHARACTER('%c')\n", (char)node->value);
            break;
        case AST_VAR:
            printf("AST_VAR(name: %s, type: %s)\n", node->name, node->data_type ? node->data_type : "unknown");
            break;
        case AST_BINARY_OP:
            printf("AST_BINARY_OP(%c)\n", node->value);
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case AST_ASSIGN:
            printf("AST_ASSIGN(var: %s, type: %s, mut: %d)\n", node->name, node->data_type, node->mutability);
            print_ast(node->left, indent + 1);
            break;
        case AST_ECHO: 
            printf("AST_ECHO\n");
            print_ast(node->left, indent + 1);
            break;
        default:
            printf("Unknown AST node type: %d\n", node->type);
    }
    
    if (node->type == AST_ASSIGN || node->type == AST_ECHO) {
        print_ast(node->right, indent);
    }
}