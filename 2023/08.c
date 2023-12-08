#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint64_t part1(FILE *file);
uint64_t parse_steps(FILE *file, uint8_t steps[]);
uint64_t parse_elements(FILE *file, uint16_t left_elements[], uint16_t right_elements[]);
uint64_t compute_steps(uint8_t steps[], uint16_t left_elements[], uint16_t right_elements[]);

#define MAX_LINE        1000
#define MAX_STEPS       1000
#define MAX_ELEMENTS    65536

int main()
{
    FILE *file = fopen("input08.txt", "r");
    printf("Part 1: %llu\n", part1(file));
    rewind(file);
    fclose(file);
}

uint64_t part1(FILE *file)
{
    uint8_t steps[MAX_STEPS];
    uint16_t left_elements[MAX_ELEMENTS];
    uint16_t right_elements[MAX_ELEMENTS];

    uint64_t total_steps = parse_steps(file, steps);
    uint64_t total_elements = parse_elements(file, left_elements, right_elements);

    uint16_t element = 0;
    uint16_t destination = (('Z'-'A') << 10) | (('Z'-'A') << 5) | (('Z'-'A'));

    uint64_t total = 0;
    while (element != destination) {
        for (size_t i = 0; i < total_steps; i++) {
            if (element == destination) break;
            if (steps[i] == 0) {
                element = left_elements[element];
            } else {
                element = right_elements[element];
            }
            total++;
        }
    }

    return total;
}

uint64_t parse_steps(FILE *file, uint8_t steps[])
{
    char line[MAX_LINE];
    uint64_t index = 0;
    
    fgets(line, MAX_LINE, file);
    for (size_t i = 0; i < strlen(line); i++) {
        switch (line[i]) {
            case 'L':
                steps[index++] = 0;
                break;
            case 'R':
                steps[index++] = 1;
                break;
        }
    }

    return index;
}

uint64_t parse_elements(FILE *file, uint16_t left_elements[], uint16_t right_elements[])
{
    char line[MAX_LINE];
    uint64_t index = 0;
    
    while (fgets(line, MAX_LINE, file)) {
        if (!strcmp(line, "\n")) continue;

        uint8_t bit_offset;
        uint16_t number, element;

        bit_offset = 10;
        element = 0;
        for (size_t i = 0; i < 3; i++) {
            element = element | ((line[i]-'A') << bit_offset);
            bit_offset -= 5;
        }

        bit_offset = 10;
        number = 0;
        for (size_t i = 7; i < 10; i++) {
            number = number | ((line[i]-'A') << bit_offset);
            bit_offset -= 5;
        }
        left_elements[element] = number;

        bit_offset = 10;
        number = 0;
        for (size_t i = 12; i < 15; i++) {
            number = number | ((line[i]-'A') << bit_offset);
            bit_offset -= 5;
        }
        right_elements[element] =  number;
        index++;
    }

    return index;
}