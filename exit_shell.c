#include "main.h"
/**
 * exit_shell - The function is to exit the shell.
 *
 * @datash: Status and arguments(relevant data)
 * Return: 0 if successful.
 */
int exit_shell(data_shell *datash)
{
	int is_digit;
	int big_number;
	unsigned int ustatus;
	int str_len;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		is_digit = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}
