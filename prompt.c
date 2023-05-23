#include "main.h"

/**
 * print_prompt - Prints the shell prompt.
 */
void print_prompt(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return;
	}

	write(STDOUT_FILENO, cwd, strlen(cwd));
	write(STDOUT_FILENO, " $ ", 3);
	fflush(stdout);
}
