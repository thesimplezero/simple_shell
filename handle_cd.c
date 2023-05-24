#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * handle_cd - Handles the 'cd' command to change the current directory.
 * @args: The command arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int
handle_cd(char **args)
{
	char *target_dir = NULL;
	char *home_dir = getenv("HOME");
	char *old_dir = getcwd(NULL, 0);
	char *current_dir;

	/* Determine the target directory */
	if (args[1] == NULL || strcmp(args[1], "-") == 0)
	{
		target_dir = home_dir;
	} else
	{
		target_dir = args[1];
	}

	/* Change to the target directory */
	if (chdir(target_dir) == -1)
	{
		perror("Error changing directory");
		free(old_dir);
		return (-1);
	}

	/* Get the current directory */
	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		perror("Error getting current directory");
		free(old_dir);
		return (-1);
	}

	/* Update the PWD environment variable */
	if (setenv("PWD", current_dir, 1) == -1)
	{
		perror("Error setting PWD");
		free(old_dir);
		free(current_dir);
		return (-1);
	}

	/* Print the old directory if cd - was used */
	if (strcmp(args[1], "-") == 0)
	{
		write(STDOUT_FILENO, old_dir, strlen(old_dir));
		write(STDOUT_FILENO, "\n", 1);
	}

	/* Cleanup */
	free(old_dir);
	free(current_dir);

	return (0);
}
