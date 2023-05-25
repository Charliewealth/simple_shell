#include "shell.h"
/**
 * get_hist_file - It gets the history file.
 * @info: The parameter Struct.
 *
 * Return: Allocated string that contain history file.
 */
char *get_hist_file(info_t *info)
{
	char *buf, *direc;

	direc = _getenv(info, "HOME=");
	if (!direc)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, direc);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * write_hist - It creates a file and  append to  existing file
 * @info: The parameter struct.
 *
 * Return: 1 on success, else return -1
 */
int write_hist(info_t *info)
{
	ssize_t pd;
	char *filename = get_hist_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	pd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (pd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, pd);
		_putfd('\n', pd);
	}
	_putfd(BUF_FLUSH, pd);
	close(pd);
	return (1);
}
/**
 * read_hist - The reads file history.
 * @info: the parameter struct.
 *
 * Return: The histcount on success, 0 else.
 */
int read_hist(info_t *info)
{
	int j, last = 0, numcount = 0;
	ssize_t pd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(info);

	if (!filename)
		return (0);

	pd = open(filename, O_RDONLY);
	free(filename);
	if (pd == -1)
		return (0);
	if (!fstat(pd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(pd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(pd);
	for (j = 0; j < fsize; j++)
		if (buf[j] == '\n')
		{
			buf[j] = 0;
			build_hist_list(info, buf + last, numcount++);
			last = j + 1;
		}
	if (last != j)
		build_hist_list(info, buf + last, numcount++);
	free(buf);
	info->histcount = numcount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renum_hist(info);
	return (info->histcount);
}

/**
 * build_hist_list - It shows entry to history link list.
 * @info: The Structure that contains potential args
 * @buf: The buffer.
 * @linenumb: The history linenumb, histnumb.
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int numcount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, numcount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_hist - The renumber the history link list when changes are made.
 * @info: The Structure that contain potential arguments. Used to maintain
 *
 * Return: The new histcount
 */
int renum_hist(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
