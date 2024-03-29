#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint64_t part1(FILE *file);
uint64_t compute_minimum_location(FILE *file, uint64_t *coordinates, uint64_t total_seeds);
uint64_t parse_line(char *line, uint64_t array[]);
void store_destinations(char* line, uint64_t array[], size_t index, uint64_t total_seeds);

#define MAX_LINE    1000

int main()
{
    FILE *file = fopen("input05.txt", "r");
    printf("Part 1: %llu\n", part1(file));
    rewind(file);
    fclose(file);
}

uint64_t part1(FILE *file)
{
    uint64_t *coordinates = malloc(sizeof(uint64_t) * 1000);
    char line[MAX_LINE];

    fgets(line, MAX_LINE, file);
    uint64_t total_seeds = parse_line(line, coordinates);
    uint64_t min = compute_minimum_location(file, coordinates, total_seeds);
    
    return min;
}

uint64_t compute_minimum_location(FILE *file, uint64_t *coordinates, uint64_t total_seeds)
{
    char line[MAX_LINE];
    size_t index = 0;

    while (fgets(line, MAX_LINE, file)) {
        if (!strcmp(line, "\n")) {
            // insert default destinations
            for (size_t i = 0; i < total_seeds; i++) {
                coordinates[i + (index+1)*total_seeds] = coordinates[i + index*total_seeds];
            }
            fgets(line, MAX_LINE, file);
            index++;
            continue;
        }
        // insert corresponding destinations if they exist
        store_destinations(line, coordinates, index, total_seeds);
    }

    // get minimum location
    uint64_t min = coordinates[(7*total_seeds)];
    for (size_t i = 1; i < total_seeds; i++) {
        if (coordinates[i + (7*total_seeds)] < min) min = coordinates[i + (7*total_seeds)];
    }

    return min;
}

uint64_t parse_line(char *line, uint64_t array[])
{
    #define IN  1
    #define OUT 0

    size_t index = 0;
    uint8_t state = OUT;
    uint64_t number = 0;

    for (size_t i = 0; i < strlen(line); i++) {
        if (isdigit(line[i])) {
            state = IN;
            number *= 10;
            number += (line[i] - '0');
        } else if (state == IN) {
            state = OUT;
            array[index++] = number;
            number = 0;
        }
    }

    return index;
}

void store_destinations(char* line, uint64_t array[], size_t map_number, uint64_t total_seeds)
{
    #define IN  1
    #define OUT 0

    size_t index = 0;
    uint8_t state = OUT;
    uint64_t number = 0;
    uint64_t data[3]; // {destination, source, range}

    parse_line(line, data);

    // for each source element, check if there is a destination map and replace the default map with it
    for (size_t i = 0; i < total_seeds; i++) {
        if ((array[i + (map_number-1)*total_seeds] >= data[1]) && (array[i + (map_number-1)*total_seeds] < (data[1] + data[2]))) {
            array[i + map_number*total_seeds] = data[0] + (array[i + (map_number-1)*total_seeds]-data[1]);
        }
    }
}