#include "shell.h"

/**
 * cus_strncpy - the func copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @num: the number of characters to be copied
 * Return: returns the concatenated string
 */

char *cus_strncpy(char *dest, char *src, int num)
{
	int i = 0, j;
	char *s = dest;

	while (src[i] != '\0' && i < num - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * cus_strncat - the func concatenates two strings together
 * @dest: the first str
 * @src: the second str
 * @num: the number of bytes used
 * Return: returns the concatenated string
 */

char *cus_strncat(char *dest, char *src, int num)
{
	int i = 0, j = 0;
	char *s = dest;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && j < num)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
	{
		dest[i] = '\0';
	}
	return (s);
}

/**
 * cus_strchr - the func locates a character in a string
 * @str: the string to be parsed
 * @c: the character
 * Return: returns a pointer to the memory of the string
 */

char *cus_strchr(char *str, char c)
{
	do {
		if (*str == c)
		{
			return (str);
		}
	} while (*str++ != '\0');

	return (NULL);
}

/**
* _search - the func checks if needle starts with haystack
* @h: haystack to search in
* @n: needle to search for
* Return: address of next char of h or NULL
*/

char *_search(const char *h, const char *n)
{
	while (*h && *n)
	{
		if (*h != *n)
			return (NULL);
		h++;
		n++;
	}
	if (*n)
		return (NULL);
	return ((char *)h);
}

