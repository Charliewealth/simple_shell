#include "shell.h"
/**
 * is_erratoi - It converts string to integer
 * @l: The string to convert
 * Return: 0 if no numb in string, converted numb otherwise
 *       -1 on error
 */
int is_erratoi(char *l)
{
	int j = 0;
	unsigned long int result = 0;

	if (*l == '+')
		l++;
	for (j = 0;  l[j] != '\0'; j++)
	{
		if (l[j] >= '0' && l[j] <= '9')
		{
			result *= 10;
			result += (l[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - It prints error message.
 * @info: The parameter and info struct
 * @estr: The string that contain specific error.
 * Return: 0 if no numb in string, converted numb otherwise
 *        -1 on error
 */
void print_err(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_dec - The function that prints decimal  number in base 10
 * @input: The input.
 * @fdes: The filedescriptor to be writen to
 *
 * Return: The number of chars printed
 */
int print_dec(int input, int fdes)
{
	int (*__putchar)(char) = _putchar;
	int x, numb = 0;
	unsigned int _abs_, current;

	if (fdes == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		numb++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + current / x);
			numb++;
		}
		current %= x;
	}
	__putchar('0' + current);
	numb++;

	return (numb);
}

/**
 * conv_numb - The converter Function.
 * @num: The number
 * @bs: The base
 * @flag: The argument flags
 *
 * Return: The string
 */
char *conv_numb(long int num, int bs, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flag & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % bs];
		n /= bs;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remov_comm - The function That replace first instance of # with \0
 * @buf: The address of the string to be modified
 *
 * Return: Always 0;
 */
void remov_comm(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
