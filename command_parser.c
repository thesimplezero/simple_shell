#include "main.h"
#include <string.h>
#include <ctype.h>

/**
* trim_string - Trims leading and trailing spaces of a string.
* @str: The string to trim.
*
* Return: Pointer to the trimmed string.
*/
char *trim_string(char *str)
{
char *end;

while (isspace((unsigned char)*str))
{
str++;
}

if (*str == 0)  /* All spaces? */
return (str);

end = str + strlen(str) - 1;
while (end > str && isspace((unsigned char)*end))
{
end--;
}

*(end + 1) = 0;

return (str);
}

/**
* command_parser - Parses a string into tokens using a delimiter.
* @line: The string to parse.
* @delimiter: The delimiter used to tokenize the string.
*
* Return: A double pointer to an array of tokens on success,
*         NULL on failure or if @line or @delimiter is NULL.
*/
char **command_parser(char *line, const char *delimiter)
{
char **tokens = NULL;
char *token = NULL;
size_t i = 0, num_tokens = 0;

if (line == NULL || delimiter == NULL)
return (NULL);
line[strcspn(line, "\n")] = '\0';
line[strcspn(line, "#")] = '\0';
line = trim_string(line);

num_tokens = 4;
tokens = malloc(sizeof(char *) * num_tokens);

/* If memory allocation fails, handle error */
if (tokens == NULL)
handle_memory_error();

token = custom_strtok(line, delimiter);
while (token != NULL)
{
if (i == num_tokens)
{
num_tokens *= 2;
tokens = realloc(tokens, sizeof(char *) * num_tokens);

/* If memory allocation fails, handle error */
if (tokens == NULL)
handle_memory_error();
}
tokens[i] = strdup(token);

/* If memory allocation fails, handle error */
if (tokens[i] == NULL)
handle_memory_error();
i++;
token = custom_strtok(NULL, delimiter);
}

tokens[i] = NULL;
return (tokens);
}
/**
* handle_memory_error - Handles memory allocation errors.
*
* Return: void.
*/
void handle_memory_error(void)
{
perror("Error: memory allocation failed");
exit(EXIT_FAILURE);
}
