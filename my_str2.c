#include "main.h"
/**
<<<<<<< HEAD
 * _strdup - It replicates a str in the heap mem.
 * @s: The Type char. pointer str.
 * Return: already replicated str
=======
 * _strdup - This function duplicates a str in the heap memory.
 * @s: This function is used to Type a char pointer str
 * Return: duplicated str
>>>>>>> 65c78ef780649095742296407eb6201bd18dfa42
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
<<<<<<< HEAD
 * _strlen - This helps to Return the len of a str.
 * @s: The Type char. pointer.
=======
 * _strlen - this function is used to Return the lenght of a string.
 * @s: This is the function that is used to Type a char pointer
>>>>>>> 65c78ef780649095742296407eb6201bd18dfa42
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
<<<<<<< HEAD
 * cmp_chars - It helps compare the chars. of strings
 * @str: The Input str.
 * @delim: The Delimiter.
=======
 * cmp_chars - this function is used to compare chars of strings
 * @str: this function is used to input string.
 * @delim: delimiter.
>>>>>>> 65c78ef780649095742296407eb6201bd18dfa42
 *
 * Return: 1 if they are equal,and  0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int x, y, z;

	for (x = 0, z = 0; str[x]; x++)
	{
		for (y = 0; delim[y]; y++)
		{
			if (str[x] == delim[y])
			{
				z++;
				break;
			}
		}
	}
	if (x == z)
		return (1);
	return (0);
}

/**
<<<<<<< HEAD
 * _strtok - Helps to break (split) a str. by some delim.
 * @str: The Input Str.
 * @delim: The delim.
=======
 * _strtok - This function splits a string by some delimiter.
 * @str: This function is used to input string.
 * @delim: This is the delimiter.
>>>>>>> 65c78ef780649095742296407eb6201bd18dfa42
 *
 * Return: string already splited.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str;
		i = _strlen(str);
		str_end = &str[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{

		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
<<<<<<< HEAD
 * _isdigit - This shows if strthe ing passed is a numb.
 *
 * @s: The Input Str.
 * Return: 1 if it's a num. and 0 else.
=======
 * _isdigit - this code defines if string passed is a number
 *
 * @s: This function is used to input string
 * Return: 1 if string is a number. 0 in other case.
>>>>>>> 65c78ef780649095742296407eb6201bd18dfa42
 */
int _isdigit(const char *s)
{
	unsigned int j;

	for (j = 0; s[j]; j++)
	{
		if (s[j] < 48 || s[j] > 57)
			return (0);
	}
	return (1);
}
