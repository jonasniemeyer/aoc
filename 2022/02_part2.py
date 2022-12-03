def total_score(input_str: str) -> int:
    score = 0

    for row in input_str.splitlines():
        a, b = row.split()

        if b == "X":
            score += scores[beats[a]]
        elif b == "Y":
            score += scores[a]
            score += 3
        else:
            score += scores[loses[a]]
            score += 6
    
    return score

beats = {"A": "C", "B": "A", "C": "B"}
loses = {"A": "B", "B": "C", "C": "A"}
scores = {"A": 1, "B": 2, "C": 3}

if __name__ == "__main__":
    with open("input2.txt", "r") as file:
        puzzle_input = file.read()
    print(total_score(puzzle_input))