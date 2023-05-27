#include "main.h"
/**
 * without_comment - Helps to remove(delete) comments from the input.
 *
 * @a: The Input Str.
 * Return: any input without comments.
 */
char *without_comment(char *a)
{
	int x, upto;

	upto = 0;
	for (x = 0; a[x]; x++)
	{
		if (a[x] == '#')
		{
			if (x == 0)
			{
				free(a);
				return (NULL);
			}

			if (a[x - 1] == ' ' || a[x - 1] == '\t' || a[x - 1] == ';')
				upto = x;
		}
	}

	if (upto != 0)
	{
		a = _realloc(a, x, upto + 1);
		a[upto] = '\0';
	}

	return (a);
}

/**
 * shell_loop - That is Loop of The shell.
 * @datash: av, input, args(data relevant)
 *
 * Return: nothing
 */
void shell_loop(data_shell *datash)
{
	int loope, i_eof;
	char *input;

	loope = 1;
	while (loope == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;
			input = rep_var(input, datash);
			loope = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loope = 0;
			free(input);
		}
	}
}
