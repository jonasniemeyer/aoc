def check_order(left: list, right: list) -> bool:
    left_len, right_len = len(left), len(right)

    for i in range(min(left_len, right_len)):
        if isinstance(left[i], int) and isinstance(right[i], int):
            comparison = left[i] - right[i]
        elif isinstance(left[i], list) and isinstance(right[i], list):
            comparison = check_order(left[i], right[i])
        elif isinstance(left[i], int) and isinstance(right[i], list):
            comparison = check_order([left[i]], right[i])
        elif isinstance(left[i], list) and isinstance(right[i], int):
            comparison = check_order(left[i], [right[i]])
        
        if comparison < 0:
            return -1
        elif comparison > 0:
            return 1
    
    if left_len > right_len:
        return 1
    elif left_len < right_len:
        return -1
    
    return 0

def sum_of_indices(input_str: str) -> int:
    pairs = [[eval(x) for x in part.splitlines()] for part in input_str.split("\n\n")]

    total = 0
    for index, pair in enumerate(pairs, 1):
        left, right = pair
        if check_order(left, right) == -1:
            total += index
    return total


if __name__ == "__main__":
    with open("input13.txt", "r") as file:
        puzzle_input = file.read()
    print(sum_of_indices(puzzle_input))