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
 * Complete the 'dayOfProgrammer' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts INTEGER year as parameter.
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
char* dayOfProgrammer(int year) {
    static char date[11]; // To store the result date in format dd.mm.yyyy
    
    if (year < 1918) {
        // Julian calendar
        if (year % 4 == 0) {
            // Leap year in Julian calendar
            snprintf(date, sizeof(date), "12.09.%d", year);
        } else {
            // Non-leap year in Julian calendar
            snprintf(date, sizeof(date), "13.09.%d", year);
        }
    } else if (year == 1918) {
        // Transition year
        snprintf(date, sizeof(date), "26.09.1918");
    } else {
        // Gregorian calendar
        if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
            // Leap year in Gregorian calendar
            snprintf(date, sizeof(date), "12.09.%d", year);
        } else {
            // Non-leap year in Gregorian calendar
            snprintf(date, sizeof(date), "13.09.%d", year);
        }
    }

    return date;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int year = parse_int(ltrim(rtrim(readline())));

    char* result = dayOfProgrammer(year);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

    return 0;
}
