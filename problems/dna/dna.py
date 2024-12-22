import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print("Usage: python dna.py DATA_FILE SEQUANCE_FILE")
        sys.exit()

    # TODO: Read database file into a variable
    suspects = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            suspects.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequance = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    key_list = list(suspects[0])
    key_list.remove("name")

    longest = {}

    for key in key_list:
        longest[key] = longest_match(sequance, key)

# TODO: Check database for matching profiles
    for suspect in suspects:
        match = is_match(suspect, longest)
        if match != None:
            print(match)
            sys.exit()
    print("No match")
    return


def is_match(suspect, longest):
    for key in longest:
        if int(suspect[key]) != int(longest[key]):
            return None

    return suspect["name"]


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
