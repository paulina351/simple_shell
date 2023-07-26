#include "shell.h"

/**
 * read_buffer - the func reads a buffer
 * @data: parameter struct
 * @buff: buffer
 * @s: size
 * Return: returns read size
 */
ssize_t read_buffer(data_t *data, char *buff, size_t *s)
{
	ssize_t r = 0;

	if (*s == 0)
	{
		r = read(data->readfd, buff, BUF_SIZE);
		if (r == -1)
			return (-1);
		*s = r;
	}
	return (r);
}

/**
 * cus_getline - the func gets the next line from standard input
 * @data: parameter struct
 * @ptr: pointer to address
 * @size: length of buffer
 * Return: returns string
 */
int cus_getline(data_t *data, char **ptr, size_t *size)
{
	static char buf[BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, str = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && size)
		str = *size;
	if (i == len)
		i = len = 0;

	r = read_buffer(data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = cus_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = cus_realloc(p, str, str ? str + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (str)
		cus_strncat(new_p, buf + i, k - i);
	else
		cus_strncpy(new_p, buf + i, k - i + 1);

	str += k - i;
	i = k;
	p = new_p;

	if (size)
		*size = str;
	*ptr = p;
	return (str);
}
