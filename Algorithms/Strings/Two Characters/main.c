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
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);


// Helper function to check if a string consists of only two alternating characters
bool is_valid_alternating_string(const char* s, char c1, char c2) {
    char last_char = '\0'; // Initialize to a character that won't match any valid input
    for (int i = 0; s[i] != '\0'; i++) {
        char current_char = s[i];
        // If current_char is neither c1 nor c2, return false
        if (current_char != c1 && current_char != c2) {
            return false;
        }
        // Check for consecutive same characters
        if (current_char == last_char) {
            return false;
        }
        last_char = current_char;
    }
    return true;
}

// Function to find the length of the longest valid alternating string
int alternate(char* s) {
    int n = strlen(s);
    // Array to keep track of unique characters
    bool present[26] = { false };

    // Mark the presence of each character in the input string
    for (int i = 0; i < n; i++) {
        present[s[i] - 'a'] = true;
    }

    // Iterate through all pairs of characters to find the longest valid alternating string
    int max_length = 0;
    for (int i = 0; i < 26; i++) {
        if (!present[i]) continue; // Skip if character is not present in the string
        for (int j = i + 1; j < 26; j++) {
            if (!present[j]) continue; // Skip if character is not present in the string
            char c1 = 'a' + i;
            char c2 = 'a' + j;
            char filtered_string[1001] = { 0 }; // Temporary string to store filtered results
            int index = 0;

            // Filter the string to keep only characters c1 and c2
            for (int k = 0; s[k] != '\0'; k++) {
                if (s[k] == c1 || s[k] == c2) {
                    filtered_string[index++] = s[k];
                }
            }
            filtered_string[index] = '\0'; // Null-terminate the filtered string

            // Check if the filtered string is a valid alternating string
            if (is_valid_alternating_string(filtered_string, c1, c2)) {
                if (index > max_length) {
                    max_length = index; // Update max_length if the current valid string is longer
                }
            }
        }
    }

    return max_length;
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int l = parse_int(ltrim(rtrim(readline())));

    char* s = readline();

    int result = alternate(s);

    fprintf(fptr, "%d\n", result);

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

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
