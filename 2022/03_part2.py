def sum_of_priorities(input_str: str) -> int:
    sum_ = 0
    rows = input_str.splitlines()
    for index, _ in enumerate(rows):
        if index % 3 != 0:
            continue
        letter, = set(rows[index]) & set(rows[index+1]) & set(rows[index+2])
        if letter.islower():
            sum_ += 1 + (ord(letter) - ord("a"))
        else:
            sum_ += 27 + (ord(letter) - ord("A"))
    return sum_

if __name__ == "__main__":
    with open("input3.txt", "r") as file:
        puzzle_input = file.read()
    print(sum_of_priorities(puzzle_input))