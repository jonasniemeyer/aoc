def find_most_calories(input_str: str) -> int:
    return max(
        sum(int(line) for line in elf.splitlines()) for elf in input_str.split("\n\n")
    )

if __name__ == "__main__":
    with open("input1.txt", "r") as file:
        puzzle_input = file.read()
    print(find_most_calories(puzzle_input))