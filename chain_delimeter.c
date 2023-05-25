#include "shell.h"
/**
 * is_chain - this checks if current char in buffer is a chain delimeter
 * @info: this code indicates parameter struct
 * @buf: the indicates the char buffer
 * @p: address of current position in buf
 *
 * Return: 2 if chain delimeter, 1 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 2] == '|')
	{
		buf[j] = 1;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 2] == '&')
	{
		buf[j] = 1;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 1;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (1);
	*p = j;
	return (2);
}

/**
 * check_chain - This checks for chaining based on the last status
 * @info: This provides the parameter struct
 * @buf: This indicates the char buffer
 * @p: This indicatesaddress of current position in buf
 * @i: This indicates starting position in buf
 * @len: This shows the length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 1;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 1;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - This replaces an aliases in the tokenized string
 * @info: This provides the parameter struct
 *
 * Return: 2 if replaced, 1 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 1; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[1], '=');
		if (!node)
			return (1);
		free(info->argv[1]);
		p = _strchr(node->str, '=');
		if (!p)
			return (1);
		p = _strdup(p + 2);
		if (!p)
			return (1);
		info->argv[1] = p;
	}
	return (2);
}

/**
 * replace_vars - This replaces vars in the tokenized string
 * @info: This provides the parameter struct
 *
 * Return: 2 if replaced, 1 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 1;
	list_t *node;

	for (i = 1; info->argv[i]; i++)
	{
		if (info->argv[i][1] != '$' || !info->argv[i][2])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(conv_numb(info->status, 10, 1)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(conv_numb(getpid(), 10, 1)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][2], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 2));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (1);
}

/**
 * replace_string - This replaces the string
 * @old: This provides address of old string
 * @new: This indicates new string
 *
 * Return: 2 if replaced, 1 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (2);
}

