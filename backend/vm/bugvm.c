#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define OP_PUSH             0x0001 // push value on the stack
#define OP_PUSH_INT         0x0002 // push int value on the stack
#define OP_PUSH_STR         0x0003 // push str value on the stack
#define OP_PUSH_FLOAT       0x0004 // push float value on the stack
#define OP_POP              0x0005 // pop value from the stack
#define OP_ADD              0x0006 // add two last values from the stack
#define OP_SUB              0x0007 // sub two last values from the stack
#define OP_MUL              0x0008 // mul two last values from the stack
#define OP_DIV              0x0009 // div two last values from the stack
#define OP_PRINT            0x000A // print the value from the stack
#define OP_INPUT            0x000B // read value to the stack
#define OP_STORE            0x000C // store value from the stack in a local variable
#define OP_LOAD             0x000D // put a value from locals onto stack
#define OP_CMP              0x000E // compare two top values from stack and set flags
#define OP_JMP              0x000F // unconditional jump to a target line
#define OP_JNZ              0x0010 // jump to a target line if flag is not zero
#define OP_JZ               0x0011 // jump to a target line if flag is zero
#define OP_JNE              0x0012 // jump if not equal (flags != FL_EQ)
#define OP_JE               0x0013 // jump if equal (flags == FL_EQ)
#define OP_JGE              0x0014 // jump if greater or equal (flags == FL_GT || flags == FL_EQ)
#define OP_JG               0x0015 // jump if greater (flags == FL_GT)
#define OP_JLE              0x0016 // jump if less or equal (flags == FL_LT || flags == FL_EQ)
#define OP_JL               0x0017 // jump if less (flags == FL_LT)
#define OP_AND              0x0018 // logical AND
#define OP_OR               0x0019 // logical OR
#define OP_NOT              0x001A // logical NOT
#define OP_CALL             0x001B // call function
#define OP_RET              0x001C // return from function
#define OP_STRLEN           0x001D // gets first string value from the stack and then return its len
#define OP_STRCMP           0x001E // compare string
#define OP_LABEL            0x001F // create label
#define OP_PRT_STACK        0x0020 // print last value on stack and it position
#define OP_PRT_ALL_STACK    0x0021 // print all value on the stack and their positions
#define OP_PRT_LOCAL        0x0022 // print last value in local storage and it position
#define OP_PRT_ALL_LOCAL    0x0023 // print all value in local storage and their positions
#define OP_HALT             0xFFFF // halt the program

typedef enum {
    FL_EQ,
    FL_GT,
    FL_LT
} CompareFlag;

CompareFlag flags;

typedef enum {
    VAL_INT,
    VAL_STR,
    VAL_FLOAT
} ValType;

typedef struct {
    ValType type;
    union {
        int as_int;
        char *as_str;
        double as_float;
    } value;
} Object;

typedef struct{
    char **tokens;
    int token_count;
} Line;

typedef struct {
    char *name;
    int line_count;
} Label;

#define STACK_SIZE (1024 * 1024 * 2)
#define LOCAL_SIZE (1024 * 1024 * 16)
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

