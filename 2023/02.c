#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

uint64_t part1(FILE *file);
uint64_t part2(FILE *file);
uint8_t limit_overflow(char *line);
uint64_t largest_no_cubes(char *line, char* color);

#define MAX_LINE    1000

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    printf("Part 1: %llu\n", part1(file));
    rewind(file);
    printf("Part 2: %llu\n", part2(file));
}

uint64_t part1(FILE *file)
{
    char line[MAX_LINE];
    uint64_t sum = 0;
    uint8_t line_count = 0;

    while (fgets(line, MAX_LINE, file)) {
        line_count++;
        if (!limit_overflow(line)) {
            sum += line_count;
        }
    }

    return sum;
}

uint64_t part2(FILE *file)
{
    char line[MAX_LINE];
    uint64_t sum = 0;
    char *colors[] = {"red", "green", "blue"};

    while (fgets(line, MAX_LINE, file)) {
        uint64_t number = 1;
        for (size_t i = 0; i < 3; i++) {
            number *= largest_no_cubes(line, colors[i]);
        }
        sum += number;
    }

    return sum;
}

uint8_t limit_overflow(char *line)
{
    char *colors[] = {"red", "green", "blue"};
    uint8_t limits[] = {12, 13, 14};

    for (size_t index = 0; index < strlen(line); index++) {
        for (size_t i = 0; i < 3; i++) {
            if (strncmp(&line[index], colors[i], strlen(colors[i])) == 0) {
                int8_t offset = -2;
                uint8_t number = 0;
                uint8_t max = limits[i];
                uint8_t base = 1;
                while (isdigit(line[index+offset])) {
                    number += (line[index+offset]-'0') * base;
                    offset -= 1;
                    base *= 10;
                }
                if (number > limits[i]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

uint64_t largest_no_cubes(char *line, char* color)
{
    uint64_t max = 0;
    for (size_t index = 0; index < strlen(line); index++) {
        if (strncmp(&line[index], color, strlen(color)) == 0) {
            int8_t offset = -2;
            uint8_t number = 0;
            uint8_t base = 1;
            while (isdigit(line[index+offset])) {
                number += (line[index+offset]-'0') * base;
                offset -= 1;
                base *= 10;
            }
            if (number > max) {
                max = number;
            }
        }
    }
    return max;
}