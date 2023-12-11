#include "shell.h"

/**
 * odup_char - creates a duplicate of a character sequence
 * @strtostr: The string containing the PATH
 * @start: Index where duplication begins
 * @arrte: Index where duplication ends
 * Return: Pointer to the newly
 * allocated buffer with duplicated characters
 */
char *odup_char(char *strtostr, int start, int arrte)
{
	int i = 0, k = 0;
	static char buffer[1024];

	for (k = 0, i = start; i < arrte; i++)
	{
		if (strtostr[i] != ':')
			buffer[k++] = strtostr[i];
	}
	buffer[k] = 0;
	return (buffer);
}
/**
 * ois_cm - checks if a given file is
 * @info: Struct containing relevant information
 * @abspath: Filepath to be evaluated
 * Return: 1 if the file is executable, 0 if not
 */
int ois_cm(info_t *info, char *abspath)
{
	struct stat st;

	(void)info;
	if (!abspath || stat(abspath, &st))
	{
		return (0);
	}

	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}
/**
 * ofind_pat - finds this get_cmd in the PATH string
 * @info: the info struct
 * @strtostr: the PATH string
 * @get_cmd: the get_cmd to find
 *
 * Return: full abspath of get_cmd if found or NULL
 */
char *ofind_pat(info_t *info, char *strtostr, char *get_cmd)
{
	char *abspath;
	int i = 0, thenewpos = 0;

	if (!strtostr)
	{
		return (NULL);
	}
	if ((_strlen(get_cmd) > 2) && ostarts_wit(get_cmd, "./"))
	{
		if (ois_cm(info, get_cmd))
			return (get_cmd);
	}
	while (1)
	{
		if (!strtostr[i] || strtostr[i] == ':')
		{
			abspath = odup_char(strtostr, thenewpos, i);
			if (!*abspath)
				_strcat(abspath, get_cmd);
			else
			{
				_strcat(abspath, "/");
				_strcat(abspath, get_cmd);
			}
			if (ois_cm(info, abspath))
				return (abspath);
			if (!strtostr[i])
				break;
			thenewpos = i;
		}
		i++;
	}
	return (NULL);
}
