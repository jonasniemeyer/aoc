def count_visible_trees(input_str: str) -> int:
    array = []
    for row in input_str.splitlines():
        array.append(list(row))
    
    height, width = len(array), len(array[0])
    visible_trees = height*2 + width*2 - 4

    for n in range(1, height-1):
        for m in range(1, width-1):
            tree_height = array[n][m]

            if (
                not any(other_height>=tree_height for other_height in array[n][:m])
                or not any(other_height>=tree_height for other_height in array[n][m+1:])
                or not any(other_height>=tree_height for other_height in (array[y][m] for y in range(n)))
                or not any(other_height>=tree_height for other_height in (array[y][m] for y in range(n+1, height)))
            ):
                visible_trees += 1
    
    return visible_trees

if __name__ == "__main__":
    with open("input8.txt", "r") as file:
        puzzle_input = file.read()
    
    print(count_visible_trees(puzzle_input))