#include "shell.h"

/**
 * is_interactive - checks if shell is in interactive mode
 * @data: ptr to struct of shell data
 * Return: returns 1 if interactive mode else 0 otherwise
 */

int is_interactive(data_t *data)
{
	return ((isatty(STDIN_FILENO) && data->readfd <= 2) ? 1 : 0);
}

/**
 * is_delimiter - this func checks if char is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: returns 1 if true else 0 if false
 */

int is_delimiter(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * is_alphabet - checks for alphabet character
 * @c: inputted character
 * Return: returns 1 if c is alphabet else 0
 */

int is_alphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
* is_chain_delim - the func checks if the chain is valid
* @data: the parameter struct
* @buf: the char buffer
* @p: address of current position in buffer
* Return: returns 1 if chain delimeter else 0 if not chain delimeter
*/

int is_chain_delim(data_t *data, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		data->cmd_buf_type = CMD_STRING;
	}
	else
		return (0);
	*p = j;
	return (1);
}
/**
* is_valid_chain - the func checks if the chain is valid
* @data: the parameter struct
* @buff: the buffer
* @p: pointer to current position in the buffer
* @i: starting position
* @len: length of buff
* Return: returns NULL
*/

void is_valid_chain(data_t *data, char *buff, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	*p = j;
}