void push_float(double val){
    Object obj;
    obj.type = VAL_FLOAT;
    obj.value.as_float = val;
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
    FILE *fptr = fopen("bytecode005.bbin", "r");
    if (!fptr)
    {
        perror("Error opening input file 'code.as'");
        return -1;
    }

    Line *lines = NULL;
    int line_count = 0;
    char buffer[1024];

    Label *labels = NULL;
    int label_count = 0;

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

    // ==================== COLLECTS ALL LABELS ====================
    for (int i = 0; i < line_count; i++) {
    if (lines[i].token_count == 0) continue;

    int opcode = (int)strtol(lines[i].tokens[0], NULL, 0);
    
    if (opcode == OP_LABEL) {
        if (lines[i].token_count < 2) {
            printf("Error: OP_LABEL requires a name/identifier!\n");
            exit(1);
        }

        labels = realloc(labels, (label_count + 1) * sizeof(Label));
        labels[label_count].name = strdup(lines[i].tokens[1]);
        labels[label_count].line_count = i;
        label_count++;
    }
}

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

            case OP_PUSH_INT: {
                double val = (int)strtol(lines[ip].tokens[1], NULL, 0);
                push_int(val);
                break;
            }

            case OP_PUSH_STR: {
                char *str_ptr = strdup(lines[ip].tokens[1]);
                push_str(str_ptr);
                break;
            }

            case OP_PUSH_FLOAT: {
                double val = (int)strtol(lines[ip].tokens[1], NULL, 0);
                push_float(val);
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
                else if (a.type == VAL_FLOAT && b.type == VAL_INT){
                    push_float(a.value.as_float + b.value.as_float);
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
                else if (a.type == VAL_FLOAT && b.type == VAL_INT){
                    push_float(a.value.as_float - b.value.as_float);
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
                else if (a.type == VAL_FLOAT && b.type == VAL_INT){
                    push_float(a.value.as_float * b.value.as_float);
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
                else if (a.type == VAL_FLOAT && b.type == VAL_FLOAT) {
                    if(b.value.as_float == 0){
                        printf("Error: cant divide by zero!");
                        exit(1);
                    }
                    push_int(a.value.as_float / b.value.as_float);
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
                    } else if (obj.type == VAL_FLOAT) {
                        printf("%f\n", obj.value.as_float);
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
                    printf("Error: required argument!\n");
                    printf("Error on %d line\n", line_count);
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
                    printf("Error: ruquired argument!\n");
                    printf("Error on %d line\n", line_count);
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

                bool a_is_num = (a.type == VAL_INT || a.type == VAL_FLOAT);
                bool b_is_num = (b.type == VAL_INT || b.type == VAL_FLOAT);

                if (!a_is_num || !b_is_num) {
                    printf("Runtime Error: OP_CMP supports INTEGER and FLOAT comparison only!\n");
                    return 1;
                }

                double val_a = (a.type == VAL_INT) ? (double)a.value.as_int : a.value.as_float;
                double val_b = (b.type == VAL_INT) ? (double)b.value.as_int : b.value.as_float;

                if (val_a == val_b) {
                    flags = FL_EQ;
                } else if (val_a > val_b) {
                    flags = FL_GT;
                } else {
                    flags = FL_LT;
                }

                break;
            }

            case OP_JMP: {
                if (lines[ip].token_count < 2) {
                    printf("Runtime Error: OP_JMP requires a target label!\n");
                    return 1;
                }
                
                char *target_name = lines[ip].tokens[1];
                int target_line = -1;

                for (int i = 0; i < label_count; i++) {
                    if (strcmp(labels[i].name, target_name) == 0) {
                        target_line = labels[i].line_count;
                        break;
                    }
                }

                if (target_line == -1) {
                    printf("Runtime Error: Label '%s' not found!\n", target_name);
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

            case OP_AND: {
                Object b = pop();
                Object a = pop();

                bool truth_a = false;
                bool truth_b = false;

                if (a.type == VAL_INT) truth_a = (a.value.as_int != 0);
                else if (a.type == VAL_FLOAT) truth_a = (a.value.as_float != 0.0);
                else if (a.type == VAL_STR) truth_a = (a.value.as_str != NULL && a.value.as_str[0] != '\0');

                if (b.type == VAL_INT) truth_b = (b.value.as_int != 0);
                else if (b.type == VAL_FLOAT) truth_b = (b.value.as_float != 0.0);
                else if (b.type == VAL_STR) truth_b = (b.value.as_str != NULL && b.value.as_str[0] != '\0');

                if (a.type == VAL_STR) free(a.value.as_str);
                if (b.type == VAL_STR) free(b.value.as_str);

                push_int((truth_a && truth_b) ? 1 : 0);
                break;
            }

            case OP_OR: {
                Object b = pop();
                Object a = pop();

                bool truth_a = false;
                bool truth_b = false;

                if (a.type == VAL_INT) truth_a = (a.value.as_int != 0);
                else if (a.type == VAL_FLOAT) truth_a = (a.value.as_float != 0.0);
                else if (a.type == VAL_STR) truth_a = (a.value.as_str != NULL && a.value.as_str[0] != '\0');

                if (b.type == VAL_INT) truth_b = (b.value.as_int != 0);
                else if (b.type == VAL_FLOAT) truth_b = (b.value.as_float != 0.0);
                else if (b.type == VAL_STR) truth_b = (b.value.as_str != NULL && b.value.as_str[0] != '\0');

                if (a.type == VAL_STR) free(a.value.as_str);
                if (b.type == VAL_STR) free(b.value.as_str);

                push_int((truth_a || truth_b) ? 1 : 0);
                break;
            }

            case OP_NOT: {
                Object a = pop();
                bool truth_a = false;

                if (a.type == VAL_INT) truth_a = (a.value.as_int != 0);
                else if (a.type == VAL_FLOAT) truth_a = (a.value.as_float != 0.0);
                else if (a.type == VAL_STR) truth_a = (a.value.as_str != NULL && a.value.as_str[0] != '\0');

                if (a.type == VAL_STR) free(a.value.as_str);

                push_int(!truth_a ? 1 : 0);
                break;
            }

            case OP_CALL:
                break;

            case OP_RET:
                break;

            case OP_STRCMP:{
                Object a = pop();
                Object b = pop();

                int cmp = strcmp(a.value.as_str, b.value.as_str);
                push_int(cmp);

                break;
            }

            case OP_STRLEN: {
                Object a = pop();

                if (a.type == VAL_INT) {
                    printf("Error: invalid type: INT!\n");
                    return 1;
                } else if (a.type == VAL_FLOAT) {
                    printf("Error: invalid type: FLOAT!\n");
                    return 1;
                } else if (a.type == VAL_STR) {
                    if (a.value.as_str == NULL) {
                        push_int(0);
                    } else {
                        int len = (int)strlen(a.value.as_str);
                        push_int(len);
                    }
                } else {
                    printf("Error: unknown type for OP_STRLEN!\n");
                    return 1;
                }
                break;
            }

            case OP_LABEL: {
                break;
            }

            case OP_PRT_STACK: {
                if (sp < 0) {
                    printf("Error: Stack is empty!\n");
                } else {
                    Object obj = stack[sp];
                    printf("Current stack position: %d, value: ", sp+1);
                    
                    if (obj.type == VAL_INT) {
                        printf("%d\n", obj.value.as_int);
                    } else if (obj.type == VAL_STR) {
                        printf("%s\n", obj.value.as_str);
                    } else if (obj.type == VAL_FLOAT) {
                        printf("%f\n", obj.value.as_float);
                    }
                }
                break;
            }

            case OP_PRT_LOCAL:
                break;

            case OP_PRT_ALL_STACK:{
                if (sp < 0){
                    printf("Error: Stack is empty!\n");
                } else {
                    Object obj = stack[sp];
                    for (int i; i <= sp; i++){
                        printf("Current stack position: %d, value: ", sp);
                    
                        if (obj.type == VAL_INT) {
                            printf("%d\n", obj.value.as_int);
                        } else if (obj.type == VAL_STR) {
                            printf("%s\n", obj.value.as_str);
                        } else if (obj.type == VAL_FLOAT) {
                            printf("%f\n", obj.value.as_float);
                        }
                    }
                }
                break;
            }

            case OP_PRT_ALL_LOCAL:
                break;

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

    for (int i = 0; i < label_count; i++) {
        free(labels[i].name);
    }
    free(labels);

    fclose(fptr);

    return 0;

}