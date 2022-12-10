def sum_signal_strengths(input_str: str) -> int:
    total, cycle = 0, 0
    value = 1
    for row in input_str.splitlines():
        if row == "noop":
            instructions_left = 1
            order = 0
        if row.startswith("addx"):
            instructions_left = 2
            order = int(row.split()[-1])
        
        while instructions_left != 0:
            instructions_left -= 1
            cycle += 1
            if cycle in (20, 60, 100, 140, 180, 220):
                total += value * cycle
        
        value += order

    return total

if __name__ == "__main__":
    with open("input10.txt", "r") as file:
        puzzle_input = file.read()
    
    print(sum_signal_strengths(puzzle_input))