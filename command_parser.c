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
size_t i = 0;

if (line == NULL || delimiter == NULL)
{
return (NULL);
}

tokens = malloc(sizeof(char *));
if (tokens == NULL)
{
return (NULL);
}

line[strcspn(line, "\n")] = '\0';
line[strcspn(line, "#")] = '\0';
line = trim_string(line);

token = custom_strtok(line, delimiter);
while (token != NULL)
{
tokens = realloc(tokens, (i + 2) * sizeof(char *));
if (tokens == NULL)
{
return (NULL);
}

tokens[i] = trim_string(token);
i++;

token = custom_strtok(NULL, delimiter);
}

tokens[i] = NULL;
return (tokens);
}
