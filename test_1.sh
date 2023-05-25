#!/bin/bash

# Test script for our shell

# Test case for process_line function
echo "Testing process_line function..."

# Send the 'env' command and check if the output matches the 'env' command in bash
echo "env" | ./hsh > test_output
env > correct_output
if diff -q test_output correct_output > /dev/null; then
  echo "Passed test: env command"
else
  echo "Failed test: env command"
fi

# Send the 'cd' command and check the current directory
echo "cd .." | ./hsh > test_output
echo "PWD: $(pwd)" > correct_output
if diff -q test_output correct_output > /dev/null; then
  echo "Passed test: cd command"
else
  echo "Failed test: cd command"
fi

# Check if unknown commands give a 'not found' error
echo "unknown_command" | ./hsh 2> test_output
echo "hsh: 1: unknown_command: not found" > correct_output
if diff -q test_output correct_output > /dev/null; then
  echo "Passed test: unknown command"
else
  echo "Failed test: unknown command"
fi

# Test case for main function
echo "Testing main function..."

# Check if pressing Ctrl+C prints a new prompt
printf "\x03" | ./hsh > test_output
echo -e "\n$(pwd) $ " > correct_output
if diff -q test_output correct_output > /dev/null; then
  echo "Passed test: SIGINT signal (Ctrl+C)"
else
  echo "Failed test: SIGINT signal (Ctrl+C)"
fi

# Clean up test files
rm test_output correct_output

echo "All tests finished"
