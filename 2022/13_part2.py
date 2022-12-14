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

def decoder_key(input_str: str) -> int:
    lists = [eval(row) for row in input_str.splitlines() if row != ""]
    lists.append([[2]])
    lists.append([[6]])

    for n in range(len(lists)-1, -1, -1):
        for i in range(n):
            if check_order(lists[i], lists[i+1]) == 1:
                lists[i], lists[i+1] = lists[i+1], lists[i]
    
    return (lists.index([[2]]) + 1) * (lists.index([[6]]) + 1)

if __name__ == "__main__":
    with open("input13.txt", "r") as file:
        puzzle_input = file.read()
    print(decoder_key(puzzle_input))