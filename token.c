#include "shell.h"

/**
* str_tok - the func splits a string into words
* @str: inputted string
* @d: delimeter str
* Return: returns a pointer to an array of strings else NULL
*/
char **str_tok(char *str, char *d)
{
	int i, j, k, m, count = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], d) && (is_delimiter(str[i + 1], d) || !str[i + 1]))
			count++;
	if (count == 0)
		return (NULL);
	s = (char **)malloc((count + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		while (is_delimiter(str[i], d))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], d) && str[i + k])
			k++;
		s[j] = (char *)malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}
	s[j] = NULL;
	return (s);
}

/**
* _strtok_ - the func splits a string into words
* @str: the string
* @d: the delimeter
* Return: returns a pointer to an array of strings else NULL
*/
char **_strtok_(char *str, char d)
{
	int i, j, k, m, count = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			count++;
	if (count == 0)
		return (NULL);
	s = malloc((count + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char *));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
* rep_alias - the func replaces aliases in the tokenized string
* @data: parameter struct
* Return: returns 1 if replaced else 0
*/
int rep_alias(data_t *data)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = prefix_node(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = cus_strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
* rep_vars - the func replaces variables in the tokenized string
* @data: parameter struct
* Return: returns 0
*/
int rep_vars(data_t *data)
{
	int i = 0;
	list_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;
		if (!_strcmp(data->argv[i], "$?"))
		{
			rep_string(&(data->argv[i]),
			_strdup(convert_num(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[i], "$$"))
		{
			rep_string(&(data->argv[i]),
			_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = prefix_node(data->env, &data->argv[i][1], '=');
		if (node)
		{
			rep_string(&(data->argv[i]),
			_strdup(cus_strchr(node->str, '=') + 1));
			continue;
		}
		rep_string(&data->argv[i], _strdup(""));
	}
	return (0);
}
/**
* rep_string - the func replaces a string
* @old: old string
* @new: new string
* Return: returns 1 on success else 0
*/
int rep_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
