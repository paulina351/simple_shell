#include "shell.h"

/**
* _puts - the func prints an input string
* @str: the string to be printed
* Return: returns NULL
*/
void _puts(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
* _putchar - the func writes the character to stdout
* @c: The character to print
* Return: returns 1 on success else -1
*/
int _putchar(char c)
{
	static int i;
	static char buff[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(STDOUT_FILENO, buff, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buff[i++] = c;
	return (1);
}
