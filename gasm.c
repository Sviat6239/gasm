#include <stdio.h>
#include <string.h>

void split(char *s, char *d){
    char *ss = strtok(s, d);
    while(ss != NULL){
        printf("%s\n", ss);
        ss = strtok(NULL, d);
    }
}

int main(){

    int size = 100;

    char *s;
    
    FILE *fptr;

    fptr = fopen("code.as", "r");

    char myString[size];

    while(fgets(myString, size, fptr)) {
        s = myString;
        char *d = " ";

        split(s, d);
    }

    fclose(fptr);

    return 0;
}