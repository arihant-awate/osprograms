#!/bin/bash

# Hardcoded number
num=12345

# Initialize the reverse number to 0
reverse=0

# Loop to reverse the digits
while [ $num -gt 0 ]
do
  # Extract the last digit
  digit=$(( num % 10 ))

  # Append the digit to the reverse number
  reverse=$(( reverse * 10 + digit ))

  # Remove the last digit from the original number
  num=$(( num / 10 ))
done

# Output the result
echo "The reversed number is: $reverse"

# FAQ:
# Q1: What does this script do?
# A1: This script reverses the digits of the hardcoded number `12345`. It extracts each digit and adds it to the reversed number.
#
# Q2: Can I change the number?
# A2: Yes, you can modify the value of `num` to any integer you want to reverse the digits of that number.
#
# Q3: How does the script reverse the digits?
# A3: The script extracts the last digit of the number using modulo (`% 10`) and appends it to the reversed number by multiplying the reversed number by 10 and adding the extracted digit.
#
# Q4: What happens if the number is zero?
# A4: If the number is `0`, the reversed number will also be `0`.
#
# Q5: Can this script handle negative numbers?
# A5: This script does not handle negative numbers. You can add a check to handle negative numbers if required.
