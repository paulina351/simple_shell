#include "shell.h"

/**
* set_alias - the func sets alias to string
* @data: parameter struct
* @str: the string alias
* Return: returns 0 on success else 1 on error
*/
int set_alias(data_t *data, char *str)
{
	char *p;

	p = cus_strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	if (!*++p)
	{
		return (unset_alias(data, str));
	}
	unset_alias(data, str);
	return (add_node_at_end(&(data->alias), str, 0) == NULL);
}
/**
* unset_alias - the func unsets alias to string
* @data: parameter struct
* @str: the string alias
* Return: Returns 0 on success else 1 on error
*/
int unset_alias(data_t *data, char *str)
{
	char *p, c;

	p = cus_strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	c = *p;
	*p = 0;

	*p = c;
	return (delete_node(&(data->alias),
				node_index(data->alias, prefix_node(data->alias, str, -1))));
}


/**
* print_alias - the func prints an alias
* @node: the alias node
* Return: returns 0 on success else 1 on error
*/
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = cus_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		{
			_putchar(*a);
		}
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
