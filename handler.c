#include "shell.h"

/**
 * input_buffer - the func buffers linked commands
 * @data: parameter struct
 * @buff: buffer address
 * @len: address of lenght variable
 * Return: returns bytes read
 */
ssize_t input_buffer(data_t *data, char **buff, size_t *len)
{

	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigint_handle);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = cus_getline(data, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			data->linecount_flag = 1;
			rem_comments(*buff);
			build_log(data, *buff, data->logcount++);
			{
				*len = r;
				data->cmd_buf = buff;
			}
		}
	}
	return (r);
}

/**
 * get_input - the func gets a line except newline
 * @data: parameter struct
 * Return: returns bytes read
 */
ssize_t get_input(data_t *data)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buff_p = &(data->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buffer(data, &buff, &len);
	if (r == -1)
	{
		return (-1);
	}
	if (len)
	{
		j = i;
		p = buff + i;

		is_valid_chain(data, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain_delim(data, buff, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->cmd_buf_type = CMD_REG;
		}

		*buff_p = p;
		return (_strlen(p));
	}
	*buff_p = buff;
	return (r);
}

/**
 * sigint_handle - the func blocks ctrl-C
 * @sig_num: the signal number
 * Return: returns void
 */
void sigint_handle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
