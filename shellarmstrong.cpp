#!/bin/bash

# Hardcoded number
num=153

# Initialize variables
sum=0
temp_num=$num
num_digits=${#num}  # Get the number of digits in the number

# Loop to calculate the sum of each digit raised to the power of the number of digits
while [ $temp_num -gt 0 ]
do
  # Extract the last digit
  digit=$(( temp_num % 10 ))

  # Add the digit raised to the power of the number of digits
  sum=$(( sum + digit ** num_digits ))

  # Remove the last digit from the number
  temp_num=$(( temp_num / 10 ))
done

# Check if the sum is equal to the original number
if [ $sum -eq $num ]; then
    echo "$num is an Armstrong number."
else
    echo "$num is not an Armstrong number."
fi

# FAQ:
# Q1: What is an Armstrong number?
# A1: An **Armstrong number** is a number that is equal to the sum of its own digits, each raised to the power of the number of digits.
#
# Q2: Can I change the number?
# A2: Yes, you can modify the value of the `num` variable to check other numbers.
#
# Q3: How does the script check for an Armstrong number?
# A3: The script calculates the sum of each digit raised to the power of the number of digits and compares it with the original number.
#
# Q4: What happens if the number is single-digit?
# A4: A single-digit number is always an Armstrong number because the sum of its digits raised to the power of 1 is the number itself.
#
# Q5: Can this script handle large numbers?
# A5: Yes, the script works for any integer, but for very large numbers, you might run into performance issues or integer overflow with very large exponents.
