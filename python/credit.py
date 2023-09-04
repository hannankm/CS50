from cs50 import get_int
import re

number = get_int("Number: ")
# check if 15 digits
amex = re.search("^34|^37", str(number))
# check if 16 digits
mastercard = re.search("^51|^52|^53|^54|^55", str(number))
# check if 13 or 16 digits
visa = re.search("^4", str(number))

sum = 0
if amex or mastercard or visa:
    for i in range(len(str(number))):
        if len(str(number)) % 2 == 0:
            if i % 2 == 0:
                if int(str(number)[i]) * 2 > 9:
                    sum += int(str(int(str(number)[i]) * 2)[0]) + int(str(int(str(number)[i]) * 2)[1])
                else:
                    sum += int(str(number)[i]) * 2
                sum += int(str(number)[i + 1])
        else:
            if i % 2 != 0:
                if int(str(number)[i]) * 2 > 9:
                    sum += int(str(int(str(number)[i]) * 2)[0]) + int(str(int(str(number)[i]) * 2)[1])
                else:
                    sum += int(str(number)[i]) * 2

            else:
                sum += int(str(number)[i])
if amex and len(str(number)) == 15 and sum % 10 == 0:
    print("AMEX")
elif mastercard and len(str(number)) == 16 and sum % 10 == 0:
    print("MASTERCARD")
elif visa and (len(str(number)) == 13 or len(str(number)) == 16) and sum % 10 == 0:
    print("VISA")
else:
    print("INVALID")
