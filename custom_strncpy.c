#include "main.h"
#include "processes.h"

/**
* custom_strncpy - Copies up to a specified number of
* characters from the source string to the destination string.
*
* @destination: Pointer to the destination string.
* @source: Pointer to the source string.
* @num: Maximum number of characters to be copied.
*
* Return: Pointer to the destination string.
*         NULL if a null pointer is passed to custom_strncpy.
*/
char *custom_strncpy(char *destination, const char *source, size_t num)
{
char *ptr = destination;

if (source == NULL || destination == NULL)
{
/* Error: Null pointer passed to custom_strncpy */
return (NULL);
}

/* Copy up to 'num' characters from the source to the destination. */
while (num > 0 && *source != '\0')
{
*ptr++ = *source++;
num--;
}

/*
* If num > 0, then we didn't reach the end of the source string.
*
* In this case, fill the remaining space with null characters.
*
*/
while (num > 0)
{
*ptr++ = '\0';
num--;
}

return (destination);
}
