def detect_start_position(input_str: str, size: int) -> int:
    marker = [0]*size
    
    for index, letter in enumerate(input_str):
        marker.pop(0)
        marker.append(letter)
        # fill first values
        if index < (size-1):
            continue

        if len(marker) == len(set(marker)):
            return index+1
    
    return -1

if __name__ == "__main__":
    with open("input6.txt", "r") as file:
        puzzle_input = file.read()
    print(detect_start_position(puzzle_input, 14))