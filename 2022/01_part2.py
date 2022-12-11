def find_three_most_calories(input_str: str) -> list:
    calories = [sum(int(line) for line in elf.splitlines()) for elf in input_str.split("\n\n")]
    return sorted(calories, reverse=True)[:3]

if __name__ == "__main__":
    with open("input01.txt", "r") as file:
        puzzle_input = file.read()
    total_calories = sum(find_three_most_calories(puzzle_input))
    print(total_calories)