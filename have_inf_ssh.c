#include "shell.h"

/**
 * oclear_inf - a function that initializes the info_t struct
 *
 * @inf: is the struct address
 *
 * Return: nothing
*/

void oclear_inf(info_t *inf)
{
	inf->arg = NULL;
	inf->argc = 0;
	inf->argv = NULL;
	inf->path = NULL;
}

/**
 * oset_inf - a function that initializes the info_t struct
 *
 * @inf: is the address of the struct
 * @av: is the argument vector
 *
 * Return: void
*/

void oset_inf(info_t *inf, char **av)
{
	int i = 0;

	inf->fname = av[0];

	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		while (inf->argv && inf->argv[i])
		{
			i++;
		}
		inf->argc = i;

		oreplace_alia(inf);
		oreplace_var(inf);
	}
}

/**
 * ofree_inf - a function that frees the fields of the info_t struct
 *
 * @inf: is the address of the struct
 * @free_all: is set true if all fields should be freed
 *
 * Return: nothing
*/

void ofree_inf(info_t *inf, int free_all)
{
	offre(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;

	if (free_all)
	{
		if (!inf->cmd_buf)
		{
			free(inf->arg);
		}
		if (inf->env)
		{
			ofree_lis(&(inf->env));
		}
		if (inf->history)
		{
			ofree_lis(&(inf->history));
		}
		if (inf->alias)
		{
			ofree_lis(&(inf->alias));
		}
		offre(inf->environ);
		inf->environ = NULL;
		obfre((void **)inf->cmd_buf);
		if (inf->readfd > 2)
		{
			close(inf->readfd);
		}
		_putchar(OBUF_FLUS);
	}
}
