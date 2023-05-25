#include "shell.h"
/**
 * _memset - This code fills the memory with constant byte.
 * @s: The Pointer to the memory Area.
 * @b: The byte to fill *s with.
 * @n: The num of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - To get a string of strings.
 * @pp: The String of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}
/**
 * _realloc - Reallocation of a block of memory
 * @ptr: The Pointer to previous malloc'ated block
 * @old_size: The byte size of previous block
 * @new_size: new block byte size
 *
 * Return: pointer to daol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

