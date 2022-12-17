import re

def count_positions(input_str: str) -> int:
    Y = 2_000_000
    beacons = set()
    impossible_positions = set()

    for line in input_str.splitlines():
        sensor_x, sensor_y, beacon_x, beacon_y = re.findall("Sensor at x=(-?\d+), y=(-?\d+): closest beacon is at x=(-?\d+), y=(-?\d+)", line)[0]
        sensor = (int(sensor_x), int(sensor_y))
        beacon = (int(beacon_x), int(beacon_y))
        beacons.add(beacon)
        
        distance = abs(beacon[0]-sensor[0]) + abs(beacon[1]-sensor[1])

        for x in range(sensor[0]-(distance-abs(Y-sensor[1])), sensor[0]+(distance-abs(Y-sensor[1]))+1):
            impossible_positions.add((x, Y))
    
    return len(impossible_positions-beacons)

if __name__ == "__main__":
    with open("input15.txt", "r") as file:
        puzzle_input = file.read()
    print(count_positions(puzzle_input))