#!/bin/bash

# Hardcoded number for which we want to calculate the factorial
num=5

# Initialize the variable factorial to 1 (the base value for multiplication)
factorial=1

# Loop through the numbers from 1 to the hardcoded number
for (( i=1; i<=num; i++ ))
do
  # Multiply factorial by the current loop number
  factorial=$(( factorial * i ))
done

# Output the result of the factorial calculation
echo "The factorial of $num (non-recursive) is $factorial"

# FAQ:
# Q1: What does this script do?
# A1: This script calculates the factorial of the number 5 using an iterative (non-recursive) method with a for loop.
#
# Q2: How does the iterative factorial calculation work?
# A2: The loop multiplies the `factorial` variable by each integer from 1 to the given number. The result is the factorial.
#
# Q3: Can I change the number?
# A3: Yes, you can change the value of the `num` variable to any positive integer to calculate its factorial.
#
# Q4: What will happen if I set num to 0 or 1?
# A4: The script will still work, as the factorial of 0 and 1 is always 1.



// NEW SECTION //


#!/bin/bash

# Hardcoded number for which we want to calculate the factorial
num=5

# Recursive function to calculate the factorial
factorial() {
  # Base case: if the input is 1 or 0, return 1
  if [ $1 -le 1 ]; then
    echo 1
  else
    # Recursive case: n * factorial(n-1)
    prev=$(factorial $(( $1 - 1 )))  # Recursively call the factorial function with (n-1)
    echo $(( $1 * prev ))  # Multiply the current number with the result of the recursive call
  fi
}

# Calling the recursive function to calculate the factorial
result=$(factorial $num)

# Output the result of the factorial calculation
echo "The factorial of $num (recursive) is $result"

# FAQ:
# Q1: What does this script do?
# A1: This script calculates the factorial of the number 5 using a recursive method.
#
# Q2: How does recursion work in this script?
# A2: The function calls itself repeatedly, each time with a smaller number, until it reaches the base case where n <= 1.
#     Then it starts returning the results, multiplying each number with the previous result.
#
# Q3: Can I change the number?
# A3: Yes, you can change the value of the `num` variable to any positive integer to calculate its factorial.
#
# Q4: What will happen if I set num to 0 or 1?
# A4: The base case of the recursive function handles both `num = 0` and `num = 1`, returning a factorial value of 1.
#
# Q5: Is recursion more efficient than iteration in this case?
# A5: Recursion may consume more memory due to the call stack, and in some cases, iteration (non-recursive) can be more efficient.
