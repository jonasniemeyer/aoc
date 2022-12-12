def fewest_steps(input_str: str) -> int:
    heightmap = [list(row) for row in input_str.splitlines()]

    start = [(row, col) for row in range(len(heightmap)) for col in range(len(heightmap[0])) if heightmap[row][col] == "E"][0]
    heightmap[start[0]][start[1]] = "z"

    seen_positions = set()
    paths = [(0, start[0], start[1])]
    path_lengths = []

    while paths:
        steps, curr_row, curr_col = paths[0]
        paths.pop(0)

        if (curr_row, curr_col) in seen_positions:
            continue
        seen_positions.add((curr_row, curr_col))
        
        for row, col in ((curr_row-1, curr_col), (curr_row, curr_col+1), (curr_row+1, curr_col), (curr_row, curr_col-1)):
            if row < 0 or row == len(heightmap) or col < 0 or col == len(heightmap[0]):
                continue
            if ord(heightmap[row][col]) - ord(heightmap[curr_row][curr_col]) < -1:
                continue
            if (row, col) in seen_positions:
                continue

            if heightmap[row][col] == "a":
                path_lengths.append(steps+1)
                break
            paths.append((steps+1, row, col))
    
    return sorted(path_lengths)[0]

if __name__ == "__main__":
    with open("input12.txt", "r") as file:
        puzzle_input = file.read()
    print(fewest_steps(puzzle_input))