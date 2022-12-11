def total_score(input_str: str) -> int:
    score = 0

    for row in input_str.splitlines():
        a, b = row.split()

        score += scores[b]
        if a == equal[b]:
            score += 3
        elif a == beats[b]:
            score += 6
    
    return score

beats = {"X": "C", "Y": "A","Z": "B"}
equal = {"X": "A", "Y": "B" ,"Z": "C"}
scores = {"X": 1, "Y": 2, "Z": 3}

if __name__ == "__main__":
    with open("input02.txt", "r") as file:
        puzzle_input = file.read()
    print(total_score(puzzle_input))