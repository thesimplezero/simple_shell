#include "main.h"

/**
 * custom_getline - Reads a line from a stream.
 *
 * @lineptr: Pointer to a buffer that will hold the read line.
 * @n: Pointer to the size of the buffer.
 * @stream: The input stream to read from.
 *
 * Return: The number of characters read on success, -1 on failure.
 */
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	char ch;
	size_t i = 0;
	const size_t initial_size = 100;

	if (*lineptr == NULL || *n == 0)
	{
		*n = initial_size;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}

	while ((ch = fgetc(stream)) != EOF && ch != '\n')
	{
		if (i == *n - 1)
		{
			*n *= 2;
			*lineptr = (char *)realloc(*lineptr, *n);
			if (*lineptr == NULL)
			{
				free(*lineptr);
				return (-1);
			}
		}
		(*lineptr)[i++] = ch;
	}
	(*lineptr)[i] = '\0';
	return (i);
}

