#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char **tokens;
    int token_count;
} Line;

typedef struct
{
    bool mutability;
    char *type;
    char *name;
    char *value;
} Variable;
typedef struct
{
    char **lines;
    int count;
    int capacity;
} Output_Code;

void init_output_code(Output_Code *oc)
{
    oc->lines = NULL;
    oc->count = 0;
    oc->capacity = 0;
}

void parse_line(const char *buffer, Line *line)
{
    char temp[1024];
    int temp_idx = 0;
    bool in_quotes = false;
    char quote_type = 0;

    for (int i = 0; buffer[i] != '\0'; i++)
    {
        char c = buffer[i];

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

    if (temp_idx > 0)
    {
        temp[temp_idx] = '\0';
        line->tokens = realloc(line->tokens, (line->token_count + 1) * sizeof(char *));
        line->tokens[line->token_count++] = strdup(temp);
    }
}

int main()
{
    FILE *fptr = fopen("code.as", "r");
    if (!fptr)
    {
        perror("Error");
        return -1;
    }

    Line *lines = NULL;
    int line_count = 0;
    char buffer[1024];

    Output_Code myCode;
    init_output_code(&myCode);

    Variable *variables = NULL;
    int vars_count = 0;

    // Read file and tokenize
    while (fgets(buffer, sizeof(buffer), fptr))
    {
        char *comment_ptr = strstr(buffer, "//");
        if (comment_ptr)
            *comment_ptr = '\0';

        char *semi = strchr(buffer, ';');
        if (semi)
            *semi = '\0';

        if (strspn(buffer, " \t\n\r\f\v") == strlen(buffer))
            continue;

        lines = realloc(lines, (line_count + 1) * sizeof(Line));
        lines[line_count].tokens = NULL;
        lines[line_count].token_count = 0;

        parse_line(buffer, &lines[line_count]);
        line_count++;
    }

    // Output
    for (int i = 0; i < line_count; i++)
    {
        printf("Line %d: ", i);
        for (int j = 0; j < lines[i].token_count; j++)
        {
            printf("[%s] ", lines[i].tokens[j]);
        }

        printf("\n");
    }

    for (int i = 0; i < line_count; i++)
    {
        if (strcmp(lines[i].tokens[0], "let") == 0)
        {
            printf("let");
        }
        else if (strcmp(lines[i].tokens[0], "echo") == 0)
        {
            printf("echo");
        }
        else
        {
            continue;
        }

        printf("\n");
    }

    // Free memory
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

    return 0;
}