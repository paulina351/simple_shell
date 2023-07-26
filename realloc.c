#include "shell.h"

/**
* cus_memset - the func fills memory with a certain byte
* @s: pointer to the memory area
* @b: byte
* @n: number of bytes to be filled
* Return: returns pointer to the memory area
*/
char *cus_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}
/**
* cus_realloc - the func reallocates a block of memory
* @ptr: pointer to prev malloc
* @old_size: byte size of prev block
* @new_size: byte size of new block
* Return: returns pointer to the old block of memory
*/
void *cus_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (!new_size)
	{
		return (free(ptr), NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
* free_str - the func frees a string of strings
* @str_str: string of strings
*/

void free_str(char **str_str)
{
	char **a = str_str;

	if (!str_str)
	{
		return;
	}
	while (*str_str)
	{
		free(*str_str++);
	}
	free(a);
}

/**
* free_ptr - the func frees a pointer and NULLs the address
* @ptr: address of the pointer to free
* Return: returns 1 if freed else 0
*/
int free_ptr(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
	{
		return (0);
	}

	free(*ptr);
	*ptr = NULL;

	return (1);
}
