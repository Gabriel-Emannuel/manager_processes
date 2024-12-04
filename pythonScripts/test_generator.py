import random
import os
import sys

LINES = random.randint(1,100)
LETTERS = random.randint(1,100)
DIRECTORIES = random.randint(1,4)
FILES = random.randint(1,10)

letters = list("abcdefghijklmnopqrstuvwyz")

def creating_word(until_now: int) -> tuple[str, int]:
    word_size = random.randint(until_now, LETTERS) - (until_now - 1)
    word = str()
    for _ in range(word_size):
        word += random.choice(letters)
    
    return word, word_size + until_now + 1

def creating_line() -> str:
    words = []
    letters = 0

    while letters < LETTERS:
        word, letter = creating_word(letters)
        words.append(word)
        letters += letter
    
    return ' '.join(words)

def creating_file() -> str:
    lines = [creating_line() for _ in range(LINES)]

    return "\n".join(lines)

DEEP = int(sys.argv[2])
PATH = sys.argv[1]

directory_time = 0

def creating_test(height: int, path: str) -> None:
    
    if height >= DEEP:
        return None
    
    directories = [f"{i}" for i in range(DIRECTORIES)]

    files = [f"{path}/{i}.txt" for i in range(FILES)]

    for file in files:
        with open(file, "x") as file:
            file.write(creating_file())
    
    for directory in directories:
        path_time = f"{path}/{directory}"
        os.makedirs(path_time)
        creating_test(height + 1, path_time)

    return None

creating_test(0, PATH)