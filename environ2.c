#include "main.h"
/**
 * copy_info - This code copies info which is uses
 * form new environ (alias)
 * @name: The name of env (alias)
 * @value: The value of env (alias)
 *
 * Return: A new env (alias).
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}
/**
 * set_env - It helps to set environ var.
 *
 * @name: The environ var. name
 * @value: The environ var. value
 * @datash: The data struct of environ)
 * Return: nothing
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int a;
	char *var_env, *name_env;

	for (a = 0; datash->_environ[a]; a++)
	{
		var_env = _strdup(datash->_environ[a]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[a]);
			datash->_environ[a] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, a, sizeof(char *) * (a + 2));
	datash->_environ[a] = copy_info(name, value);
	datash->_environ[a + 1] = NULL;
}
/**
 * _setenv - It helps to compare environ var. names
 * with the passed names.
 * @datash: env name and env value (relevant data).
 *
 * Return: 1 if successful.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}
/**
 * _unsetenv - It helps delete(remove) environ var.
 *
 * @datash: env name(relevant data)
 *
 * Return: 1 if successful
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int x, y, z;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	z = -1;
	for (x = 0; datash->_environ[x]; x++)
	{
		var_env = _strdup(datash->_environ[x]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			z = x;
		}
		free(var_env);
	}
	if (z == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (x));
	for (x = y = 0; datash->_environ[x]; x++)
	{
		if (x != z)
		{
			realloc_environ[y] = datash->_environ[x];
			y++;
		}
	}
	realloc_environ[y] = NULL;
	free(datash->_environ[z]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
