#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

uint64_t part1(FILE *file);
uint64_t part2(FILE *file);
uint64_t line_sum(char *line, char* line_above, char* line_below);
uint64_t gear_sumproduct(char *line, char* line_above, char* line_below);
uint64_t extract_number(char *line, size_t index);

#define MAX_LINE    1000

int main()
{
    FILE *file = fopen("input03.txt", "r");
    printf("Part 1: %llu\n", part1(file));
    rewind(file);
    printf("Part 2: %llu\n", part2(file));
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

    fgets(line_middle, MAX_LINE, file);

    while (fgets(line_below, MAX_LINE, file)) {
        sum += line_sum(line_middle, line_above, line_below);
        strcpy(line_above, line_middle);
        strcpy(line_middle, line_below);
    }

    // set imaginary line below last line
    for (size_t i = 0; i < MAX_LINE; i++) {
        line_below[i] = '.';
    }
    sum += line_sum(line_middle, line_above, line_below);

    return sum;
}

uint64_t part2(FILE *file)
{
    char line_above[MAX_LINE];
    char line_middle[MAX_LINE];
    char line_below[MAX_LINE];
    uint64_t sum = 0;

    // set imaginary line above first line
    for (size_t i = 0; i < MAX_LINE; i++) {
        line_above[i] = '.';
    }

    fgets(line_middle, MAX_LINE, file);

    size_t line_counter = 0;
    while (fgets(line_below, MAX_LINE, file)) {
        line_counter += 1;
        sum += gear_sumproduct(line_middle, line_above, line_below);
        strcpy(line_above, line_middle);
        strcpy(line_middle, line_below);
    }

    return sum;
}

uint64_t line_sum(char *line, char* line_above, char* line_below)
{
    #define IN  1
    #define OUT 0

    uint64_t sum = 0;
    uint8_t valid_no;
    uint8_t state = OUT;
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

uint64_t gear_sumproduct(char *line, char* line_above, char* line_below)
{
    uint64_t sum = 0;

    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] != '*') {
            continue;
        }
        uint64_t number = 1;
        size_t total = 0;
        size_t left_index;

        // take care of leftmost asterisks
        if (i == 0) {
            left_index = 0;
        } else {
            left_index = i-1;
        }

        // check left
        if (isdigit(line[left_index])) {
            number *= extract_number(line, left_index);
            total += 1;
        }
        
        // check right
        if (isdigit(line[i+1])) {
            number *= extract_number(line, i+1);
            total += 1;
        }

        // check above
        if (isdigit(line_above[left_index])) {
            number *= extract_number(line_above, left_index);
            total += 1;
            if (!isdigit(line_above[i]) && isdigit(line_above[i+1])) {
                number *= extract_number(line_above, i+1);
                total += 1;
            }
        } else if (isdigit(line_above[i])) {
            number *= extract_number(line_above, i);
            total += 1;
        } else if (isdigit(line_above[i+1])) {
            number *= extract_number(line_above, i+1);
            total += 1;
        }

        // check below
        if (isdigit(line_below[left_index])) {
            number *= extract_number(line_below, left_index);
            total += 1;
            if (!isdigit(line_below[i]) && isdigit(line_below[i+1])) {
                number *= extract_number(line_below, i+1);
                total += 1;
            }
        } else if (isdigit(line_below[i])) {
            number *= extract_number(line_below, i);
            total += 1;
        } else if (isdigit(line_below[i+1])) {
            number *= extract_number(line_below, i+1);
            total += 1;
        }

        if (total == 2) {
            sum += number;
        }
    }

    return sum;
}

uint64_t extract_number(char *line, size_t index)
{
    char number[10];
    char *ptr = &number[0];

    while ((index != 0) && isdigit(line[--index])) {
    }

    while (isdigit(line[++index])) {
        *ptr++ = line[index];
    }
    *ptr = '\0';

    return atoi(number);
}