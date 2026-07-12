#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * Structure to hold tokenized line.
 * tokens - array of strings (each token)
 * token_count - number of tokens in the line
 */
typedef struct
{
    char **tokens;
    int token_count;
} Line;

/*
 * Represents a variable in our simple language.
 * mutability - whether the variable can be changed (true = mutable)
 * type       - data type (e.g. "int")
 * name       - variable name
 * value      - initial value as string
 */
typedef struct
{
    bool mutability;
    char *type;
    char *name;
    char *value;
} Variable;

/*
 * Structure to collect generated output code (LLVM IR in this case).
 * lines    - array of code lines
 * count    - current number of lines
 * capacity - allocated capacity for dynamic growth
 */
typedef struct
{
    char **lines;
    int count;
    int capacity;
} Output_Code;

/*
 * Initializes Output_Code structure with safe default values.
 */
void init_output_code(Output_Code *oc)
{
    oc->lines = NULL;
    oc->count = 0;
    oc->capacity = 0;
}

/*
 * Parses a single line into tokens, handling:
 * - quoted strings (preserves content inside "" and '')
 * - parentheses as separate tokens
 * - whitespace as delimiters
 * - basic escape support for quotes
 */
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
        // Handle parentheses as separate tokens when outside quotes
        else if (!in_quotes && (c == '(' || c == ')'))
        {
            if (temp_idx > 0)
            {
                temp[temp_idx] = '\0';
                line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
                line->tokens[line->token_count++] = strdup(temp);
                temp_idx = 0;
            }
            line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
            char bracket[2] = {c, '\0'};
            line->tokens[line->token_count++] = strdup(bracket);
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

/*
 * Adds a new variable to the variables array.
 * Dynamically resizes the array and duplicates strings.
 */
void add_variable(Variable **vars, int *count, bool mut, char *type, char *name, char *val)
{
    *vars = realloc(*vars, (*count + 1) * sizeof(Variable));

    Variable *v = &((*vars)[*count]);
    v->mutability = mut;
    v->type = strdup(type);
    v->name = strdup(name);
    v->value = strdup(val);

    (*count)++;
}

/*
 * Adds a line of generated code to the output buffer.
 * Automatically grows the buffer when needed.
 */
void add_line_to_code(Output_Code *oc, const char *text)
{
    if (oc->count >= oc->capacity)
    {
        oc->capacity = (oc->capacity == 0) ? 10 : oc->capacity * 2;
        oc->lines = realloc(oc->lines, oc->capacity * sizeof(char *));
    }

    oc->lines[oc->count] = strdup(text);
    oc->count++;
}

int main()
{
    // Open the source file
    FILE *fptr = fopen("code.as", "r");
    if (!fptr)
    {
        perror("Error opening input file 'code.as'");
        return -1;
    }

    Line *lines = NULL;
    int line_count = 0;
    char buffer[1024];

    Output_Code myCode;
    init_output_code(&myCode);

    Variable *vars = NULL;
    int vars_count = 0;

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

    // ==================== CODE GENERATION PHASE ====================
    printf("\n=== Generating output code ===\n");

    for (int i = 0; i < line_count; i++)
    {
        if (lines[i].token_count == 0)
            continue;

        if (strcmp(lines[i].tokens[0], "let") == 0)
        {
            char *type = lines[i].tokens[2];
            char *name = lines[i].tokens[3];
            char *val = lines[i].tokens[5];

            char llvm_type[16];
            if (strcmp(type, "i32") == 0)
                strcpy(llvm_type, "i32");
            else if (strcmp(type, "f32") == 0)
                strcpy(llvm_type, "float");
            else if (strcmp(type, "f64") == 0)
                strcpy(llvm_type, "double");
            else
                strcpy(llvm_type, "i64");

            char buf[256];
            sprintf(buf, "%%%s = alloca %s", name, llvm_type);
            add_line_to_code(&myCode, buf);

            sprintf(buf, "store %s %s, %s* %%%s", llvm_type, val, llvm_type, name);
            add_line_to_code(&myCode, buf);
        }
        else if (strcmp(lines[i].tokens[0], "echo") == 0)
        {
            add_line_to_code(&myCode, "there is the echo");
            printf("echo\n");
        }
        else
        {
            printf("Unknown command: %s\n", lines[i].tokens[0]);
            continue;
        }
    }

    // ==================== WRITE OUTPUT TO FILE ====================
    FILE *out_fptr = fopen("output.ll", "w");
    if (out_fptr == NULL)
    {
        perror("Unable to create output file 'output.ll'");
        return -1;
    }

    for (int i = 0; i < myCode.count; i++)
    {
        fprintf(out_fptr, "%s\n", myCode.lines[i]);
    }

    fclose(out_fptr);
    printf("Output written to output.ll\n");

    // ==================== CLEANUP PHASE ====================
    // Free all allocated memory to prevent leaks
    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < lines[i].token_count; j++)
        {
            free(lines[i].tokens[j]);
        }
        free(lines[i].tokens);
    }
    free(lines);

    fclose(fptr);

    free(myCode.lines);

    for (int i = 0; i < vars_count; i++)
    {
        free(vars[i].type);
        free(vars[i].name);
        free(vars[i].value);
    }
    free(vars);

    return 0;
}