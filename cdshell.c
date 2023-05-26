#include "main.h"
/**
 * cd_shell - This code changes the current dir
 *
 * @datash: The relevant data env.
 * Return: 1 if successful
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int emex, emex1, isemex;

	dir = datash->args[1];

	if (dir != NULL)
	{
		emex = _strcmp("$HOME", dir);
		emex1 = _strcmp("~", dir);
		isemex = _strcmp("--", dir);
	}

	if (dir == NULL || !emex || !emex1 || !isemex)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
