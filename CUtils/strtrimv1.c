#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50

/* 
This function will return a trimmed version of the string
without the left and right spaces and in-between duplicate
spaces as well
*/

int get_strlen(char* str) {
    int size = 0;
    while(*str) {
        size++;
        *str++;
    }
    return size;
}

void rmv_extra_spaces(char* str) {
    int i = 0, x = 0;
    for(; *(str + i); ++i) {
        if (!isspace(*(str+i)) || (i > 0 && !isspace(*(str + (i-1))))) {
            *(str + (x++)) = *(str + i);
        }
    }
    *(str + x) = '\0';
}

void rmv_last(char* str) {
    int last = get_strlen(str)-1;
    *(str + last) = '\0';
}

void strtrim(char* str) {
    rmv_extra_spaces(str);
    rmv_last(str);
}

int main()
{
    char* str = malloc(sizeof(int) * MAX);
    
    fgets(str, MAX, stdin);
    strtrim(str);
    printf("%s.\n", str);

    return 0;
}