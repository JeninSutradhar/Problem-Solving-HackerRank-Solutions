/*
 * To solve this problem, we need to reduce a string by repeatedly 
 * removing pairs of adjacent matching characters until no such pairs remain.
 * We can use a stack to achieve this efficiently. As we iterate through 
 * the string, we'll push characters onto the stack, but if the top of
 * the stack matches the current character, we'll pop the stack instead
 * of pushing the current character.
*/
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();

char* superReducedString(char* s) {
    int length = strlen(s);

    // Allocate Memory for the Stack
    char* stack = (char*)malloc(length + 1);

    // This will act as the Index of our Stack
    int stackPointer = 0;

    for (int i = 0; i < length; i++) {
        if (stackPointer > 0 && stack[stackPointer - 1] == s[i]) {
            // If the top of the Stack matches the Current character, pop the Stack 
            stackPointer--;
        } else {
            // Otherwise, push the current character onto the Character
            stack[stackPointer++] = s[i];
        }
    }

    // Null termiate the Stack string
    stack[stackPointer] = '\0';

    if (stackPointer == 0) {
        // If the stack is Empty, return the empty String
        free(stack);
        return "Empty String";
    }

    // Allocate Exact memory for the result and copy the Stack Content
    char* result = (char*)malloc(stackPointer + 1);
    strncpy(result, stack, stackPointer + 1);

    free(stack);

    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = superReducedString(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}
