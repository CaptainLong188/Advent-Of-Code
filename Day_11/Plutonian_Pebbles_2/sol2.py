import sys
import os
sys.setrecursionlimit(1000000)

# Get the directory of the script
script_dir = os.path.dirname(os.path.abspath(__file__))

# Construct the path to the file
file_path = os.path.join(script_dir, "../puzzle_input.txt")

with open(file_path) as f:
    s = f.read().strip()

ans = 0
s = [int(n) for n in s.split()]

memo = {}
def count_blinks(stone, rep) :

    if rep == 0: return 1
    if (stone, rep) not in memo:
        if stone == 0:
            result = count_blinks(1, rep - 1)
        elif len(str(stone)) % 2 == 0:
            x = str(stone)
            result = count_blinks(int(x[:len(x)//2]), rep - 1)
            result += count_blinks(int(x[len(x)//2:]), rep - 1)
        else:
            result = count_blinks(stone * 2024, rep - 1)
        
        memo[(stone, rep)] = result

    return memo[((stone, rep))]

for stone in s:
    ans += count_blinks(stone, 75)

print(ans)
print(memo)