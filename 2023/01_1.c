#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

uint64_t part1(FILE *file);

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    printf("%llu", part1(file));
}

uint64_t part1(FILE *file)
{
    char line[1000];
    uint64_t sum = 0;
    uint8_t first;
    uint8_t last = 0;

    while (fgets(line, 1000, file)) {
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