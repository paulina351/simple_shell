#include "shell.h"

/**
 * list_len - the func determines length of linked list
 * @head: pointer to head node
 * Return: returns the size of list
 */
size_t list_len(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * free_list - the func frees all nodes of a list
 * @head_ptr: pointer to head node
 * Return: returns void / NULL
 */
void free_list(list_t **head_ptr)
{
	list_t *node;
	list_t *next_node;
	list_t *head;

	if (!head_ptr || !*head_ptr)
	{
		return;
	}
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * str_array - the func returns an array of strings
 * @head: pointer to head node
 * Return: returns the string array
 */
char **str_array(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strings;
	char *str;

	if (!head || !i)
	{
		return (NULL);
	}
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
	{
		return (NULL);
	}
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
			{
				free(strings[j]);
			}
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}


/**
 * print_list - the func prints all elements of a linked list
 * @head: pointer to head node
 * Return: returns the size of list
 */
size_t print_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(convert_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil...)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * print_str_list - the func prints only the str
 * element of a list_t linked list
 * @head: pointer to first/ head node
 * Return: returns the size of list
 */
size_t print_str_list(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil...)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}



