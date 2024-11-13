#!/bin/bash

# Hardcoded string
str="madam"

# Reverse the string
reverse_str=$(echo $str | rev)

# Check if the original string is equal to the reversed string
if [ "$str" == "$reverse_str" ]; then
    echo "\"$str\" is a palindrome string."
else
    echo "\"$str\" is not a palindrome string."
fi

# FAQ:
# Q1: What does this script do?
# A1: This script checks if a hardcoded string is a palindrome by reversing the string and comparing it with the original string.
#
# Q2: Can I change the string?
# A2: Yes, you can modify the `str` variable to any string to check if it's a palindrome.
#
# Q3: Does the script handle spaces and punctuation?
# A3: No, this script only checks the exact string. If you want to ignore spaces or punctuation, you would need to preprocess the string (e.g., removing spaces and non-alphabetic characters).
#
# Q4: How does the reversal process work?
# A4: The script uses the `rev` command to reverse the string. This command reads the string and outputs it in reverse order.
#
# Q5: Does the script handle case sensitivity?
# A5: Yes, the script is case-sensitive. To make it case-insensitive, you can convert both strings to lowercase using `tr` or `awk` before comparison.
