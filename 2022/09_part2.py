def count_visited_positions(input_str: str, rope_length) -> int:
    rope = [[0,0] for _ in range(rope_length)]
    visited_positions = [[0,0]]
    
    for row in input_str.splitlines():
        direction, order = row.split()
        order = int(order)

        for _ in range(order):
            if direction == "L":
                rope[-1][0] -= 1
            elif direction == "R":
                rope[-1][0] += 1
            elif direction == "U":
                rope[-1][1] += 1
            elif direction == "D":
                rope[-1][1] -= 1
            
            for index in range(len(rope)-2, -1, -1):
                diff = [rope[index+1][0] - rope[index][0], rope[index+1][1] - rope[index][1]]
                if diff == [2, 2]:
                    rope[index][0] += 1
                    rope[index][1] += 1
                elif diff == [2, 1]:
                    rope[index][0] += 1
                    rope[index][1] += 1
                elif diff == [2, 0]:
                    rope[index][0] += 1
                elif diff == [2, -1]:
                    rope[index][0] += 1
                    rope[index][1] -= 1
                elif diff == [2, -2]:
                    rope[index][0] += 1
                    rope[index][1] -= 1
                elif diff == [1, 2]:
                    rope[index][0] += 1
                    rope[index][1] += 1
                elif diff == [1, -2]:
                    rope[index][0] += 1
                    rope[index][1] -= 1
                elif diff == [0, 2]:
                    rope[index][1] += 1
                elif diff == [0, -2]:
                    rope[index][1] -= 1
                elif diff == [-1, 2]:
                    rope[index][0] -= 1
                    rope[index][1] += 1
                elif diff == [-1, -2]:
                    rope[index][0] -= 1
                    rope[index][1] -= 1
                elif diff == [-2, 2]:
                    rope[index][0] -= 1
                    rope[index][1] += 1
                elif diff == [-2, 1]:
                    rope[index][0] -= 1
                    rope[index][1] += 1
                elif diff == [-2, 0]:
                    rope[index][0] -= 1
                elif diff == [-2, -1]:
                    rope[index][0] -= 1
                    rope[index][1] -= 1
                elif diff == [-2, -2]:
                    rope[index][0] -= 1
                    rope[index][1] -= 1
            
            if rope[0] not in visited_positions:
                visited_positions.append([rope[0][0], rope[0][1]])
    
    return len(visited_positions)

if __name__ == "__main__":
    with open("input9.txt", "r") as file:
        puzzle_input = file.read()
    
    print(count_visited_positions(puzzle_input, rope_length=10))