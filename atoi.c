#include "shell.h"

/**
 * _atoi - the func converts a string to an int
 * @str: the string to convert
 * Return: returns 0 if no numbers in string
 */

int _atoi(char *str)
{
	int i = 0, sign = 1;
	unsigned int result = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
		}
		else
		{
			break;
		}
		i++;
	}

	return (sign * result);
}

