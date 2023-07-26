#include "shell.h"

/**
 * cd_cmd - the func changes the current directory
 * @data: parameter struct containing potential arguments
 * Return: returns 0
 */
int cd_cmd(data_t *data)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts(">>The cakk to getcwd failed<<\n");
	if (!data->argv[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			chdir_ret = chdir("/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir(_getenv(data, "OLDPWD="));
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "cannot change directory to ");
		err_puts(data->argv[1]), err_putchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * exit_cmd - the func exits the shell as a builtin
 * @data: parameter struct containing potential arguments
 * Return: returns exits with a given exit status e.g (0)
 */
int exit_cmd(data_t *data)
{
	int check_exit_arg;
	int exit_code = -2;

	if (data->argv[1])
	{
		check_exit_arg = err_str(data->argv[1]);
		if (check_exit_arg == -1)
		{
			data->status = 2;
			print_error(data, "Wrong number: ");
			err_puts(data->argv[1]);
			err_putchar('\n');
			return (1);
		}
		data->err_num = check_exit_arg;
		return (exit_code);
	}
	data->err_num = -1;
	return (exit_code);
}

/**
* log_cmd - the func displays the log list
* @data: parameter struct containing potential arguments
* Return: returns 0
*/
int log_cmd(data_t *data)
{
	print_list(data->log);
	return (0);
}

/**
* alias_cmd - the func behaves like the alias builtin
* @data: parameter struct
* Return: returns 0 on success else 1 on error
*/
int alias_cmd(data_t *data)
{
	int i = 0;
	char *p = NULL;

	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = cus_strchr(data->argv[i], '=');
		if (p)
			set_alias(data, data->argv[i]);
		else
			print_alias(prefix_node(data->alias, data->argv[i], '='));
	}
	return (0);
}

/**
 * help_cmd - the func to display help information
 * @data: Parameter struct containing potential arguments
 * Return: returns 0
 */
int help_cmd(data_t *data)
{
	char **array;

	array = data->argv;
	_puts("Help is not yet available for this program.\n");
	if (0)
		_puts(*array);
	return (0);
}
