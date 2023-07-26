#include "shell.h"

/**
 * log_file - the func gets the log file
 * @data: parameter struct
 * Return: returns the log file
 */

char *log_file(data_t *data)
{
	char *buff, *dir;

	dir = _getenv(data, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(LOG_FILE) + 2));
	if (!buff)
	{
		return (NULL);
	}
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, LOG_FILE);
	return (buff);
}

/**
 * write_log - the func creates a new file or appends to an existing file
 * @data: the parameter struct
 * Return: returns 1 on success else -1 on error
 */
int write_log(data_t *data)
{
	ssize_t fd;
	char *filename = log_file(data);
	list_t *node = NULL;

	if (!filename)
	{
		return (-1);
	}
	fd = open(filename, CREATE_TRUNC_RW, 0644);
	free(filename);
	if (fd == -1)
	{
		return (-1);
	}
	for (node = data->log; node; node = node->next)
	{
		_putstr(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_log - the func reads log from file
 * @data: the parameter struct
 * Return: returns the log on success (0) else error
 */
int read_log(data_t *data)
{
	int i, count = 0, end = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = log_file(data);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_log(data, buffer + end, count++);
			end = i + 1;
		}
	if (end != i)
		build_log(data, buffer + end, count++);
	free(buffer);
	data->logcount = count;
	while (data->logcount-- >= LOG_MAX)
		delete_node(&(data->log), 0);
	reorder_log(data);
	return (data->logcount);
}

/**
 * build_log - the func adds an entry to the log
 * @data: the parameter struct
 * @buff: buffer
 * @count: log count
 * Return: returns 0
 */
int build_log(data_t *data, char *buff, int count)
{
	list_t *node = NULL;

	if (data->log)
	{
		node = data->log;
	}
	add_node_at_end(&node, buff, count);

	if (!data->log)
	{
		data->log = node;
	}
	return (0);
}

/**
 * reorder_log - the func renumbers the log linked list after changes
 * @data: parameter struct
 * Return: returns the new log count
 */
int reorder_log(data_t *data)
{
	int i = 0;
	list_t *node = data->log;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->logcount = i);
}

