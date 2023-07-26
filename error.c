#include "shell.h"

/**
 * print_error - the func prints an error message
 * @data: data struct
 * @str_err: string containing a specified error type
 * Return: returns no value
 */
void print_error(data_t *data, char *str_err)
{
	err_puts(data->fname);
	err_puts(": ");
	prints_deci(data->line_count, STDERR_FILENO);
	err_puts(": ");
	err_puts(data->argv[0]);
	err_puts(": ");
	err_puts(str_err);
}

/**
 * err_str - the func converts a string to an int
 * @str: the string to be converted
 * Return: returns int if no numbers in string else -1 on error
 */
int err_str(char *str)
{
	int i = 0;
	long int result = 0;

	bool is_positive = true;

	if (*str == '-')
	{
		is_positive = false;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			if (result > INT_MAX || result < INT_MIN)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
	return (is_positive ? (int)result : -(int)result);
}


/**
 * prints_deci - the func prints a decimal number
 * @input: the input
 * @fd: file descriptor
 * Return: returns number of characters printed
 */
int prints_deci(int input, int fd)
{
	int (*print_char)(char) = _putchar;
	int i, count = 0;
	unsigned int _absolute_, current;

	if (fd == STDERR_FILENO)
	{
		print_char = err_putchar;
	}
	if (input < 0)
	{
		_absolute_ = -input;
		print_char('-');
		count++;
	}
	else
	{
		_absolute_ = input;
	}
	current = _absolute_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_absolute_ / i)
		{
			print_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	print_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_num - the func converts numbers
 * @num: number
 * @b: base
 * @f: argument flags
 * Return: returns string
 */
char *convert_num(long int num, int b, int f)
{
	static char *array;
	static char buff[SMALL_BUF_SIZE];
	char sign = 0, *ptr;
	unsigned long n = num;

	if (!(f & CONV_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = f & CONV_LOWERCASE ? "0123456789abcdef" :
	"0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % b];
		n /= b;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_comments - the function replaces first instance of '#' with '\0'
 * @buff: address of the str to modify
 * Return: returns 0;
 */
void rem_comments(char *buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
	{
		if (buff[i] == '#')
		{
			buff[i] = '\0';
			break;
		}
	}
}
