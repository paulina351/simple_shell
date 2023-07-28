#include "shell.h"

/**
* find_path - the func finds the full path of a command
* @data: the data struct
* @pathstr: the PATH string
* @cmd: command to find
* Return: returns the full path of cmd if found else NULL
*/
char *find_path(data_t *data, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && _search(cmd, "./"))
	{
		if (is_cmd(data, cmd))
		return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(data, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}


/**
* is_cmd - the func checks if a file is a command
* @data: the data struct
* @path: PATH
* Return: returns 1 if cmd else 0
*/
int is_cmd(data_t *data, char *path)
{
	struct stat st;

	if (stat(path, &st) == 0)
	{
		if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
		{
			return (1);
		}
		else
		{
			data->status = 126;
			print_error(data, "Denied Access\n");
		}
	}
	return (0);
}

/**
* dup_chars - the func duplicates chars from a string
* @pathstr: the PATH string
* @start: index start
* @end: index end
* Return: returns a pointer to the duplicated chars
*/
char *dup_chars(char *pathstr, int start, int end)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < end; i++)
		if (pathstr[i] != ':')
		{
			buf[k++] = pathstr[i];
		}
	buf[k] = 0;
	return (buf);
}
