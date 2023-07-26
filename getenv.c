#include "shell.h"

/**
 * get_env - this function returns the string array copy of our env
 * @data: parameter struct
 * Return: returns 0 on success
 */
char **get_env(data_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = str_array(data->env);
		data->env_changed = 0;
	}
	return (data->environ);
}

/**
 * env_cmd - this function prints the current environment
 * @data: parameter struct
 * Return: returns 0 on success
 */
int env_cmd(data_t *data)
{
	print_str_list(data->env);
	return (0);
}

/**
 * _getenv - this function gets the value of an env variable
 * @data: parameter struct
 * @name: environment variable name
 * Return: returns the value of the environment
 */
char *_getenv(data_t *data, const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = _search(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}



/**
 * build_env_list - build the environment  list
 * @data: parameter struct
 * Return: returns 0 on success
 */
int build_env_list(data_t *data)
{
	size_t i;
	list_t *node = NULL;

	for (i = 0; environ[i]; i++)
	{
		add_node_at_end(&node, environ[i], 0);
	}
	data->env = node;
	return (0);
}
