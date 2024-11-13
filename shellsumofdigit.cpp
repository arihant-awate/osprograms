#!/bin/bash

# Hardcoded number
num=12345

# Initialize sum to 0
sum=0

# Loop to extract each digit and add it to the sum
while [ $num -gt 0 ]
do
  digit=$(( num % 10 ))   # Get the last digit of the number
  sum=$(( sum + digit ))  # Add the digit to the sum
  num=$(( num / 10 ))     # Remove the last digit
done

# Output the result
echo "The sum of the digits is: $sum"

# FAQ:
# Q1: What does this script do?
# A1: This script calculates the sum of digits of the hardcoded number `12345`. It extracts each digit and adds it to a sum variable.
#
# Q2: Can I change the number?
# A2: Yes, you can modify the value of `num` to any integer you want to calculate the sum of its digits.
#
# Q3: How does the script calculate the sum of digits?
# A3: The script extracts each digit of the number by using modulo (`% 10`) and integer division (`/ 10`). It then adds the extracted digit to the sum.
#
# Q4: What happens if the number is zero?
# A4: If the number is `0`, the sum will also be `0`, as there are no digits to add.
#
# Q5: Can this script handle negative numbers?
# A5: This script does not handle negative numbers directly. To handle negative numbers, you can add a check to take the absolute value of the number.
