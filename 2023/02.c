#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

uint64_t part1(FILE *file);
uint64_t part2(FILE *file);
void parse_line(char *line, char **colors, uint64_t *values);
uint64_t limit_overflow(uint64_t values[], uint64_t limits[]);

#define MAX_LINE    1000

int main()
{
    FILE *file = fopen("input02.txt", "r");
    printf("Part 1: %llu\n", part1(file));
    rewind(file);
    printf("Part 2: %llu\n", part2(file));
    fclose(file);
}

uint64_t part1(FILE *file)
{
    char line[MAX_LINE];
    char *colors[] = {"red", "green", "blue"};
    uint64_t limits[] = {12, 13, 14};

    uint64_t sum = 0;
    uint64_t line_count = 0;

    while (fgets(line, MAX_LINE, file)) {
        uint64_t values[] = {0, 0, 0};
        line_count++;
        
        parse_line(line, colors, values);
        if (!limit_overflow(values, limits)) sum += line_count;
    }

    return sum;
}

uint64_t part2(FILE *file)
{
    char line[MAX_LINE];
    char *colors[] = {"red", "green", "blue"};

    uint64_t sum = 0;

    while (fgets(line, MAX_LINE, file)) {
        uint64_t values[] = {0, 0, 0};
        uint64_t line_prod = 1;

        parse_line(line, colors, values);
        for (size_t i = 0; i < 3; i++) {
            line_prod *= values[i];
        }
        sum += line_prod;
    }

    return sum;
}

void parse_line(char *line, char **colors, uint64_t *values)
{
    for (size_t index = 0; index < strlen(line); index++) {
        for (size_t i = 0; i < 3; i++) {
            if (strncmp(&line[index], colors[i], strlen(colors[i])) == 0) {
                int64_t offset = -2;
                uint64_t number = 0;
                uint64_t base = 1;
                while (isdigit(line[index+offset])) {
                    number += (line[index+offset]-'0') * base;
                    offset -= 1;
                    base *= 10;
                }
                if (number > values[i]) values[i] = number;
            }
        }
    }
}

uint64_t limit_overflow(uint64_t values[], uint64_t limits[]) {
    for (size_t i = 0; i < 3; i++) {
        if (values[i] > limits[i]) return 1;
    }
    return 0;
}