#include "processes.h"
#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * create_process - creates a new process using fork
 *
 * Return: pid of the new process, or -1 on failure
 */
pid_t create_process(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error creating process");
		exit(EXIT_FAILURE);
	}

	return (pid);
}

/**
 * execute_command - Executes a command.
 * @command: The command to execute.
 * @args: The arguments to pass to the command.
 * @program_name: The name of the program calling this function.
 *
 * Return: 0 on success, -1 on failure.
 */
int execute_command(char *command, char **args, char *program_name)
{
    char *resolved_path;

    resolved_path = resolve_path(command);
    if (resolved_path == NULL)
    {
        write(STDERR_FILENO, program_name, strlen(program_name));
        write(STDERR_FILENO, ": 1: ", 5);
        write(STDERR_FILENO, command, strlen(command));
        write(STDERR_FILENO, ": not found\n", 12);
        return (-1);
    }

    if (execve(resolved_path, args, NULL) == -1)
    {
        perror("Error executing command");
        free(resolved_path);
        return (-1);
    }

    free(resolved_path);
    return (0);
}

/**
 * resolve_path - Resolves a command to an executable in the PATH.
 * @command: The command to resolve.
 *
 * Return: Resolved path to executable on success, NULL on failure.
 */
char *resolve_path(char *command)
{
    char *PATH;
    char *p;
    char *resolved_path;
    char *possible_path;

    if (strchr(command, '/') != NULL)
    {
        if (access(command, X_OK) == 0)
            return (custom_strdup(command));
        return (NULL);
    }

    PATH = getenv("PATH");
    p = custom_strtok(PATH, ":");
    resolved_path = NULL;

    while (p != NULL)
    {
        possible_path = malloc(strlen(p) + strlen(command) + 2);
        sprintf(possible_path, "%s/%s", p, command);
        if (access(possible_path, X_OK) == 0)
        {
            resolved_path = possible_path;
            break;
        }

        free(possible_path);
        p = custom_strtok(NULL, ":");
    }

    return (resolved_path);
}
