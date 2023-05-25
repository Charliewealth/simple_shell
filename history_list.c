#include "shell.h"
/**
 * _history - This displays history list, one command by line, preceded
 *              with the line numbers and starts from 0.
 * @info: This is the structure containing potential arguments. It maintains
 *        constant function prototype.
 *  Return: Always 0
 */
int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - This command sets alias to string
 * @info: This indicates the parameter struct
 * @stra: This indicates the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *stra)
{
	char *c, a;
	int del;

	c = _strchr(stra, '=');
	if (!c)
		return (1);
	a = *c;
	*c = 0;
	del = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, stra, -1)));
	*c = a;
	return (del);
}
/**
 * set_alias - This command sets alias to The string.
 * @info: This indicates the parameter struct.
 * @str: This provides the string alias.
 *
 * Return: Always 0 on success, 1 else.
 */
int set_alias(info_t *info, char *str)
{
	char *c;

	c = _strchr(str, '=');
	if (!c)
		return (1);
	if (!*++c)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - This code prints an alias String.
 * @node: this indicates the alias node
 *
 * Return: Always 0 on success, 1 else
 */
int print_alias(list_t *node)
{
	char *c = NULL, *a = NULL;

	if (node)
	{
		c = _strchr(node->str, '=');
		for (a = node->str; a <= c; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(c + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _mimicalias - This command mimics the builtin alias(man alias).
 * @info: This is the structure containing potential arguments. maintains
 *          constant function prototype.
 *  Return: Always 0
 */
int _mimicalias(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = _strchr(info->argv[j], '=');
		if (p)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}
	return (0);
}

