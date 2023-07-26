#include "shell.h"

/**
 * set_data - this func initializes data_t struct
 * @data: struct address
 * @av: argument vector
 * Return: returns the set data
 */
void set_data(data_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = str_tok(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		rep_alias(data);
		rep_vars(data);
	}
}

/**
 * clear_data - this func initializes data_t struct
 * @data: struct address
 * Return: returns NULL
 */
void clear_data(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * free_data - this function frees data_t struct fields
 * @data: struct address
 * @a: all data to be freed
 * Return: returns NULL
 */
void free_data(data_t *data, int a)
{
	free_str(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (a)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->log)
			free_list(&(data->log));
		if (data->alias)
			free_list(&(data->alias));
		free_str(data->environ);
			data->environ = NULL;
		free_ptr((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUF_FLUSH);
	}
}
