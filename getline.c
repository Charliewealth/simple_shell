#include "main.h"
/**
 * bring_line - Helps to assign Line var for getline.
 * @lineptr: Buffer (store the input str).
 * @buffer: The str which is called to Line.
 * @n: The Size of the line.
 * @k: Size of the BUFFER.
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t k)
{

	if (*lineptr == NULL)
	{
		if  (k > BUFSIZE)
			*n = k;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < k)
	{
		if (k > BUFSIZE)
			*n = k;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Helps to Read the inpt from stream.
 * @lineptr: Buffer (which store the input).
 * @n: The Size of the lineptr.
 * @stream: The stream from where to read
 * Return: The numb of Byte.
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	char *buffer;
	char t = 'z';
	int j;
	ssize_t retval;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		j = read(STDIN_FILENO, &t, 1);
		if (j == -1 || (j == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (j == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (j != 0)
		input = 0;
	return (retval);
}
