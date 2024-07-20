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
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'kangaroo' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER x1
 *  2. INTEGER v1
 *  3. INTEGER x2
 *  4. INTEGER v2
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* kangaroo(int x1, int v1, int x2, int v2) {
    // Check if the Second Kangaroo is already ahead and has a higher or Equal Velocity
    if (x1 < x2 && v1 <= v2) {
        return "NO";
    }

    // Check if the Velocities are the Same but the starting positions are different
    if (v1 == v2) {
        return "YES";
    }

    // Use the formula to determine if the kangaroos will meet:
    // (x1 + x2 * v1) == (x2 + n * v2) can be rearranged to:
    // n = (x2 - x1) / (v1 - v2)
    // And Check if 'n' is a Positive Integer
    if ((x2 - x1) % (v1 - v2) == 0 && (x2 - x1) / (v1 - v2) >= 0) {
        return "YES";
    }

    return "NO";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int x1 = parse_int(*(first_multiple_input + 0));

    int v1 = parse_int(*(first_multiple_input + 1));

    int x2 = parse_int(*(first_multiple_input + 2));

    int v2 = parse_int(*(first_multiple_input + 3));

    char* result = kangaroo(x1, v1, x2, v2);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}
