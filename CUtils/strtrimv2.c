#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50

/* 
This function will return a trimmed version of the string
without the left and right spaces
*/

int get_strlen(char* str) {
    int size = 0;
    while(*str) {
        size++;
        *str++;
    }
    return size;
}

char* first_trim(char* str) {
    while(isspace(*str)) {
        str++;
    }
    return str;
}

char* last_trim(char* str) {
    char* back = str + get_strlen(str);
    while(isspace(*--back));
    *(back+1) = '\0';
    return str;
}

char* strtrim(char* str){
    return last_trim(first_trim(str)); 
}

int main() {
    char* str = malloc(sizeof(int) * MAX);
    
    fgets(str, MAX, stdin);
    str = strtrim(str);
    printf("%s.\n", str);

    return 0;
}