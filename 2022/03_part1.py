def sum_of_priorities(input_str: str) -> int:
    sum_ = 0
    for row in input_str.splitlines():
        middle = len(row)//2
        first, second = row[:middle], row[middle:]
        letter, = set(first) & set(second)
        if letter.islower():
            sum_ += 1 + (ord(letter) - ord("a"))
        else:
            sum_ += 27 + (ord(letter) - ord("A"))
    return sum_

if __name__ == "__main__":
    with open("input3.txt", "r") as file:
        puzzle_input = file.read()
    print(sum_of_priorities(puzzle_input))