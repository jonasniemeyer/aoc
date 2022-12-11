import math

def monkey_business(input_str: str) -> int:
    ROUNDS = 10_000

    items = {}
    operations = {}
    targets = {}
    inspections = {}
    factor = 1

    parts = input_str.split("\n\n")
    for part in parts:
        lines = part.splitlines()
        monkey = int(lines[0].split()[1].replace(":", ""))
        starting_items = [int(item) for item in lines[1].split(": ")[1].split(", ")]
        if "old * old" in lines[2]:
            operation = lambda x=0: (x * x)
        elif "old * " in lines[2]:
            order = int(lines[2].split("old * ")[1])
            operation = lambda x=0, order=order: (x * order)
        elif "old + " in lines[2]:
            order = int(lines[2].split("old + ")[1])
            operation = lambda x=0, order=order: (x + order)
        
        floor_divisor = int(lines[3].split()[-1])
        factor *= floor_divisor
        target_true = int(lines[4].split()[-1])
        target_false = int(lines[5].split()[-1])
        target_monkey = lambda x, a=target_true, b=target_false, c=floor_divisor: a if (x % c == 0) else b

        items[monkey] = starting_items
        operations[monkey] = operation
        targets[monkey] = target_monkey
        inspections[monkey] = 0
    
    for _ in range(ROUNDS):
        for monkey in items.keys():
            for _ in range(len(items[monkey])):
                inspections[monkey] += 1
                new_item = operations[monkey](items[monkey].pop(0)) % factor
                items[targets[monkey](new_item)].append(new_item)
    
    sorted_inspections = sorted(inspections.values())
    return sorted_inspections[-1] * sorted_inspections[-2]

if __name__ == "__main__":
    with open("input11.txt", "r") as file:
        puzzle_input = file.read()
    print(monkey_business(puzzle_input))