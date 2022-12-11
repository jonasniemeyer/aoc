import re

def top_crates(input_str: str) -> str:
    stack_section, moves = input_str.split("\n\n")

    # build stacks
    stack_section_split = stack_section.splitlines()
    total_stacks = len(stack_section_split[-1].split())
    stacks = [[] for _ in range(total_stacks)]
    for level in stack_section_split[:-1]:
        for stack, char in enumerate(level[1::4]):
            if not char.isspace():
                stacks[stack].append(char)

    # move crates
    for line in moves.splitlines():
        amount, from_, to = re.findall("move ([0-9]+) from ([0-9]+) to ([0-9]+)", line)[0]
        amount, from_, to = int(amount), int(from_)-1, int(to)-1
        for _ in range(amount):
            stacks[to].insert(0, stacks[from_].pop(0))
    
    return "".join(stack[0] for stack in stacks if len(stack) > 0)

if __name__ == "__main__":
    with open("input05.txt", "r") as file:
        puzzle_input = file.read()
    print(top_crates(puzzle_input))