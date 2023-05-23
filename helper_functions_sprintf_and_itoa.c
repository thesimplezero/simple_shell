#include "main.h"
#include "processes.h"
#include <string.h>

/**
* custom_itoa - Custom integer to string converter.
* @num: The integer to convert.
* @str: The string buffer to hold the result.
*
* Return: Nothing.
*/
void
custom_itoa(int num, char *str)
{
int i = 0;
int isNegative = 0;
int start, end;

if (num == 0)
{
str[i++] = '0';
str[i] = '\0';
return;
}

if (num < 0)
{
isNegative = 1;
num = -num;
}

while (num != 0)
{
int digit = num % 10;

str[i++] = digit + '0';
num = num / 10;
}

if (isNegative)
str[i++] = '-';

str[i] = '\0';

start = 0;
end = i - 1;

while (start < end)
{
char temp = str[start];

str[start] = str[end];
str[end] = temp;
start++;
end--;
}
}

/**
* custom_sprintf - Custom sprintf implementation.
* @str: Destination string.
* @format: Format string.
* @number: Integer number to be formatted into the string.
*
* Return: Nothing.
*/
void
custom_sprintf(char *str, const char *format, int number)
{
int i = 0, j = 0;
int numLen;

while (format[i] != '\0')
{
if (format[i] == '%' && format[i + 1] == 'd')
{
char numStr[12];
custom_itoa(number, numStr);
numLen = strlen(numStr);
custom_strncpy(&str[j], numStr, numLen + 1);
j += numLen;
i += 2;
}
else
{
str[j++] = format[i++];
}
}

str[j] = '\0';
}
