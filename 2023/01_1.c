#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

uint64_t part1(FILE *file);
uint64_t part2(FILE *file);

#define MAX_LINE    1000

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    printf("%llu\n", part1(file));
    rewind(file);
    printf("%llu\n", part2(file));
}

uint64_t part1(FILE *file)
{
    char line[MAX_LINE];
    uint64_t sum = 0;
    uint8_t first;
    uint8_t last = 0;

    while (fgets(line, MAX_LINE, file)) {
        first = 1;
        for (size_t index = 0; index < strlen(line); index++) {
            if (isdigit(line[index])) {
                if (first) {
                    sum += (line[index]-'0') * 10;
                    last = (line[index]-'0');
                    first = 0;
                } else {
                    last = (line[index]-'0');
                }
            }
        }
        sum += last;
    }
    
    return sum;
}

uint64_t part2(FILE *file)
{
    char line[MAX_LINE];
    uint64_t sum = 0;
    uint8_t first;
    uint8_t last = 0;

    char *numbers[] = {
        "placeholder",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };

    while (fgets(line, MAX_LINE, file)) {
        first = 1;
        for (size_t index = 0; index < strlen(line); index++) {
            if (isdigit(line[index])) {
                if (first) {
                    sum += (line[index]-'0') * 10;
                    last = (line[index]-'0');
                    first = 0;
                } else {
                    last = (line[index]-'0');
                }
            } else {
                for (size_t i = 1; i < 10; i++) {
                    if (strncmp(&line[index], numbers[i], strlen(numbers[i])) == 0) {
                        if (first) {
                            sum += i * 10;
                            last = i;
                            first = 0;
                        } else {
                            last = i;
                        }
                    }
                }
            }
        }
        sum += last;
    }
    
    return sum;
}