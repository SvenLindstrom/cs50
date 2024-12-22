from cs50 import get_int
# TODO


while (True):
    n = get_int("Height: ")
    if n > 0 and n < 9:
        break

for i in range(n):

    print(" " * (n-1-i), end="")
    print("#" * (i+1), end="")
    print(" " * 2, end="")
    print("#" * (i+1))

