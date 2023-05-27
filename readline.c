#include "main.h"
/**
 * read_line -Helps to read Input String.
 *
 * @i_eof: It returns the value of getline funct.
 * Return: The Input str.
 */
char *read_line(int *i_eof)
{
	char *inp = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&inp, &bufsize, stdin);

	return (inp);
}
