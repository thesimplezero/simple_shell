#include "main.h"
#include <signal.h>
#include <unistd.h>

/**
 * sigint_handler - Signal handler for SIGINT (Ctrl+C).
 *
 * @sig: The signal number.
 */
void sigint_handler(int sig)
{
	(void)sig;

	/* Check if STDOUT is connected to a terminal */
	if (isatty(STDOUT_FILENO))
	{
		/* Print a newline character and the prompt */
		write(STDOUT_FILENO, "\n", 1);
		print_prompt();
		/* Flush the output buffer to immediately show the prompt */
		fflush(stdout);
	}
}
