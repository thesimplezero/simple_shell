#include "main.h"
#include "processes.h"
#include <sys/wait.h>

/**
* process_command - Processes a single command.
* @command: The command to process.
* @program_name: name of the program
*
* Return: nothing
*/
void process_command(char *command, char *program_name)
{
char **tokens = command_parser(command, " \t");

if (tokens != NULL && tokens[0] != NULL)
{
if (strcmp(tokens[0], "env") == 0)
builtin_env();
else if (strcmp(tokens[0], "exit") == 0)
handle_exit(tokens);
else if (strcmp(tokens[0], "cd") == 0)
handle_cd(tokens);
else
{
pid_t pid = create_process();
if (pid == 0)
{
if (execute_command(tokens[0], tokens, program_name) == -1)
{
write(STDERR_FILENO, program_name, strlen(program_name));
write(STDERR_FILENO, ": 1: ", 5);
write(STDERR_FILENO, tokens[0], strlen(tokens[0]));
write(STDERR_FILENO, ": not found\n", 12);
exit(EXIT_FAILURE);
}
}
else if (pid > 0)
{
if (wait_for_process(pid) == -1)
perror("Failed to wait for process");
}
}
}

free_tokens(tokens);
}

/**
* process_line - Process each line of input
* @line: the input line
* @is_interactive: flag to check if input is interactive
* @program_name: name of the program
*
* Return: nothing
*/
void process_line(char *line, int is_interactive, char *program_name)
{
char **commands = NULL;
int i;

(void)is_interactive;

/* Parse commands separated by ';' */
commands = command_parser(line, ";");

if (commands == NULL)
return;

/* Loop over each command */
for (i = 0; commands[i] != NULL; i++)
process_command(commands[i], program_name);

/* Free commands array */
free_tokens(commands);
}


/**
* main - main function for the shell
* @argc: argument count
* @argv: argument vector
*
* Return: 0 on success, or other number on failure
*/
int main(int argc, char **argv)
{
char *line = NULL;
size_t len = 0;
int is_interactive;

(void)argc;

/* Attach sigint_handler to SIGINT signal */
signal(SIGINT, sigint_handler);

is_interactive = isatty(STDIN_FILENO);

while (1)
{
if (is_interactive)
print_prompt();

if (custom_getline(&line, &len, stdin) == -1)
{
perror("Error reading input");
free(line);
exit(EXIT_FAILURE);
}

if (feof(stdin))
{
free(line);
if (is_interactive)
write(STDOUT_FILENO, "\n", 1);
exit(EXIT_SUCCESS);
}

process_line(line, is_interactive, argv[0]);
}

free(line);
return (0);
}
