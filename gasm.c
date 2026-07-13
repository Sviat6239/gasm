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

    char **globals;
    int global_count;
    int global_capacity;

    int tmp_count;
    int str_count;
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

const char *map_to_llvm_type(const char *lang_type);

Variable *find_variable(Variable *vars, int count, const char *name)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(vars[i].name, name) == 0)
            return &vars[i];
    }
    return NULL;
}

void add_global_line(Output_Code *oc, const char *line)
{
    if (oc->global_count >= oc->global_capacity)
    {
        oc->global_capacity = (oc->global_capacity == 0) ? 10 : oc->global_capacity * 2;
        oc->globals = realloc(oc->globals, sizeof(char *) * oc->global_capacity);
    }
    oc->globals[oc->global_count++] = strdup(line);
}

void add_global_string(Output_Code *oc, const char *name, const char *value)
{
    char buf[512];
    sprintf(buf, "%s = private unnamed_addr constant [%zu x i8] c\"%s\\00\"",
            name, strlen(value) + 1, value);
    add_global_line(oc, buf);
}

void write_output_to_file(Output_Code *oc, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
        return;

    fprintf(fp, "target triple = \"aarch64-w64-windows-gnu\"\n\n");

    fprintf(fp, "declare i32 @printf(i8*, ...)\n");
    fprintf(fp, "@.str.d = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
    fprintf(fp, "@.str.f = private unnamed_addr constant [4 x i8] c\"%%f\\0A\\00\"\n");
    fprintf(fp, "@.str.s = private unnamed_addr constant [3 x i8] c\"%%s\\00\"\n\n");

    for (int i = 0; i < oc->global_count; i++)
    {
        fprintf(fp, "%s\n", oc->globals[i]);
    }

    fprintf(fp, "\ndefine i32 @main() {\n");

    for (int i = 0; i < oc->count; i++)
    {
        fprintf(fp, "%s\n", oc->lines[i]);
    }

    fprintf(fp, "  ret i32 0\n");
    fprintf(fp, "}\n");

    fclose(fp);
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
    myCode.lines = NULL;
    myCode.count = 0;
    myCode.capacity = 0;
    myCode.globals = NULL;
    myCode.global_count = 0;
    myCode.global_capacity = 0;
    myCode.tmp_count = 0;
    myCode.str_count = 0;

    Variable *vars = NULL;
    int vars_count = 0;

    // Flags
    bool is_use_echo = false;

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

            const char *llvm_type = map_to_llvm_type(type);
            const char *storage_type = (strcmp(llvm_type, "float") == 0) ? "double" : llvm_type;
            if (strcmp(type, "str") == 0)
                storage_type = "i8*";

            Variable *existing = find_variable(vars, vars_count, name);
            char buf[256];

            if (existing == NULL)
            {
                sprintf(buf, "  %%%s = alloca %s", name, storage_type);
                add_line_to_code(&myCode, buf);
                add_variable(&vars, &vars_count, true, type, name, val);
            }

            if (strcmp(type, "str") == 0)
            {
                char str_label[32];
                sprintf(str_label, "@.str.%d", myCode.str_count++);
                add_global_string(&myCode, str_label, val);

                sprintf(buf, "  store i8* getelementptr ([%zu x i8], [%zu x i8]* %s, i32 0, i32 0), i8** %%%s",
                        strlen(val) + 1, strlen(val) + 1, str_label, name);
                add_line_to_code(&myCode, buf);
            }
            else
            {
                sprintf(buf, "  store %s %s, %s* %%%s", storage_type, val, storage_type, name);
                add_line_to_code(&myCode, buf);
            }
        }
        else if (strcmp(lines[i].tokens[0], "echo") == 0)
        {

            is_use_echo = true;

            char *name = lines[i].tokens[2];
            Variable *v = find_variable(vars, vars_count, name);
            if (!v)
            {
                printf("Error: Variable %s not found\n", name);
                continue;
            }

            const char *l_type = map_to_llvm_type(v->type);
            char buf[256];
            int id = myCode.tmp_count++;

            sprintf(buf, "  %%tmp%d = load %s, %s* %%%s", id, l_type, l_type, name);
            add_line_to_code(&myCode, buf);

            if (strcmp(v->type, "str") == 0)
            {
                sprintf(buf, "  call i32 (i8*, ...) @printf(i8* getelementptr ([3 x i8], [3 x i8]* @.str.s, i32 0, i32 0), i8* %%tmp%d)", id);
                add_line_to_code(&myCode, buf);
            }
            else if (strcmp(l_type, "float") == 0)
            {
                sprintf(buf, "  %%ext%d = fpext float %%tmp%d to double", id, id);
                add_line_to_code(&myCode, buf);
                sprintf(buf, "  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.f, i32 0, i32 0), double %%ext%d)", id);
                add_line_to_code(&myCode, buf);
            }
            else if (strcmp(l_type, "double") == 0)
            {
                sprintf(buf, "  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.f, i32 0, i32 0), double %%tmp%d)", id);
                add_line_to_code(&myCode, buf);
            }
            else
            {
                sprintf(buf, "  call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.d, i32 0, i32 0), %s %%tmp%d)", l_type, id);
                add_line_to_code(&myCode, buf);
            }
        }
        else if (strcmp(lines[i].tokens[0], "mov") == 0)
        {
        }
        else if (strcmp(lines[i].tokens[0], "$") == 0)
        {
        }
        else if (strcmp(lines[i].tokens[0], "jne") == 0)
        {
        }
        else if (strcmp(lines[i].tokens[0], "je") == 0)
        {
        }
        else if (strcmp(lines[i].tokens[0], "jge") == 0)
        {
        }
        else if (strcmp(lines[i].tokens[0], "jg") == 0)
        {
        }
        else if (strcmp(lines[i].tokens[0], "jle") == 0)
        {
        }
        else if (strcmp(lines[i].tokens[0], "jl") == 0)
        {
        }
        else if (strcmp(lines[i].tokens[0], "cmp") == 0)
        {
        }
    }

    // ==================== WRITE OUTPUT TO FILE ====================
    write_output_to_file(&myCode, "output.ll");
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

