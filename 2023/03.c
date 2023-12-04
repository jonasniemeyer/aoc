#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

uint64_t part1(FILE *file);
uint64_t line_sum(char *line, char* line_above, char* line_below);

#define MAX_LINE    1000

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    printf("%llu", part1(file));
}

uint64_t part1(FILE *file)
{
    char line_above[MAX_LINE];
    char line_middle[MAX_LINE];
    char line_below[MAX_LINE];
    uint64_t sum = 0;

    // set imaginary line above first line
    for (size_t i = 0; i < MAX_LINE; i++) {
        line_above[i] = '.';
    }

    size_t line_counter = 0;
    while (fgets(line_below, MAX_LINE, file)) {
        line_counter++;

        if (line_counter >= 2) {
            sum += line_sum(line_middle, line_above, line_below);
            strcpy(line_above, line_middle);
        }

        strcpy(line_middle, line_below);
    }

    // set imaginary line below last line
    for (size_t i = 0; i < MAX_LINE; i++) {
        line_below[i] = '.';
    }
    sum += line_sum(line_middle, line_above, line_below);

    return sum;
}

uint64_t line_sum(char *line, char* line_above, char* line_below)
{
    #define IN  1
    #define OUT 0

    uint64_t sum = 0;
    uint8_t state = OUT;
    uint8_t valid_no;
    char number_str[10] = "\0";
    char *ptr = &number_str[0];

    for (size_t i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
            // check left side for the first number if necessary
            if ((state == OUT) && i != 0) {
                if (
                    (!isdigit(line_above[i-1]) && (line_above[i-1] != '.')) ||
                    (!isdigit(line[i-1]) && (line[i-1] != '.'))             ||
                    (!isdigit(line_below[i-1]) && (line_below[i-1] != '.'))
                ) {
                    valid_no = 1;
                } else {
                    valid_no = 0;
                }

                state = IN;
            }

            // check above and below
            if (
                !valid_no &&
                (!isdigit(line_above[i]) && (line_above[i] != '.')) ||
                (!isdigit(line_below[i]) && (line_below[i] != '.'))
            ) {
                valid_no = 1;
            }

            *ptr = line[i];
            ptr++;

        } else if (state == IN) {
            state = OUT;
            // check right side for the last number
            if (
                !valid_no &&
                (!isdigit(line_above[i]) && (line_above[i] != '.') && (line_above[i] != '\n'))  ||
                (!isdigit(line[i]) && (line[i] != '.') && (line[i] != '\n'))                    ||
                (!isdigit(line_below[i]) && (line_below[i] != '.') && (line_below[i] != '\n'))
            ) {
                valid_no = 1;
            }

            if (valid_no) {
                *ptr = '\0';
                sum += atoi(number_str);
            }

            ptr = &number_str[0];
        }
    }

    return sum;
}