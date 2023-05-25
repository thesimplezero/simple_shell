#include "main.h"
#include "processes.h"
/**
 * handle_command_separator - Handles command separator
 *                            logic in input line.
 * @progname: The program name or identifier.
 * @line: The input line to be processed.
 *
 * Return: 0 on successful execution.
 *
 * Description:
 * This function takes a program name and a line of input
 * and handles command separator logic.It parses the input line
 * into commands using a custom_strtok function, then further parses
 * each command into tokens using the command_parser function.
 * It checks if the command is abuilt-in command (cd or exit)
 * and handles it accordingly. If not a built-in command, it creates
 * a new process to execute the command using create_process
 * function and waits for the process to complete using
 * wait_for_process function. The function iterates through
 * all commands in the input line and frees
 * allocated memory before returning 0.
 */
int handle_command_separator(char *progname, char *line)
{
	char *command;
	char **tokens;
	pid_t pid;
	/* Parse the line into commands */
	command = custom_strtok(line, ";");

	while (command != NULL)
{
		/* Parse the command into tokens */
		tokens = command_parser(command, " ");

		if (tokens != NULL && tokens[0] != NULL)
{
			/* Check if the command is a built-in command */
			if (strcmp(tokens[0], "cd") == 0)
{
				handle_cd(tokens);
			} else if (strcmp(tokens[0], "exit") == 0)
{
				handle_exit(tokens);
			}
else
{
				/* Create a new process to execute the command */
				pid = create_process();
				if (pid == 0)
{
					/* Child process: execute the command */
					execute_command(tokens[0], tokens, progname);
				} else if (pid > 0)
{
					wait_for_process(pid);
				}
			}
			free(tokens);
		}
		/* Get the next command */
		command = custom_strtok(NULL, ";");
	}
	return (0);
}
