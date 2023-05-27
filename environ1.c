#include "main.h"
/**
 * cmp_env_name - This code help compare environ var names.
 * with the passed name.
 * @nenv: The environ variable name.
 * @name: The passed name.
 *
 * Return: 0 if they are not equal, and other value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int x;

	for (x = 0; nenv[x] != '='; x++)
	{
		if (nenv[x] != name[x])
		{
			return (0);
		}
	}

	return (x + 1);
}
/**
 * _getenv - This gets environ var. name
 * @name: The environ var. name
 * @_environ: The environ var.
 *
 * Return: environ var (if is found).
 * Else, return Null.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int j, vom;


	ptr_env = NULL;
	vom = 0;
	for (j = 0; _environ[j]; j++)
	{
		vom = cmp_env_name(_environ[j], name);
		if (vom)
		{
			ptr_env = _environ[j];
			break;
		}
	}

	return (ptr_env + vom);
}
/**
 * _env - It helps to print env var.
 *
 * @datash: Relevant data.
 * Return: 1 if successful.
 */
int _env(data_shell *datash)
{
	int x, y;

	for (x = 0; datash->_environ[x]; x++)
	{

		for (y = 0; datash->_environ[x][y]; y++)
			;

		write(STDOUT_FILENO, datash->_environ[x], y);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
