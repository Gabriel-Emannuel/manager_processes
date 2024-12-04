import sys

file_path = sys.argv[1]

words = 0
lines = 0

with open(file_path, "r") as file:
    for line in file.readlines():
        lines += 1
        words += len(line.split())

with open(file_path, "w") as file:
    file.write(f"Lines Ammount: {lines}, Words Ammount: {words}")