#include "shell.h"

/**
 * oget_history_fil - a function that gets the history file
 *
 * @info: is the struct of the parameter
 *
 * Return: the allocated string that contains the history file
*/

char *oget_history_fil(info_t *info)
{
	char *buff, *direc;

	direc = o_geten(info, "HOME=");

	if (direc == NULL)
	{
		return (NULL);
	}
	buff = malloc(sizeof(char) * (_strlen(direc) + _strlen(OHIST_FIL) + 2));

	if (buff == NULL)
	{
		return (NULL);
	}
	buff[0] = 0;
	_strcpy(buff, direc);
	_strcat(buff, "/");
	_strcat(buff, OHIST_FIL);
	return (buff);
}

/**
 * owrite_histor - a function that creates a file,
 *	or appends to an existing file
 *
 * @info: is the parameter struct
 *
 * Return: on success return 1, otherwise -1
*/

int owrite_histor(info_t *info)
{
	ssize_t fdess;
	char *f_name = oget_history_fil(info);
	list_t *nod = NULL;

	if (f_name == NULL)
	{
		return (-1);
	}
	fdess = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);

	if (fdess == -1)
	{
		return (-1);
	}
	for (nod = info->history; nod; nod = nod->next)
	{
		o_putsf(nod->str, fdess);
		o_putf('\n', fdess);
	}
	o_putf(OBUF_FLUS, fdess);
	close(fdess);
	return (1);
}

/**
 * oread_histor - a function that reads history from file
 *
 * @info: is the struct of the parameter
 *
 * Return: on success return histcount , otherwise return 0
*/

int oread_histor(info_t *info)
{
	int i, las = 0, l_count = 0;
	ssize_t fdess, len, f_size = 0;
	struct stat st;
	char *buff = NULL, *f_name = oget_history_fil(info);

	if (f_name == NULL)
		return (0);
	fdess = open(f_name, O_RDONLY);
	free(f_name);
	if (fdess == -1)
		return (0);
	if (!fstat(fdess, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	len = read(fdess, buff, f_size);
	buff[f_size] = 0;
	if (len <= 0)
		return (free(buff), 0);
	close(fdess);
	for (i = 0; i < f_size; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			obuild_history_lis(info, buff + las, l_count++);
			las = i + 1;
		}
	if (las != i)
		obuild_history_lis(info, buff + las, l_count++);
	free(buff);
	info->histcount = l_count;
	while (info->histcount-- >= OHIST_MA)
	{
		odelete_node_at_inde(&(info->history), 0);
	}
	orenumber_histor(info);
	return (info->histcount);
}

/**
 * obuild_history_lis - a function that adds entry to a history linked list
 *
 * @info: is a Structure that contains potential arguments
 *	Used in maintaining a constant function prototype
 * @buff: is a buffer
 * @l_count: is the history linecount, histcount
 *
 * Return: Always 0 (Success)
*/

int obuild_history_lis(info_t *info, char *buff, int l_count)
{
	list_t *nod = NULL;

	if (info->history)
	{
		nod = info->history;
	}
	oadd_node_en(&nod, buff, l_count);

	if (!info->history)
	{
		info->history = nod;
	}
	return (0);
}

/**
 * orenumber_histor - a function that renumbers the history
 *	linked list after the changes
 *
 * @info: is a Structure that contains the potential arguments,
 *	used in maintaining a constant function prototype
 *
 * Return: the new histcount is returned
*/

int orenumber_histor(info_t *info)
{
	list_t *nod = info->history;
	int i = 0;

	while (nod != NULL)
	{
		nod->num = i++;
		nod = nod->next;
	}
	return (info->histcount = i);
}
