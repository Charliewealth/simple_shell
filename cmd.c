#include "shell.h"
/**
 * _cmd - shows whether a file is executable
 * @info: this is info struct
 * @path: the path leading to the file
 *
 * Return: 1 if true, otherwise 0
 */
int _cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - It duplicates the characters
 * @pathstr: The path leading to string
 * @start: The Starting INDEX
 * @stop: The Stopping INDEX
 *
 * Return: The pointer to a new Buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[y++] = pathstr[x];
	buf[y] = 0;
	return (buf);
}

/**
 * get_path - locates  cmd in the path string
 * @info: information struct
 * @pathstr: the string Path
 * @cmd: The cmd to be found
 *
 * Return: The full path of the cmd if found or NULL
 */
char *get_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, curr_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			curr_pos = a;
		}
		a++;
	}
	return (NULL);
}
