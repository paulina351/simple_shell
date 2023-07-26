#include "shell.h"

/**
 * _setenv - This function initialize a new env variable or modify it
 * @data: parameter struct
 * @var: environment variable
 * @value: environment variable's value
 *  Return: returns 0 on success
 */
int _setenv(data_t *data, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
	{
		return (1);
	}
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = data->env;
	while (node)
	{
		p = _search(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_at_end(&(data->env), buf, 0);
	free(buf);
	data->env_changed = 1;
	return (0);
}

/**
 * setenv_cmd - this function initialize a new env variable or modify it
 * @data: parameter struct
 *  Return: returns 0 on success
 */
int setenv_cmd(data_t *data)
{
	if (data->argc != 3)
	{
		err_puts("Wrong number of arguments...\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - This function remove an env variable
 * @data: parameter struct
 * @var: environment variable
 * Return: returns 1 on delete else 0
 */
int _unsetenv(data_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
	{
		return (0);
	}

	while (node)
	{
		p = _search(node->str, var);
		if (p && *p == '=')
		{
			data->env_changed = delete_node(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}


/**
 * unsetenv_cmd - This function remove an env variable
 * @data: parameter struct
 * Return: returns 0 on success
 */
int unsetenv_cmd(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		err_puts("Little arguements...\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
	{
		_unsetenv(data, data->argv[i]);
	}
	return (0);
}

