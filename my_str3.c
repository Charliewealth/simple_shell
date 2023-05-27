#include "main.h"
/**
 * rev_string - This code helps to reverse a str.
 * @s: The Input str.
 * Return: nothing.
 */
void rev_string(char *s)
{
	int num = 0, i, j;
	char *str, temp;

	while (num >= 0)
	{
		if (s[num] == '\0')
			break;
		num++;
	}
	str = s;

	for (i = 0; i < (num - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
