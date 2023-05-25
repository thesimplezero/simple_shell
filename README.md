
# Simple Shell

This is a simple UNIX command interpreter written in C language. The program provides a command line user interface for UNIX-like operating systems.

## Features

- Implements most of the basic functions of a command-line interpreter.
- Reads commands from standard input and executes them.
- Provides built-in functions like `cd` and `exit`.
- Handles command separators (`;`).
- Handles logical operators (`&&`, `||`).
- Custom getline implementation.
- Resolves commands to their paths before execution.
- Basic signal handling.
- Uses a custom strtok function.
- Handles command execution in child processes.

## Getting Started

### Prerequisites

You need to have a UNIX-like operating system with a gcc compiler installed to compile and run this program.

### Compilation

Compile the program by using gcc:
`bash
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
`

### Running

After compilation, you can run the program with:
` bash

./hsh

`


You should see a prompt where you can type commands



## Files

`main.h` - This is the main header file containing all the function prototypes of the shell.

`processes.h` - This is the header file containing the prototypes of functions dealing with process creation and management.

`*.c` - These are the source files containing all the functions used by the shell.

## Functions

The shell implements various functions, including:

- `print_prompt()`: Displays the shell prompt.
- `custom_getline()`: Reads an entire line from the stream.
- `sigint_handler()`: Handles SIGINT signals.
- `command_parser()`: Parses a string into tokens using a delimiter.
- `get_path()`, `set_path()`, `add_to_path()`: Handle the `PATH` environment variable.
- `custom_strtok()`, `custom_strdup()`, `custom_sprintf()`, `custom_strncpy()`: Custom string manipulation functions.
- `builtin_env()`, `handle_exit()`, `handle_cd()`: Handle built-in commands.
- `handle_command_separator()`, `handle_logical_operators()`: Handle command separators and logical operators.

In `processes.h`:

- `create_process()`: Creates a new process.
- `execute_command()`: Executes a command.
- `resolve_path()`: Resolves a command to its absolute path.
- `wait_for_process()`: Waits for a process to change its state.
- `handle_signal()`: Handles signals.
- `terminate_process()`: Terminates a process.

## Authors


