#include "shell.h"

/**
 * main - the main entry point or main function
 * @argc: argument count
 * @argv: argument vector
 * Return: returns 0 on success else 1 on error
 */

int main(int argc, char *argv[])
{
	data_t data[] = { DATA_INIT };
	int fd = 2;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				err_puts(argv[0]);
				err_puts(">0: Unable to open ");
				err_puts(argv[1]);
				err_putchar('\n');
				err_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fd;
	}
	build_env_list(data);
	read_log(data);
	hsh(data, argv);

	return (EXIT_SUCCESS);
}
