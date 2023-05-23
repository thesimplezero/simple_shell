#include "main.h"
#include <stdlib.h>
/**
 * @brief Handles the program's exit based on the provided 
 *  arguments.
 * This function takes a double pointer to a character array as its parameter.
 * It is responsible for processing the exit status argument and terminating
 * the program accordingly. If a valid exit status argument is provided, the
 * program exits with that status. If an invalid argument is encountered or no
 * argument is provided, an error message is displayed, and the function returns
 * -1 to indicate an error condition.
 *
 * @param args A double pointer to a character array representing 
 *      the command-line arguments.
 * The exit status argument is expected to be present at args[1].
 * 
 * @return Returns -1 if an error occurs, otherwise the program 
 *                 is terminated with the provided exit status.
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
