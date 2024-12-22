# TODO
from cs50 import get_string

card_number = get_string("Number: ")

length = len(card_number)


if length < 13 or length > 16:
    print("INVALID")
    exit()

if card_number[0] == "4":
    card_name = "VISA"

elif length == 15 and card_number[0] == "3" and (card_number[1] == "4" or card_number[1] == "7"):
    card_name = "AMEX"

elif length == 16 and card_number[0] == "5" and (int(card_number[1]) > 0 and int(card_number[1]) < 6):
    card_name = "MASTERCARD"

else:
    print("INVALID")
    exit()

switch = 0
odd_sum = 0
even_sum = 0

for i in range(length-1, -1, -1):
    if switch == 0:
        odd_sum += int(card_number[i])
        switch = 1
    else:
        even_sum += (int(card_number[i]) * 2) % 10 + (int(card_number[i])*2) // 10
        switch = 0


if (odd_sum + even_sum) % 10 == 0:
    print(card_name)
    exit()

print("INVALID")
exit()