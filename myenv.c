#include "shell.h"
/**
 * _myenv - This program prints the current environment
 * @info: The Struct that contain potential args Used to maintain
 *          a constant function prototype
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - It prints the value of environ variables.
 * @info: The Structure that contains potential args Used to maintain
 * @name: env variable name.
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *c;

	while (node)
	{
		c = starts_with(node->str, name);
		if (c && *c)
			return (c);
		node = node->next;
	}
	return (NULL);
}
/**
 * _setenv - It sets a new environment variable
 *             or modifies the existing one.
 * @info: The Structure that contains potential args Used to maintain
 *        a constant function prototype.
 *  Return: Always 0
 */
int _setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _unsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}
/**
 * increase_env_list - It increase  env linked lists.
 * @info: The Structure that contains potential args Used to maintain
 *          a constant function prototype.
 * Return: Always 0
 */
int increase_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
