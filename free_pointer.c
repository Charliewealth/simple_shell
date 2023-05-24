#include "shell.h"

/**
 * freep - This command frees a pointer and NULLs the address
 * @ptf: This indicates the address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int freep(void **ptf)
{
	if (ptf && *ptf)
	{
		free(*ptf);
		*ptf = NULL;
		return (1);
	}
	return (0);
}

