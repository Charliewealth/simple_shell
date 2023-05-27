#include "main.h"
/**
 * get_sigint - Helps to Handle the crtl + c prompt
 * @sig: The handler of the signal.
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
