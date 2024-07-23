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

/*
 * Complete the 'minimumNumber' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING password
 */

/*
 * Length is atleast 6
 * Contains atleast one digit
 * Contains atleast one english lowercase Character
 * Contains atleast one english uppercase Character
 * Contains atleast one Special Character
*/

int minimumNumber(int n, char* password) {
    // Initialize the Flags to check the Presence of each required character type
    bool has_digit = false;
    bool has_lower = false;
    bool has_upper = false;
    bool has_special = false;    

    // Define the set of special Characters
    char* special_characters = "!@#$%^&*()-+";

    // Loop through each character in the Password 
    for (int i = 0; i < n; i++) {
        if (isdigit(password[i])) {
            // Check if the character is a digit
            has_digit = true;
        } else if (islower(password[i])) {
            // Check if the Character is a lowercase letter
            has_lower = true;
        } else if (isupper(password[i])) {
            // Check if the character is an Uppercase letter
            has_upper = true;
        } else if (strchr(special_characters, password[i])) {
            // Check if the Character is special character
            has_special = true;
        }
    }

    // Initialze a Counter for the number of missing character types
    int missing_types = 0;
    // Increment if No digit is Found 
    if (!has_digit) {
        missing_types++;
    }
    // Increment is no lowercase is Found
    if (!has_lower) {
        missing_types++;
    }
    // Increment if no uppercase Letter is found
    if (!has_upper) {
        missing_types++;
    }
    // Increment if No special Character is found
    if (!has_special) {
        missing_types++;
    }

    // Calculate the Number of additional characters needed to meet the minimum length requirement
    int additional_characters_needed = (n < 6) ? (6 - n) : 0;

    // Return the maximum of missing characters types and additional characters needed
    return (missing_types > additional_characters_needed) ? missing_types : additional_characters_needed;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char* password = readline();

    int answer = minimumNumber(n, password);

    fprintf(fptr, "%d\n", answer);

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
    