def resting_sand(input_str: str) -> int:

    coordinates = set()

    for line in input_str.splitlines():
        positions = line.split(" -> ")
        prev_col, prev_row = positions[0].split(",")
        prev_col, prev_row = int(prev_col), int(prev_row)

        for pos in positions[1:]:
            col, row = pos.split(",")
            col, row = int(col), int(row)

            if (col, row) == (prev_col, prev_row):
                coordinates.add((col, row))
            elif col != prev_col:
                for n in range(min(col, prev_col), max(col, prev_col)+1):
                    coordinates.add((n, row))
            elif row != prev_row:
                for n in range(min(row, prev_row), max(row, prev_row)+1):
                    coordinates.add((col, n))
            
            prev_col, prev_row = col, row
    
    max_row = max(coordinates, key=lambda x: x[1])[1]

    pos = (500, 0)
    total = 0
    top_reached = False
    while not top_reached:
        col, row = pos
        if (col, row+1) not in coordinates and row+1 != max_row+2:
            pos = (col, row+1)
        elif (col-1, row+1) not in coordinates and row+1 != max_row+2:
            pos = (col-1, row+1)
        elif (col+1, row+1) not in coordinates and row+1 != max_row+2:
            pos = (col+1, row+1)
        else:
            total += 1
            coordinates.add(pos)
            if pos == (500, 0):
                top_reached = True
            pos = (500, 0)
    
    return total

if __name__ == "__main__":
    with open("input14.txt", "r") as file:
        puzzle_input = file.read()
    print(resting_sand(puzzle_input))