const char *map_to_llvm_type(const char *lang_type)
{
    if (strcmp(lang_type, "i8") == 0)
        return "i8";
    if (strcmp(lang_type, "i16") == 0)
        return "i16";
    if (strcmp(lang_type, "i32") == 0)
        return "i32";
    if (strcmp(lang_type, "i64") == 0)
        return "i64";

    if (strcmp(lang_type, "ui8") == 0)
        return "i8";
    if (strcmp(lang_type, "ui16") == 0)
        return "i16";
    if (strcmp(lang_type, "ui32") == 0)
        return "i32";
    if (strcmp(lang_type, "ui64") == 0)
        return "i64";

    if (strcmp(lang_type, "int8_t") == 0)
        return "i8";
    if (strcmp(lang_type, "int16_t") == 0)
        return "i16";
    if (strcmp(lang_type, "int32_t") == 0)
        return "i32";
    if (strcmp(lang_type, "int64_t") == 0)
        return "i64";

    if (strcmp(lang_type, "uint8_t") == 0)
        return "i8";
    if (strcmp(lang_type, "uint16_t") == 0)
        return "i16";
    if (strcmp(lang_type, "uint32_t") == 0)
        return "i32";
    if (strcmp(lang_type, "uint64_t") == 0)
        return "i64";

    if (strcmp(lang_type, "char") == 0)
        return "i8";
    if (strcmp(lang_type, "str") == 0)
        return "i8*";

    if (strcmp(lang_type, "f32") == 0 || strcmp(lang_type, "float") == 0)
        return "float";
    if (strcmp(lang_type, "f64") == 0 || strcmp(lang_type, "double") == 0)
        return "double";

    return "i64";
}