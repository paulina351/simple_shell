#include "shell.h"

/**
 * hsh - the func runs the shell in interactive or non interactive mode
 * @data: the parameter and return data struct
 * @argv: the parameter argument vector
 * Return: returns 0 on success else 1 on error
 */

int hsh(data_t *data, char **argv)
{
	ssize_t ret = 0;
	int builtin = 0;

	while (ret != -1 && builtin != -2)
	{
		clear_data(data);
		if (is_interactive(data))
		{
			_puts("SP>> ");
		}
		err_putchar(BUF_FLUSH);
		ret = get_input(data);
		if (ret != -1)
		{
			set_data(data, argv);
			builtin = find_commands(data);
			if (builtin == -1)
			{
				find_cmd(data);
			}
		}
		else if (is_interactive(data))
		{
			_putchar('\n');
		}
		free_data(data, 0);
	}
	write_log(data);
	free_data(data, 1);
	if (!is_interactive(data) && data->status)
		exit(data->status);
	if (builtin == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin);
}

/**
 * find_commands - the func finds a builtin command
 * @data: the parameter and return data struct
 * Return: returns 0 on success else 1 on error
 */

int find_commands(data_t *data)
{
	int i, builtin = -1;

	cmd_table builtintbl[] = {
		{"exit", exit_cmd},
		{"cd", cd_cmd},
		{"log", log_cmd},
		{"alias", alias_cmd},
		{"help", help_cmd},
		{"env", env_cmd},
		{"setenv", setenv_cmd},
		{"unsetenv", unsetenv_cmd},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(data->argv[0], builtintbl[i].type) == 0)
		{
			data->line_count++;
			builtin = builtintbl[i].func(data);
			break;
		}
	return (builtin);
}

/**
 * find_cmd - the func finds a command in the PATH
 * @data: the parameter and return data struct
 * Return: returns void
 */

void find_cmd(data_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
		if (!is_delimiter(data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = find_path(data, _getenv(data, "PATH=>"), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((is_interactive(data) || _getenv(data, "PATH=>")
					|| data->argv[0][0] == '/') && is_cmd(data, data->argv[0]))
		{
			fork_cmd(data);
		}
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "path not found\n");
		}
	}
}

/**
 * fork_cmd - the func forks an executable to run cmd process(pid)
 * @data: data struct parameter
 * return: returns void
 */

void fork_cmd(data_t *data)
{
	pid_t pid_child;

	pid_child = fork();
	if (pid_child == -1)
	{
		perror("Process Error: ");
		return;
	}
	if (pid_child == 0)
	{
			if (execve(data->path, data->argv, get_env(data)) == -1)
			{
				free_data(data, 1);
				if (errno == EACCES)
					exit(126);
				exit(1);
			}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
			{

				print_error(data, "Access Denied\n");
			}
		}
	}
}
