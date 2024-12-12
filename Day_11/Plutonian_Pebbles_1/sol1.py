import sys
import os
sys.setrecursionlimit(1000000)

# Get the directory of the script
script_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the path to the file
file_path = os.path.join(script_dir, "../puzzle_input.txt")

with open(file_path) as f:
    s = f.read().strip()

s = [int(n) for n in s.split()]

def blink(stones) :

    new_stones = []

    for stone in stones:
        if stone == 0:
            new_stones.append(1)
        elif len(str(stone)) % 2 == 0: # number of digits is even
            stone = str(stone)
            half = len(stone) // 2
            new_stones.append(int(stone[:half])) # first half
            new_stones.append(int(stone[half:])) # second half
        else:
            new_stones.append(stone * 2024)

    return new_stones

for _ in range(25):
    s = blink(s)

print(len(s))