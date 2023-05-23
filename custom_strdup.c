#include "processes.h"
#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
* custom_strdup - Duplicates a string.
*
* @s: The string to duplicate.
*
* Return: A pointer to the newly allocated duplicated string,
*         or NULL if memory allocation fails.
*/
char *custom_strdup(const char *s)
{
size_t len = strlen(s) + 1; /* +1 for the null-terminator */
char *new = malloc(len);

if (new == NULL)
{
return (NULL);
}
/* memcpy is generally faster than a manual loop */
return ((char *)memcpy(new, s, len));
}
