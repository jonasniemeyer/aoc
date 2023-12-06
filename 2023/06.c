#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint64_t part1(FILE *file);
uint64_t part2(FILE *file);
uint64_t parse_line(FILE *file, uint64_t array[]);
uint64_t parse_line_part2(FILE *file);
uint64_t compute_possible_charges(uint64_t time, uint64_t record);

#define MAX_LINE    1000
#define MAX_RACES   100

int main()
{
    FILE *file = fopen("input06.txt", "r");
    printf("Part 1: %llu\n", part1(file));
    rewind(file);
    printf("Part 2: %llu\n", part2(file));
    fclose(file);
}

uint64_t part1(FILE *file)
{
    uint64_t time[MAX_RACES];
    uint64_t record[MAX_RACES];
    uint64_t margin_error = 1;

    uint64_t total_races = parse_line(file, time);
    parse_line(file, record);

    for (size_t i = 0; i < total_races; i++) {
        margin_error *= compute_possible_charges(time[i], record[i]);
    }

    return margin_error;
}

uint64_t part2(FILE *file)
{

    uint64_t time = parse_line_part2(file);
    uint64_t record = parse_line_part2(file);

    return compute_possible_charges(time, record);
}

uint64_t parse_line(FILE *file, uint64_t array[])
{
    #define IN  1
    #define OUT 0

    char line[MAX_LINE];
    size_t index = 0;
    uint8_t state = OUT;
    uint64_t number = 0;

    fgets(line, MAX_LINE, file);

    for (size_t i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
            state = IN;
            number *= 10;
            number += (line[i] - '0');
            if ((i == (strlen(line)-1))) {
                array[index++] = number;
            }
        } else if (state == IN) {
            state = OUT;
            array[index++] = number;
            number = 0;
        }
    }

    return index;
}

uint64_t parse_line_part2(FILE *file)
{
    char line[MAX_LINE];
    uint64_t number = 0;

    fgets(line, MAX_LINE, file);

    for (size_t i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
            number *= 10;
            number += (line[i] - '0');
        }
    }

    return number;
}

uint64_t compute_possible_charges(uint64_t time, uint64_t record)
{
    uint64_t total = 0;
    uint64_t distance;

    for (size_t charge = 1; charge < time; charge++) {
        if ((charge * (time-charge)) > record) total++;
    }

    return total;
}