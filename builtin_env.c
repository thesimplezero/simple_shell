#include "main.h"
#include <unistd.h>

/**
 * builtin_env - Handles the env builtin
 *
 * Return: 0 on success, -1 on failure
 */
int
builtin_env(void)
{
	char **env = environ;

	/* Iterate over each environment variable and print it */
	while (*env)
{
		if (write(STDOUT_FILENO, *env, strlen(*env)) == -1)
{
			perror("Error writing environment variable");
			return (-1);
		}

		/* Print a newline after each variable */
		if (write(STDOUT_FILENO, "\n", 1) == -1)
{
			perror("Error writing newline");
			return (-1);
		}

		env++;
	}

	return (0);
}
