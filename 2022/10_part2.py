def draw_crt(input_str: str) -> str:
    crt = ""
    cycle = 0
    sprite = 0

    for row in input_str.splitlines()[:]:
        if row == "noop":
            instructions_left = 1
            order = 0
        if row.startswith("addx"):
            instructions_left = 2
            order = int(row.split()[-1])
        
        while instructions_left != 0:
            instructions_left -= 1
            
            if cycle in range(sprite, sprite+3):
                crt += "|"
            else:
                crt += " "
            
            cycle += 1
            if cycle % 40 == 0:
                cycle -= 40
                crt += "\n"
        
        sprite += order
    
    return crt

if __name__ == "__main__":
    with open("input10.txt", "r") as file:
        puzzle_input = file.read()
    
    print(draw_crt(puzzle_input))