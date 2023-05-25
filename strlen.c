#include "shell.h"
/**
 * _strlen - This code returns the string length.
 * @s: The lenght of string to be checked.
 *
 * Return: the length of string (integer)
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - This code compares two strings lexicogarphically.
 * @s1: The 1st strang
 * @s2: The 2nd strang
 *
 * Return: -ve if s1 < s2, +ve if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - It Checks whether needle starts with haystack
 * @haystack: The string to be searched
 * @needle: The substring to Find.
 *
 * Return: Address of the next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - The concatenation of two strings.
 * @dest: The destination Buffer.
 * @src: The source BUFFER.
 *
 * Return: pointer to the destination Buffer.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
