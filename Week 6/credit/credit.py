# TODO
from cs50 import get_int

number = get_int("Number: ")
number = str(number)

# See the lenght of the number
if len(number) in [16, 13, 15]:

    # List of all digits in the number
    digits = [int(digit) for digit in number]

    # Calculate the digits that will be doble and doble them
    doubled_digits = [digit * 2 for digit in digits[-2::-2]]
    doubled_digits = [digit - 9 if digit >= 10 else digit for digit in doubled_digits]

    # Store the other digits
    other_digits = digits[::-2]

    # Sum the digits
    add = sum(doubled_digits + other_digits)

    # Check if the sum is base of 10
    if add % 10 == 0:

        # Check the beggining of the number
        beginning = int(number[:2])
        if beginning in [34, 37]:
            print("AMEX")
        elif beginning in [51, 52, 53, 54, 55]:
            print("MASTERCARD")
        elif int(number[0]) == 4:
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")
