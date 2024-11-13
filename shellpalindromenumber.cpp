#!/bin/bash

# Hardcoded number
num=121

# Reverse the number
original_num=$num
reverse_num=0

while [ $num -gt 0 ]
do
    remainder=$(( num % 10 ))  # Get the last digit
    reverse_num=$(( reverse_num * 10 + remainder ))  # Append the digit to reverse_num
    num=$(( num / 10 ))  # Remove the last digit from num
done

# Check if the original number is equal to the reversed number
if [ $original_num -eq $reverse_num ]; then
    echo "$original_num is a palindrome number."
else
    echo "$original_num is not a palindrome number."
fi

# FAQ:
# Q1: What does this script do?
# A1: This script checks if a hardcoded number is a palindrome by reversing the digits and comparing it with the original number.
#
# Q2: Can I change the number?
# A2: Yes, you can modify the `num` variable to any positive integer to check if it's a palindrome.
#
# Q3: What happens if the number is negative?
# A3: The script only checks positive integers. You can add additional checks to handle negative numbers if needed.
#
# Q4: How does the reversal process work?
# A4: The script extracts the last digit of the number using modulo (`% 10`), then constructs the reversed number by multiplying the existing reversed number by 10 and adding the extracted digit.
#
# Q5: Will this script work for multi-digit numbers?
# A5: Yes, the script works for any positive integer, regardless of the number of digits.
