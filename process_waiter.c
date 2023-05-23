#include "processes.h"
#include "main.h"
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * wait_for_process - Waits for a child process to change state.
 * @pid: Process ID of the child process.
 *
 * Return: If the process terminated normally, returns the exit status.
 *         If the process terminated due to a signal, it writes an
 *         appropriate message and returns -1. If an error occurred,
 *         returns -1.
 */
int wait_for_process(pid_t pid)
{
	int status;

	if (waitpid(pid, &status, 0) < 0)
	{
		perror("Error waiting for process");
		return (-1);
	}

	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	else
	{
		char *message;

		if (WIFSIGNALED(status))
		{
			message = "Child terminated by signal\n";
		}
		else if (WIFSTOPPED(status))
		{
			message = "Child stopped by signal\n";
		}
		else
		{
			return (-1);
		}

		write(2, message, strlen(message));
	}

	return (-1);
}

/**
 * handle_signal - Handles received signals.
 * @sig: Signal number.
 *
 * Writes a message indicating the signal that was received.
 */
void handle_signal(int sig)
{
	char buf[32];
	/* Custom sprintf function */
	custom_sprintf(buf, "Received signal: %d\n", sig);
	write(1, buf, strlen(buf));
}

/**
 * terminate_process - Terminates a process.
 * @pid: Process ID of the process to terminate.
 *
 * Return: 0 on success, -1 on failure.
 */
int terminate_process(pid_t pid)
{
	if (kill(pid, SIGTERM) == -1)
	{
		perror("Error terminating process");
		return (-1);
	}

	return (0);
}
