#include "shell.h"
/**
 * **strtow - It splits a string into constituent words & ingnore Repeat delim
 * @str: represents input string
 * @d: represents the delimeter string
 * Return: Pointer to an array of strings,and or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, x, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		x = 0;
		while (!is_delim(str[i + x], d) && str[i + x])
			x++;
		s[j] = malloc((x + 1) * sizeof(char));
		if (!s[j])
		{
			for (x = 0; x < j; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < x; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
 * **strtow2 -this code splits a string into words
 * @str: represents input string
 * @d: represents the delimeter
 * Return: A pointer to an array of strings,and or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, x, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		x = 0;
		while (str[i + x] != d && str[i + x] && str[i + x] != d)
			x++;
		s[j] = malloc((x + 1) * sizeof(char));
		if (!s[j])
		{
			for (x = 0; x < j; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < x; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
