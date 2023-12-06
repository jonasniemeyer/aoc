#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint64_t part1(FILE *file);
uint64_t part2(FILE *file);
uint64_t winning_hands_count(char *line);

#define MAX_LINE    1000

int main()
{
    FILE *file = fopen("input04.txt", "r");
    printf("Part 1: %llu\n", part1(file));
    rewind(file);
    printf("Part 2: %llu\n", part2(file));
}

uint64_t part1(FILE *file)
{
    uint64_t sum = 0;
    char line[MAX_LINE];

    while (fgets(line, MAX_LINE, file)) {
        sum += ((uint64_t)1 << (winning_hands_count(line)-1));
    }

    return sum;
}

uint64_t part2(FILE *file)
{
    uint64_t sum = 0;
    char line[MAX_LINE];
    size_t total_lines = 0;
    size_t current_line = 0;

    while (fgets(line, MAX_LINE, file)) {
        total_lines++;
    }
    rewind(file);

    size_t *card_count = malloc(sizeof(size_t) * total_lines);
    for (size_t i = 0; i < total_lines; i++) {
        card_count[i] = 1;
    }

    while (fgets(line, MAX_LINE, file)) {
        sum += card_count[current_line];

        for (size_t offset = 1; offset < winning_hands_count(line)+1; offset++) {
            if ((current_line+offset) <= total_lines) {
                card_count[current_line+offset] += card_count[current_line];
            }
        }

        current_line++;
    }

    free(card_count);
    return sum;
}

uint64_t winning_hands_count(char *line)
{
    #define IN  1
    #define OUT 0

    uint64_t total = 0;
    uint64_t number;
    uint64_t winners[100];
    size_t no_winners = 0;
    size_t in_part = OUT, in_number = OUT;
    char number_str[10];
    char *ptr = &number_str[0];

    // insert winning numbers
    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] == '|') break;

        if (line[i] == ':') {
            in_part = IN;
        }
    
        if (!in_part) {
            continue;
        }

        if (isdigit(line[i])) {
            in_number = IN;
            *ptr++ = line[i];
        } else if (in_number == IN) {
            in_number = OUT;
            *ptr = '\0';
            ptr = &number_str[0];
            winners[no_winners++] = atoi(number_str);
        }
    }

    // evaluate our numbers
    in_part = OUT;
    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] == '|') {
            in_part = IN;
        }

        if (!in_part) {
            continue;
        }

        if (isdigit(line[i])) {
            in_number = IN;
            *ptr++ = line[i];
        } else if (in_number == IN) {
            in_number = OUT;
            *ptr = '\0';
            ptr = &number_str[0];
            number = atoi(number_str);
            for (size_t j = 0; j < no_winners; j++) {
                if (number == winners[j]) {
                    total += 1;
                    break;
                }
            }
        }
    }

    return total;
}