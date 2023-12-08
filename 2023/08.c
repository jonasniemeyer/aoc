#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint64_t part1(FILE *file);
uint64_t part2(FILE *file);
uint64_t parse_steps(FILE *file, uint8_t steps[]);
uint64_t parse_elements(FILE *file, uint16_t elements[], uint16_t left_elements[], uint16_t right_elements[]);
uint64_t compute_total_steps_p1(uint16_t element, uint16_t left_elements[], uint16_t right_elements[], uint8_t steps[], uint64_t step_arr_length);
uint64_t compute_total_steps_p2(uint16_t element, uint16_t left_elements[], uint16_t right_elements[], uint8_t steps[], uint64_t step_arr_length);
uint64_t compute_lowest_common_multiplicative(uint16_t numbers[], uint64_t arr_length);
uint64_t compute_greatest_common_divisor(uint64_t a, uint64_t b);

#define MAX_LINE        1000
#define MAX_STEPS       1000
#define MAX_ELEMENTS    65536

int main()
{
    FILE *file = fopen("input08.txt", "r");
    printf("Part 1: %llu\n", part1(file));
    rewind(file);
    printf("Part 2: %llu\n", part2(file));
    fclose(file);
}

uint64_t part1(FILE *file)
{
    uint8_t steps[MAX_STEPS];
    uint16_t elements[MAX_ELEMENTS]; // only needed in part 2
    uint16_t left_elements[MAX_ELEMENTS];
    uint16_t right_elements[MAX_ELEMENTS];

    uint64_t step_arr_length = parse_steps(file, steps);
    uint64_t total_elements = parse_elements(file, elements, left_elements, right_elements);

    uint16_t element = 0;
    return compute_total_steps_p1(element, left_elements, right_elements, steps, step_arr_length);
}

uint64_t part2(FILE *file)
{
    uint8_t steps[MAX_STEPS];
    uint16_t elements[MAX_ELEMENTS];
    uint16_t left_elements[MAX_ELEMENTS];
    uint16_t right_elements[MAX_ELEMENTS];

    uint64_t step_arr_length = parse_steps(file, steps);
    uint64_t total_elements = parse_elements(file, elements, left_elements, right_elements);

    for (size_t i = 0; i < total_elements; i++) {
        elements[i] = compute_total_steps_p2(elements[i], left_elements, right_elements, steps, step_arr_length);
    }

    return compute_lowest_common_multiplicative(elements, total_elements);
}

uint64_t compute_total_steps_p1(uint16_t element, uint16_t left_elements[], uint16_t right_elements[], uint8_t steps[], uint64_t step_arr_length)
{
    uint16_t destination = (('Z'-'A') << 10) | (('Z'-'A') << 5) | (('Z'-'A'));
    uint64_t total_steps = 0;

    while (1) {
        for (size_t j = 0; j < step_arr_length; j++) {
            if (element == destination) {
                return total_steps;
            }

            if (steps[j] == 0) {
                element = left_elements[element];
            } else {
                element = right_elements[element];
            }
            total_steps++;
        }
    }
}

uint64_t compute_total_steps_p2(uint16_t element, uint16_t left_elements[], uint16_t right_elements[], uint8_t steps[], uint64_t step_arr_length)
{
    uint16_t destination = ('Z'-'A');
    uint64_t total_steps = 0;

    while (1) {
        for (size_t j = 0; j < step_arr_length; j++) {
            if ((element & 0b11111) == destination) {
                return total_steps;
            }

            if (steps[j] == 0) {
                element = left_elements[element];
            } else {
                element = right_elements[element];
            }
            total_steps++;
        }
    }
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

uint64_t parse_elements(FILE *file, uint16_t elements[], uint16_t left_elements[], uint16_t right_elements[])
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
        if ((element & 0b11111) == ('A'-'A')) {
            elements[index] = element;
            index++;
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
    }

    return index;
}

uint64_t compute_lowest_common_multiplicative(uint16_t numbers[], uint64_t arr_length)
{
    uint64_t lcm = numbers[0];
    uint64_t gcd = numbers[0];
 
    for(size_t i = 1; i < arr_length; i++) {
        gcd = compute_greatest_common_divisor(numbers[i], lcm);
        lcm = (lcm*numbers[i])/gcd;
    }

    return lcm;
}

uint64_t compute_greatest_common_divisor(uint64_t a, uint64_t b)
{
    if (b==0) return a;
    return compute_greatest_common_divisor(b, a % b);
}