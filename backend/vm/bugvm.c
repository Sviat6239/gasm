#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define OP_PUSH     0x0001 // push value on the stack
#define OP_PUSH_STR 0x0002 // push str value on the stack
#define OP_POP      0x0003 // pop value from the stack
#define OP_ADD      0x0004 // add two last values from the stack
#define OP_SUB      0x0005 // sub two last values from the stack
#define OP_MUL      0x0006 // mul two last values from the stack
#define OP_DIV      0x0007 // div two last values from the stack
#define OP_PRINT    0x0008 // print the value from the stack
#define OP_INPUT    0x0009 // read value to the stack
#define OP_STORE    0x000A // store value from the stack in a local variable
#define OP_LOAD     0x000B // put a value from locals onto stack
#define OP_CMP      0x000C // compare two top values from stack and set flags
#define OP_JMP      0x000D // unconditional jump to a target line
#define OP_JNZ      0x000E // jump to a target line if flag is not zero
#define OP_JZ       0x000F // jump to a target line if flag is zero
#define OP_JNE      0x0010 // jump if not equal (flags != FL_EQ)
#define OP_JE       0x0011 // jump if equal (flags == FL_EQ)
#define OP_JGE      0x0012 // jump if greater or equal (flags == FL_GT || flags == FL_EQ)
#define OP_JG       0x0013 // jump if greater (flags == FL_GT)
#define OP_JLE      0x0014 // jump if less or equal (flags == FL_LT || flags == FL_EQ)
#define OP_JL       0x0015 // jump if less (flags == FL_LT)
#define OP_HALT     0xFFFF // halt the program

typedef enum {
    FL_EQ,
    FL_GT,
    FL_LT
} CompareFlag;

CompareFlag flags;

typedef enum {
    VAL_INT,
    VAL_STR
} ValType;

typedef struct {
    ValType type;
    union {
        int as_int;
        char *as_str;
    } value;
} Object;

typedef struct{
    char **tokens;
    int token_count;
} Line;

#define STACK_SIZE (1024 * 1024)
#define LOCAL_SIZE (1024 * 1024)
Object stack[STACK_SIZE];
Object locals[LOCAL_SIZE];
int sp = -1;
int ip = 0;

void push(Object obj) {
    if (sp >= STACK_SIZE - 1) {
        printf("Error: stack overflow!\n");
        exit(1);
    }
    stack[++sp] = obj;
}

void push_int(int val) {
    Object obj;
    obj.type = VAL_INT;
    obj.value.as_int = val;
    push(obj);
}

void push_str(char *str) {
    Object obj;
    obj.type = VAL_STR;
    obj.value.as_str = str;
    push(obj);
}

Object pop() {
    if (sp < 0) {
        printf("Error: stack is empty!\n");
        exit(1);
    }
    return stack[sp--];
}

int o_cmp(int a, int b){
    return 1;
}

void parse_line(const char *buffer, Line *line)
{
    char temp[1024]; // temporary buffer for building current token
    int temp_idx = 0;
    bool in_quotes = false;
    char quote_type = 0;

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        char c = buffer[i];

        // Handle quote characters (start/end of string literals)
        if ((c == '"' || c == '\'') && (i == 0 || buffer[i - 1] != '\\'))
        {
            if (!in_quotes)
            {
                in_quotes = true;
                quote_type = c;
            }
            else if (c == quote_type)
            {
                in_quotes = false;
            }
            else
            {
                temp[temp_idx++] = c;
            }
        }

        // Whitespace delimiters (outside quotes)
        else if (!in_quotes && (c == ' ' || c == '\t' || c == '\n' || c == '\r'))
        {
            if (temp_idx > 0)
            {
                temp[temp_idx] = '\0';
                line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
                line->tokens[line->token_count++] = strdup(temp);
                temp_idx = 0;
            }
        }
        else
        {
            temp[temp_idx++] = c;
        }
    }

    // Add the last token if any remains
    if (temp_idx > 0)
    {
        temp[temp_idx] = '\0';
        line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
        line->tokens[line->token_count++] = strdup(temp);
    }
}

