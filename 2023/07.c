#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint64_t compute_winnings(FILE *file, uint64_t (*hand_parser)(char *line));
uint64_t parse_lines(FILE *file, uint64_t hands[], uint64_t bids[], uint64_t (*hand_parser)(char *line));
uint64_t parse_hand(char *line);
uint64_t parse_hand_p2(char *line);
uint64_t parse_bid(char *line);
void dual_sort(uint64_t *hands, uint64_t *bids, uint64_t total_elements);

#define MAX_LINE        1000
#define MAX_ELEMENTS    100000

int main()
{
    FILE *file = fopen("input07.txt", "r");
    printf("Part 1: %llu\n", compute_winnings(file, parse_hand));
    rewind(file);
    printf("Part 1: %llu\n", compute_winnings(file, parse_hand_p2));
    fclose(file);
}

uint64_t compute_winnings(FILE *file, uint64_t (*hand_parser)(char *line))
{
    uint64_t total_winnings = 0;
    uint64_t hands[MAX_ELEMENTS];
    uint64_t bids[MAX_ELEMENTS];

    uint64_t total_elements = parse_lines(file, hands, bids, hand_parser);
    dual_sort(hands, bids, total_elements);

    for (size_t i = 0; i < total_elements; i++) {
        total_winnings += (i+1) * bids[i];
    } 

    return total_winnings;
}

uint64_t parse_lines(FILE *file, uint64_t hands[], uint64_t bids[], uint64_t (*hand_parser)(char *line))
{
    char line[MAX_LINE];
    uint64_t index = 0;

    while (fgets(line, MAX_LINE, file)) {
        hands[index] = hand_parser(line);
        bids[index] = parse_bid(line);
        index++;
    }

    return index;
}

/*
Represent each hand by a 64bit integer
The first 12 bits represent the rightmost character, the bits 13 to 24 the second rightmost character and so on.
The final 4 bits represent the rank of the hand from 1 (high card, bit pattern 0000) to 7 (Five of a kind, bit pattern 0111).
With that, we can sort an array of 64 bit integers
Example (KJK2J Two Pair)
RRRR AKQJT9876543 AKQJT9876543 AKQJT9876543 AKQJT9876543 AKQJT9876543
0011 010000000000 000100000000 010000000000 000000000000 000100000000
*/
uint64_t parse_hand(char *line)
{
    uint64_t card = 0, bit_offset = 48;
    char cards[] = {'3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    uint64_t counts[13] = {0};

    for (size_t i = 0; i < 5; i++) {
        if (line[i] == '2') {
            bit_offset -= 12;
            counts[0]++;
            continue;
        }

        uint64_t index = 0;
        for (size_t j = 0; j < 12; j++) {
            if (line[i] == cards[j]) {
                counts[j+1]++;
                break;
            }
            index++;
        }

        card = card | ((uint64_t)1 << (bit_offset+index));
        bit_offset -= 12;
    }

    uint64_t checkvalue = 0, rank;
    for (size_t i = 0; i < 13; i++) {
        if (counts[i] != 0) {
            checkvalue += (counts[i]*counts[i]);
        }
    }

    switch (checkvalue) {
        case 5:
            rank = 1;
            break;
        case 7:
            rank = 2;
            break;
        case 9:
            rank = 3;
            break;
        case 11:
            rank = 4;
            break;
        case 13:
            rank = 5;
            break;
        case 17:
            rank = 6;
            break;
        case 25:
            rank = 7;
            break;
    }

    card = card | (rank << 60);
    return card;
}

uint64_t parse_hand_p2(char *line)
{
    uint64_t card = 0, bit_offset = 48;
    char cards[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};
    uint64_t counts[13] = {0};
    uint64_t jacks = 0;

    for (size_t i = 0; i < 5; i++) {
        if (line[i] == 'J') {
            jacks++;
            bit_offset -= 12;
            continue;
        }

        uint64_t index = 0;
        for (size_t j = 0; j < 12; j++) {
            if (line[i] == cards[j]) {
                counts[j+1]++;
                break;
            }
            index++;
        }

        card = card | ((uint64_t)1 << (bit_offset+index));
        bit_offset -= 12;
    }

    // increment the maximum card count by the number of jokers
    uint64_t max_count_idx = 0, max_count = 0;
    for (size_t i = 0; i < 13; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_count_idx = i;
        }
    }
    counts[max_count_idx] += jacks;

    uint64_t checkvalue = 0, rank;
    for (size_t i = 0; i < 13; i++) {
        if (counts[i] != 0) {
            checkvalue += (counts[i]*counts[i]);
        }
    }

    switch (checkvalue) {
        case 5:
            rank = 1;
            break;
        case 7:
            rank = 2;
            break;
        case 9:
            rank = 3;
            break;
        case 11:
            rank = 4;
            break;
        case 13:
            rank = 5;
            break;
        case 17:
            rank = 6;
            break;
        case 25:
            rank = 7;
            break;
    }

    card = card | (rank << 60);
    return card;
}

uint64_t parse_bid(char *line)
{
    uint64_t number = 0;

    for (size_t i = 6; (i < strlen(line)) && (isdigit(line[i])); i++) {
        number *= 10;
        number += (line[i] - '0');
    }

    return number;
}

void dual_sort(uint64_t *hands, uint64_t *bids, uint64_t total_elements)
{
    for (size_t i = 0; i < total_elements-1; i++) {
        // Last i elements are already in place, so no need to check them
        for (size_t j = 0; j < total_elements-i-1; j++) {
            if (hands[j] > hands[j+1]) {
                uint64_t temp = hands[j];
                hands[j] = hands[j+1];
                hands[j+1] = temp;

                temp = bids[j];
                bids[j] = bids[j+1];
                bids[j+1] = temp;
            }
        }
    }
}
