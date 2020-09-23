import re

def main():
    # Check input. Only digits are permitted
    while True:
        pan = input("Number: ")
        if pan.isdecimal():
            break
    # Check the beginning of PAN, lenght and checksum
    if bool(re.search(r"^[3][47]", pan)) and len(pan) == 15 and check_luhn(pan):
        print('AMEX')
    elif bool(re.search(r"^[5][12345]", pan)) and len(pan) == 16 and check_luhn(pan):
        print('MASTERCARD')
    elif bool(re.search(r"^[4]", pan)) and len(pan) in [13, 16] and check_luhn(pan):
        print('VISA')
    else:
        print('INVALID')

def check_luhn(pan):
    # Make reverse string of the PAN
    reversed_pan = ''.join(reversed(pan))

    # counting sum
    sum = 0
    # select every second digit of the reverse PAN from the second position
    for i in reversed_pan[1::2]:
        # If the product of number is 10, 11, ..., then we need to split them for separate counting 1 and 0
        if (int(i) * 2) > 9:
            tmp_i = str(int(i) * 2)
            # make substring from the product of numbers
            for j in tmp_i:
                sum += int(j)
        else:
            sum += int(i) * 2

    # select every second digit of the reverse PAN from the first position
    for i in reversed_pan[::2]:
        sum += int(i)

    # true if the last digit of SUM is 0
    if sum % 10 == 0:
        return True
    else:
        return False

main()
