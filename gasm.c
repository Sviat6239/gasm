#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **tokens;
    int token_count;
} Line;

int main() {
    FILE *fptr = fopen("code.as", "r");
    if (!fptr) { perror("Error"); return -1; }

    Line *lines = NULL;
    int line_count = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fptr)) {

        lines = realloc(lines, (line_count + 1) * sizeof(Line));
        lines[line_count].tokens = NULL;
        lines[line_count].token_count = 0;

        char *token = strtok(buffer, " \t\n\r");
        while (token != NULL) {
            int t_cnt = lines[line_count].token_count;
            lines[line_count].tokens = realloc(lines[line_count].tokens, (t_cnt + 1) * sizeof(char *));
            
            lines[line_count].tokens[t_cnt] = strdup(token);
            lines[line_count].token_count++;
            
            token = strtok(NULL, " \t\n\r");
        }
        line_count++;
    }

    for (int i = 0; i < line_count; i++) {
        printf("Line %d: ", i);
        for (int j = 0; j < lines[i].token_count; j++) {
            printf("[%s] ", lines[i].tokens[j]);
        }
        printf("\n");
    }

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