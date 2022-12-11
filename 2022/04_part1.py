def count_nested_pairs(input_str: str) -> list:
    total = 0
    for line in input_str.splitlines():
        ab, cd = line.split(",")
        a, b = ab.split("-")
        c, d = cd.split("-")
        a, b, c, d = int(a), int(b), int(c), int(d)
        if (c <= a <= b <= d) or (a <= c <= d <= b):
            total += 1
    return total

if __name__ == "__main__":
    with open("input04.txt", "r") as file:
        puzzle_input = file.read()
    print(count_nested_pairs(puzzle_input))