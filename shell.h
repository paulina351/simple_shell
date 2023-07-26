#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>

#define BUF_SIZE 1024
#define BUF_FLUSH -1
#define SMALL_BUF_SIZE 50
#define LOG_FILE ".simple_shell_history"
#define LOG_MAX 4096
#define CMD_REG 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_STRING 3
#define CONV_UNSIGNED 2
#define CONV_LOWERCASE 1
#define USE_GETLINE 0
#define CREATE_TRUNC_RW (O_CREAT | O_TRUNC | O_RDWR)

#define DATA_INIT \
{ \
	NULL, \
	NULL, \
	NULL, \
	NULL, \
	0, \
	NULL, \
	NULL, \
	0, \
	NULL, \
	0, \
	0, \
	NULL, \
	0, \
	0, \
	0, \
	NULL, \
	0, \
	0 \
}

extern char **environ;

/**
* struct liststr - the struct is singly linked list
* @num: the number field
* @str: a string
* @next: points to the next node
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
* struct data - struct for passing data to functions
* @alias: the alias node
* @arg: a string generated from getline containing arguements
* @argv:an array of strings generated from arg
* @argc: the argument count
* @cmd_buf: address of pointer to cmd_buf, on if chaining
* @cmd_buf_type: CMD_type ||, &&, ;
* @env: linked list local copy of environ
* @environ: custom modified copy of environ from LL env
* @env_changed: on if environ was changed
* @err_num: the error code for exit()s
* @fname: the program filename
* @log: the history node
* @logcount: the log line number count
* @line_count: the error count
* @linecount_flag: if on count this line of input
* @path: a string path for the current command
* @readfd: the fd from which to read line input
* @status: the return status of the last exec'd command
* Description: data holder
*/
typedef struct data
{
	list_t *alias;
	list_t *env;
	list_t *log;
	char *arg;
	int argc;
	char **argv;
	char **cmd_buf;
	int cmd_buf_type;
	char **environ;
	int env_changed;
	int err_num;
	char *fname;
	unsigned int line_count;
	int linecount_flag;
	int logcount;
	char *path;
	int readfd;
	int status;
} data_t;

/**
* struct cmd - struct for builtin commands
* @type: the type is a ptr to the command
* @func: the func is a ptr to the builtin func
*/
typedef struct cmd
{
	char *type;
	int (*func)(data_t *);
} cmd_table;

/**_cmd.c**/
int cd_cmd(data_t *data);
int exit_cmd(data_t *data);
int log_cmd(data_t *data);
int alias_cmd(data_t *data);
int help_cmd(data_t *data);

/**alias.c**/
int set_alias(data_t *data, char *str);
int unset_alias(data_t *data, char *str);
int print_alias(list_t *node);

/**atoi.c**/
int _atoi(char *str);

/**check.c**/
int is_interactive(data_t *data);
int is_delimiter(char c, char *delim);
int is_alphabet(int c);
int is_chain_delim(data_t *data, char *buf, size_t *p);
void is_valid_chain(data_t *data, char *buff, size_t *p, size_t i, size_t len);

/**command.c**/
int hsh(data_t *data, char **av);
int find_commands(data_t *data);
void find_cmd(data_t *data);
void fork_cmd(data_t *data);

/**error.c**/
void print_error(data_t *data, char *str_err);
int err_str(char *str);
int prints_deci(int input, int fd);
char *convert_num(long int num, int b, int f);
void rem_comments(char *buff);

/**err_puts.c**/
int err_putchar(char c);
void err_puts(char *str);
int _putfd(char c, int fd);
int _putstr(char *str, int fd);

/**get_data**/
void clear_data(data_t *data);
void set_data(data_t *data, char **av);
void free_data(data_t *data, int all);

/**getenv.c**/
char **get_env(data_t *data);
int env_cmd(data_t *data);
int build_env_list(data_t *data);
char *_getenv(data_t *data, const char *name);

/**getline.c**/
ssize_t read_buffer(data_t *data, char *buff, size_t *i);
int cus_getline(data_t *data, char **ptr, size_t *size);

/**handler**/
ssize_t input_buffer(data_t *data, char **buff, size_t *len);
ssize_t get_input(data_t *data);
void sigint_handle(__attribute__((unused))int sig_num);

/**list.c**/
size_t list_len(const list_t *head);
void free_list(list_t **head_ptr);
char **str_array(list_t *head);
size_t print_list(const list_t *head);
size_t print_str_list(const list_t *head);

/**log.c**/
char *log_file(data_t *data);
int write_log(data_t *data);
int read_log(data_t *data);
int build_log(data_t *data, char *buff, int count);
int reorder_log(data_t *data);

/**node.c**/
list_t *add_node_at_start(list_t **head, const char *str, int num);
list_t *add_node_at_end(list_t **head, const char *str, int num);
int delete_node(list_t **head, unsigned int index);
list_t *prefix_node(list_t *node, char *prefix, char c);
ssize_t node_index(list_t *head, list_t *node);

/**path.c**/
char *find_path(data_t *data, char *pathstr, char *cmd);
int is_cmd(data_t *data, char *path);
char *dup_chars(char *pathstr, int start, int end);

/**puts.c**/
void _puts(char *str);
int _putchar(char c);

/**realloc.c**/
char *cus_memset(char *s, char b, unsigned int n);
void *cus_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_str(char **str_str);
int free_ptr(void **ptr);

/**setenv**/
int _setenv(data_t *data, char *var, char *value);
int setenv_cmd(data_t *data);
int _unsetenv(data_t *data, char *var);
int unsetenv_cmd(data_t *data);

/**str.c**/
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strlen(char *str);
char *_strcat(char *dest, char *src);
char *_strdup(const char *str);

/**string.c**/
char *cus_strncpy(char *dest, char *src, int num);
char *cus_strncat(char *dest, char *src, int num);
char *cus_strchr(char *str, char c);
char *_search(const char *h, const char *n);

/**token.c**/
char **str_tok(char *str, char *d);
char **_strtok_(char *str, char d);
int rep_alias(data_t *data);
int rep_vars(data_t *data);
int rep_string(char **old, char *new);

#endif /* SHELL_H_ */
