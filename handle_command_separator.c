#include "main.h"
#include "processes.h"

/**
 * @brief: Executes multiple commands separated by the ';' character
 *
 * @param progname: The name of the program (usually argv[0])
 * @param line: A string containing one or more commands separated by ';'
 * @return If successful, returns 0. If an error occurs, returns -1.
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
			}
			else if (strcmp(tokens[0], "exit") == 0)
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
					execute_command(progname, tokens);
				}
				else if (pid > 0)
				{
/* Parent process: wait for the child process to complete */
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
