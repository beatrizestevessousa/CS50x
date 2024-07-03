# TODO
from cs50 import get_int

# Get user input
while True:
    height = get_int("Height: ")
    if 0 < height < 9:
        break


for i in range(height):
    # Calculate how many spaces and hashes
    space = height-1 - i
    hashes = i + 1

    # Printing the pyramid
    print(' ' * space + '#' * hashes + '  ' + '#' * hashes)
