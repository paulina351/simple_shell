#include "shell.h"

/**
 * err_putchar - writes the character c to stderr
 * @c: The character to print
 * Return: returns 1 else -1 if there is error
 */
int err_putchar(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * err_puts - the func prints an input string
 * @str: string
 * Return: returns NULL
 */
void err_puts(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}
	while (str[i] != '\0')
	{
		err_putchar(str[i]);
		i++;
	}
}

/**
 * _putfd - the func writes the character to the file des
 * @c: The character to print
 * @fd: filedescriptor
 * Return: returns 1 else -1 if there is error
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putstr - the func prints an input string
 * @str: string
 * @fd: filedescriptor
 * Return: returns the number of chars put
 */
int _putstr(char *str, int fd)
{
	int i = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
