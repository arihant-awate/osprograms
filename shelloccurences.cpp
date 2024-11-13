#!/bin/bash

# Hardcoded string and substring
string="hello world, hello everyone, hello universe"
substring="hello"

# Method 1: Using 'grep' to count occurrences
count1=$(echo "$string" | grep -o "$substring" | wc -l)

# Method 2: Using Bash parameter expansion to count occurrences
count2=0
temp_string="$string"
while [[ "$temp_string" == *"$substring"* ]]; do
    count2=$((count2 + 1))
    temp_string="${temp_string#*$substring}"  # Remove the first occurrence of substring
done

# Output the results
echo "Method 1: The substring '$substring' occurred $count1 times (using 'grep')."
echo "Method 2: The substring '$substring' occurred $count2 times (using bash expansion)."

# FAQ:
# Q1: What does the script do?
# A1: This script counts how many times the substring `hello` appears in the string `hello world, hello everyone, hello universe`.
#     It uses two different methods: `grep` and bash parameter expansion.
#
# Q2: Can I change the string or substring?
# A2: Yes, you can modify the values of `string` and `substring` to check for different strings and substrings.
#
# Q3: What is the `grep` method doing?
# A3: The `grep -o` command finds all occurrences of the substring in the string. The `-o` option makes `grep` output 
#     each match on a new line, and `wc -l` counts how many lines were printed, which is equal to the number of matches.
#
# Q4: How does the bash parameter expansion method work?
# A4: In this method, the script repeatedly removes the first occurrence of the substring from the string, and each time it removes 
#     an occurrence, it increments the counter. The loop continues until no more occurrences are found.
