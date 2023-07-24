#include "shell.h"

/**
 * add_node_at_start - the func adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: string field of node
 * @num: node's index
 * Return: returns the size of list
 */
list_t *add_node_at_start(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
	{
		return (NULL);
	}
	new_head = malloc(sizeof(list_t));
	if (!new_head)
	{
		return (NULL);
	}
	cus_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_at_end - the func adds a node to the end of the list
 * @head: pointer to the head node
 * @str: string field of node
 * @num: node's index
 * Return: returns the size of list
 */
list_t *add_node_at_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
	{
		return (NULL);
	}
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}
	cus_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * delete_node - the func deletes node at a given index
 * @head: pointer address to first / head node
 * @index: node's index to delete
 * Return: returns 1 on success else 0 on failure
 */
int delete_node(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
	{
		return (0);
	}
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * prefix_node - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: returns the match node else null
 */
list_t *prefix_node(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = _search(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - the func gets the index of a node
 * @head: pointer to head
 * @node: pointer to the node
 * Return: returns the index of node else returns -1
 */
ssize_t node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
		{
			return (i);
		}
		head = head->next;
		i++;
	}
	return (-1);
}