int main(){
    FILE *fptr = fopen("bytecode001.bbin", "r");
    if (!fptr)
    {
        perror("Error opening input file 'code.as'");
        return -1;
    }

    Line *lines = NULL;
    int line_count = 0;
    char buffer[1024];

    // ==================== READING AND TOKENIZING PHASE ====================
    printf("=== Reading and tokenizing code.as ===\n");
    while (fgets(buffer, sizeof(buffer), fptr))
    {
        // Remove comments (everything after //)
        char *comment_ptr = strstr(buffer, "//");
        if (comment_ptr)
            *comment_ptr = '\0';

        // Remove semicolon if present (simple statement terminator)
        char *semi = strchr(buffer, ';');
        if (semi)
            *semi = '\0';

        // Skip empty lines
        if (strspn(buffer, " \t\n\r\f\v") == strlen(buffer))
            continue;

        // Allocate new Line structure
        lines = realloc(lines, (line_count + 1) * sizeof(Line));
        lines[line_count].tokens = NULL;
        lines[line_count].token_count = 0;

        parse_line(buffer, &lines[line_count]);
        line_count++;
    }

    // ==================== DEBUG: PRINT ALL TOKENS ====================
    printf("\n=== Tokenized lines ===\n");
    for (int i = 0; i < line_count; i++)
    {
        printf("Line %d: ", i);
        for (int j = 0; j < lines[i].token_count; j++)
        {
            printf("[%s] ", lines[i].tokens[j]);
        }
        printf("\n");
    }

    char *value;

    // ==================== EXECUTE LOOP ====================
    printf("\n=== Execution ===\n");
    for (ip = 0; ip < line_count; ip++) {
        if (lines[ip].token_count == 0) continue;

        char *cmd = lines[ip].tokens[0];
        int opcode = (int)strtol(cmd, NULL, 0);

        switch (opcode) {
            case OP_PUSH: {
                int val = (int)strtol(lines[ip].tokens[1], NULL, 0);
                push_int(val);
                break;
            }
            case OP_PUSH_STR: {
                char *str_ptr = strdup(lines[ip].tokens[1]);
                push_str(str_ptr);
                break;
            }
            case OP_POP: {
                pop();
                break;
            }
            case OP_ADD: {
                Object b = pop();
                Object a = pop();

                if (a.type == VAL_INT && b.type == VAL_INT) {
                    push_int(a.value.as_int + b.value.as_int);
                } 
                else if (a.type == VAL_STR && b.type == VAL_STR) {
                    char *new_str = malloc(strlen(a.value.as_str) + strlen(b.value.as_str) + 1);
                    strcpy(new_str, a.value.as_str);
                    strcat(new_str, b.value.as_str);
                    push_str(new_str);
                    
                    free(a.value.as_str);
                    free(b.value.as_str);
                } 
                else {
                    printf("Runtime Error: Invalid types for OP_ADD!\n");
                    return 1;
                }
                break;
            }
            case OP_SUB: {
                Object b = pop();
                Object a = pop();

                if (a.type == VAL_INT && b.type == VAL_INT) {
                    push_int(a.value.as_int - b.value.as_int);
                } 
                else if (a.type == VAL_STR && b.type == VAL_STR) {
                    char *new_str = malloc(strlen(a.value.as_str) + strlen(b.value.as_str) + 1);
                    strcpy(new_str, a.value.as_str);
                    strcat(new_str, b.value.as_str);
                    push_str(new_str);
                    
                    free(a.value.as_str);
                    free(b.value.as_str);
                } 
                else {
                    printf("Runtime Error: Invalid types for OP_SUB!\n");
                    return 1;
                }
                break;
            }
            case OP_MUL: {
                Object b = pop();
                Object a = pop();

                if (a.type == VAL_INT && b.type == VAL_INT) {
                    push_int(a.value.as_int * b.value.as_int);
                } 
                else if (a.type == VAL_STR && b.type == VAL_STR) {
                    char *new_str = malloc(strlen(a.value.as_str) + strlen(b.value.as_str) + 1);
                    strcpy(new_str, a.value.as_str);
                    strcat(new_str, b.value.as_str);
                    push_str(new_str);
                    
                    free(a.value.as_str);
                    free(b.value.as_str);
                } 
                else {
                    printf("Runtime Error: Invalid types for OP_MUL!\n");
                    return 1;
                }
                break;
            }
            case OP_DIV: {
                Object b = pop();
                Object a = pop();

                if (a.type == VAL_INT && b.type == VAL_INT) {
                    if(b.value.as_int == 0){
                        printf("Error: cant divide by zero!");
                        exit(1);
                    }
                    push_int(a.value.as_int / b.value.as_int);
                } 
                else if (a.type == VAL_STR && b.type == VAL_STR) {
                    char *new_str = malloc(strlen(a.value.as_str) + strlen(b.value.as_str) + 1);
                    strcpy(new_str, a.value.as_str);
                    strcat(new_str, b.value.as_str);
                    push_str(new_str);
                    
                    free(a.value.as_str);
                    free(b.value.as_str);
                } 
                else {
                    printf("Runtime Error: Invalid types for OP_DIV!\n");
                    return 1;
                }
                break;
            }
            case OP_PRINT: {
                if (sp < 0) {
                    printf("Error: Stack is empty!\n");
                } else {
                    Object obj = stack[sp];
                    if (obj.type == VAL_INT) {
                        printf("%d\n", obj.value.as_int);
                    } else if (obj.type == VAL_STR) {
                        printf("%s\n", obj.value.as_str);
                    }
                }
                break;
            }
            case OP_INPUT: {
                char input_buf[1024];
                if (scanf(" %1023[^\n]", input_buf) != 1) {
                    printf("Error: invalid input!\n");
                    return 1;
                }

                bool is_number = true;
                int start_idx = (input_buf[0] == '-') ? 1 : 0;
                
                if (input_buf[start_idx] == '\0') is_number = false;
                
                for (int i = start_idx; input_buf[i] != '\0'; i++) {
                    if (input_buf[i] < '0' || input_buf[i] > '9') {
                        is_number = false;
                        break;
                    }
                }

                if (is_number) {
                    int val = atoi(input_buf);
                    push_int(val);
                } else {
                    push_str(strdup(input_buf));
                }
                break;
            }
            case OP_STORE:{
                if (lines[ip].token_count < 2){
                    printf("Error: required argument!");
                    exit(1);
                }
                int idx = (int)strtol(lines[ip].tokens[1], NULL, 0);

                if (idx < 0 || idx >= LOCAL_SIZE) {
                    printf("Error: Local index out of bounds!\n");
                    return 1;
                }

                if (locals[idx].type == VAL_STR && locals[idx].value.as_str != NULL) {
                    free(locals[idx].value.as_str);
                }

                locals[idx] = pop(); 
                break;
            }
            case OP_LOAD:{
                if (lines[ip].token_count < 2){
                    printf("Error: ruquired argumnet!");
                    exit(1);
                }
                int idx = (int)strtol(lines[ip].tokens[1], NULL, 0);

                if (idx < 0 || idx >= LOCAL_SIZE) {
                    printf("Error: Local index out of bounds!\n");
                    return 1;
                }

                push(locals[idx]); 
                break;
            }
            case OP_CMP: {
                Object b = pop();
                Object a = pop();

                if (a.type != VAL_INT || b.type != VAL_INT) {
                    printf("Runtime Error: OP_CMP supports INTEGER comparison only!\n");
                    return 1;
                }

                if (a.value.as_int == b.value.as_int) {
                    flags = FL_EQ;
                } else if (a.value.as_int > b.value.as_int) {
                    flags = FL_GT;
                } else {
                    flags = FL_LT;
                }

                break;
            }

            case OP_JMP: {
                if (lines[ip].token_count < 2) {
                    printf("Runtime Error: OP_JMP requires a target line!\n");
                    return 1;
                }
                int target_line = (int)strtol(lines[ip].tokens[1], NULL, 0);
                if (target_line < 0 || target_line >= line_count) {
                    printf("Runtime Error: JMP target out of bounds!\n");
                    return 1;
                }
                ip = target_line - 1; 
                break;
            }

            case OP_JE:
            case OP_JNE:
            case OP_JG:
            case OP_JGE:
            case OP_JL:
            case OP_JLE: {
                if (lines[ip].token_count < 2) {
                    printf("Runtime Error: Conditional jump requires a target line!\n");
                    return 1;
                }
                int target_line = (int)strtol(lines[ip].tokens[1], NULL, 0);

                bool should_jump = false;

                if (opcode == OP_JE || opcode == OP_JZ)    should_jump = (flags == FL_EQ);
                if (opcode == OP_JNE || opcode == OP_JNZ)  should_jump = (flags != FL_EQ);
                if (opcode == OP_JG)   should_jump = (flags == FL_GT);
                if (opcode == OP_JGE)  should_jump = (flags == FL_GT || flags == FL_EQ);
                if (opcode == OP_JL)   should_jump = (flags == FL_LT);
                if (opcode == OP_JLE)  should_jump = (flags == FL_LT || flags == FL_EQ);

                if (should_jump) {
                    if (target_line < 0 || target_line >= line_count) {
                        printf("Runtime Error: Jump target out of bounds!\n");
                        return 1;
                    }
                    ip = target_line - 1;
                }
                break;
            }
            case OP_HALT:
                ip = line_count;
                break;

            default:
                printf("Unknown instruction opcode: 0x%04X (string: %s)\n", opcode, cmd);
                return 1;
        }
        
        if (opcode == OP_HALT) break;
    }

    // ==================== CLEANUP PHASE ====================
    // Free all allocated memory to prevent leaks
    for (int i = 0; i < line_count; i++) {
        for (int j = 0; j < lines[i].token_count; j++) {
            free(lines[i].tokens[j]);
        }
        free(lines[i].tokens);
    }
    free(lines);
    fclose(fptr);

    return 0;

}