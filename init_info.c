#include "shell.h"
/**
 * init_info - It initializes the info_t struct.
 * @info: The struct address.
 */
void init_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * reset_info - It resets the  info_t struct.
 * @info: Then struct address.
 * @arv: The argument vector
 */
void reset_info(info_t *info, char **arv)
{
	int j = 0;

	info->fname = arv[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		replace_alias(info);
		replace_vars(info);
	}
}
/**
 * frees_info - It sets free info_t struct file.
 * @info: The Struct address.
 * @al: Show true if setting all files free.
 */
void frees_info(info_t *info, int al)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (al)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		ffree((char **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
