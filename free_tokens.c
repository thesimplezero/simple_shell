#include "main.h"
/**
* free_tokens - Frees an array of strings.
* @tokens: The array of strings.
*
* Return: void
*/
void free_tokens(char **tokens)
{
int i;

/* If tokens is NULL, just return */
if (tokens == NULL)
return;

/* Loop over each string and free it */
for (i = 0; tokens[i] != NULL; i++)
free(tokens[i]);

/* Free the array itself */
free(tokens);
}
