import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print(sys.argv)
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    persons = []

    file = sys.argv[1]
    with open(file) as data:
        reader = csv.DictReader(data)
        strs = reader.fieldnames[1:]
        for line in reader:
            persons.append(line)

    # TODO: Read DNA sequence file into a variable
    str_count = dict.fromkeys(strs, 0)

    filename = sys.argv[2]
    with open(filename) as f:
        sequence = f.read()

    # TODO: Find longest match of each STR in DNA sequence
    for STR in strs:
        str_count[STR] = longest_match(sequence, STR)

    # TODO: Check database for matching profiles
    for person in persons:
        match = 0

        for STR in strs:
            if (int(person[STR]) == str_count[STR]):
                match += 1

        if match == len(strs):
            print(person['name'])
            exit(0)
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
