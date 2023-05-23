#include "main.h"
#include <stdlib.h>
/**
 * handle_exit - Handles the "exit" command in the shell.
 * @args: The array of command arguments.
 *
 * Return: -1 if an error occurs or the shell should exit,
 *        otherwise the function does not return.
 */
int handle_exit(char **args)
{
	int status = 0;

	/* If an exit status is provided, convert it to an integer */
	if (args[1] != NULL)
	{
		char *endptr;

		status = (int)strtol(args[1], &endptr, 10);

/* Check for conversion error */
		if (*endptr != '\0')
		{
			write(STDERR_FILENO, "Error: Invalid argument to exit: ", 33);
			write(STDERR_FILENO, args[1], strlen(args[1]));
			write(STDERR_FILENO, "\n", 1);
			return (-1);
		}
	}

	/* Exit the program with the given status */
	exit(status);

/* We won't actually get here */
/*but return (-1) just in case something goes wrong with exit */
	return (-1);
}
