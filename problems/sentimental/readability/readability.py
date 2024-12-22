# TODO
from cs50 import get_string


text = get_string("Text: ")

text = text.lower()

letters = 0
words = 0
sentences = 0

for i in range(len(text)):
    c = text[i]
    if c == " ":
        words += 1
    elif c == "." or c == "!" or c == "?":
        sentences += 1
    elif c.isalpha():
        letters += 1

words += 1

averiage_letters = (letters / words) * 100
averiage_sentences = (sentences / words) * 100


grade = 0.0588 * averiage_letters - 0.296 * averiage_sentences - 15.8

# print(averiage_letters)
# print(averiage_sentences)
# print(letters)
# print(words)
# print(sentences)
# print(grade)
# print(text)


grade = round(grade)


if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade: {grade}")

