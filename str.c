#include "shell.h"

/**
* _strcpy - the func copies a string
* @dest: destination
* @src: source
* Return: ptr to destination
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strcmp - the func compares two strings
* @s1: the first string
* @s2: the second string
* Return: returns 0 if strings are equal else -1
*/
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
* _strlen - the func returns the length of a string
* @str: the string's length being checked
* Return: returns the length of the string
*/
int _strlen(char *str)
{
	int i = 0;

	while (str[i])
	{
		i++;
	}
	return (i);
}

/**
* _strcat - the func concatenates two strings
* @dest: destination
* @src: source
* Return: returns a ptr to the resulting string
*/
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[i])
	{
		i++;
	}
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strdup - the func duplicates a string
* @str: string to be duplicated
* Return: ptr to the duplicated string
*/
char *_strdup(const char *str)
{
	char *dup;
	int i = 0, len = 0;

	if (!str)
	{
		return (NULL);
	}
	while (str[len])
	{
		len++;
	}
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
	{
		return (NULL);
	}
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
