def highest_scenic_score(input_str: str) -> int:
    array = []
    for row in input_str.splitlines():
        array.append(list(row))
    
    height, width = len(array), len(array[0])
    max_score = 0

    for n in range(1, height-1):
        for m in range(1, width-1):
            tree_height = array[n][m]

            for index, other_height in enumerate(reversed(array[n][:m])):
                if other_height >= tree_height:
                    break
            left = index+1

            for index, other_height in enumerate(array[n][m+1:]):
                if other_height >= tree_height:
                    break
            right = index+1

            for index, other_height in enumerate((array[y][m] for y in range(n-1, -1, -1))):
                if other_height >= tree_height:
                    break
            top = index+1

            for index, other_height in enumerate(array[y][m] for y in range(n+1, height)):
                if other_height >= tree_height:
                    break
            down = index+1
            
            score = left * right * top * down
            if score > max_score:
                max_score = score
    
    return max_score

if __name__ == "__main__":
    with open("input8.txt", "r") as file:
        puzzle_input = file.read()
    
    print(highest_scenic_score(puzzle_input))