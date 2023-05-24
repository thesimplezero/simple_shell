#include "main.h"

/**
* print_prompt - Prints a shell prompt.
*/
void print_prompt(void)
{
ssize_t write_res;

write_res = write(STDOUT_FILENO, "$ ", 2);
if (write_res == -1)
{
write(STDERR_FILENO, "Error writing prompt to stdout\n", 32);
exit(EXIT_FAILURE);
}
else if (write_res < 2)
{
write(STDERR_FILENO, "Incomplete write of prompt to stdout\n", 37);
exit(EXIT_FAILURE);
}

if (fflush(stdout) != 0)
{
write(STDERR_FILENO, "Error flushing stdout\n", 22);
exit(EXIT_FAILURE);
}
}
