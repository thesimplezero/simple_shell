#include "main.h"
#include "processes.h"
/**
 * handle_command_separator - Handle separation of commands
 * @progname: Program name
 * @line: The line of commands
 *
 * Return: Always 0
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
