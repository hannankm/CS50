from cs50 import get_string

text = get_string("Text: ")
letters = sentences = 0
words = 1
for char in text:
    if char.isalpha():
        letters += 1
    elif char.isspace():
        words += 1
    elif char == "." or char == "?" or char == "!":
        sentences += 1
    else:
        continue
L = (letters / words) * 100
S = (sentences / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

if index > 0 and index < 16:
    print("Grade ", index)
elif index >= 16:
	print("Grade 16+")
else:
	print("Before Grade 1")

