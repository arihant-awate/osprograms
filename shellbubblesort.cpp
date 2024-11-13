#!/bin/bash

# Hardcoded array of numbers to be sorted
arr=(64 34 25 12 22 11 90)

# Function to perform Bubble Sort
bubbleSort() {
  local n=${#arr[@]}  # Get the length of the array
  # Outer loop for each pass
  for ((i = 0; i < n-1; i++))
  do
    # Inner loop for comparing adjacent elements
    for ((j = 0; j < n-i-1; j++))
    do
      # If the element is greater than the next element, swap them
      if [ ${arr[j]} -gt ${arr[$((j+1))]} ]; then
        # Swap the elements
        temp=${arr[j]}
        arr[$j]=${arr[$((j+1))]}
        arr[$((j+1))]=$temp
      fi
    done
  done
}

# Print the original array
echo "Original Array: ${arr[@]}"

# Call the bubbleSort function
bubbleSort

# Print the sorted array
echo "Sorted Array: ${arr[@]}"

# FAQ:
# Q1: What is Bubble Sort?
# A1: Bubble Sort is a simple comparison-based sorting algorithm where adjacent elements are compared and swapped if necessary. 
#     The process is repeated until the array is sorted.
#
# Q2: How does Bubble Sort work?
# A2: It repeatedly compares adjacent elements and swaps them if they are in the wrong order. After each pass through the list, 
#     the largest unsorted element "bubbles up" to its correct position.
#
# Q3: Is Bubble Sort efficient?
# A3: Bubble Sort has a time complexity of O(n^2) in the worst case, which makes it inefficient for large datasets.
#
# Q4: Can I change the array to sort other numbers?
# A4: Yes, you can modify the array in the script (the `arr` variable) to sort different numbers.
#
# Q5: What happens if the array is already sorted?
# A5: If the array is already sorted, Bubble Sort still goes through all the iterations, making it inefficient compared to more optimized algorithms.
