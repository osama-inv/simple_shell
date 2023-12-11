#include "shell.h"

/**
 * o_myhistor - a function that displays the history list, starting at 0,
 *	one command by line, preceded with line numbers
 *
 * @inf: is a structure that contains potential arguments,
 *	Used in maintainiga constant function prototype
 *
 * Return: Always return 0 (Success)
*/

int o_myhistor(info_t *inf)
{
	oprint_lis(inf->history);

	return (0);
}

/**
 * ounset_alia - a function that sets alias to string
 *
 * @inf: is the struct of the parameter
 * @strin: is the alias string
 *
 * Return: Always 0 (success), when error return 1
*/

int ounset_alia(info_t *inf, char *strin)
{
	int retrn;
	char *ptr, ch;

	ptr = _strchr(strin, '=');

	if (!ptr)
	{
		return (1);
	}
	ch = *ptr;
	*ptr = 0;
	retrn = odelete_node_at_inde(&(inf->alias),
			oget_node_inde(inf->alias, onode_starts_wit(inf->alias, strin, -1)));
	*ptr = ch;

	return (retrn);
}

/**
 * oset_alia - a function that sets alias to the string
 *
 * @inf: is the struct of the parameter
 * @strin: is the alias string
 *
 * Return: Always 0 (success), when error return 1
*/

int oset_alia(info_t *inf, char *strin)
{
	char *ptr;

	ptr = _strchr(strin, '=');

	if (ptr == NULL)
	{
		return (1);
	}
	if (!*(++ptr))
	{
		return (ounset_alia(inf, strin));
	}
	ounset_alia(inf, strin);
	return (oadd_node_en(&(inf->alias), strin, 0) == NULL);
}

/**
 * oprint_alia - a function that prints an alias string
 *
 * @n: is the node of alias
 *
 * Return: Always 0 (success), when error return 1
*/

int oprint_alia(list_t *n)
{
	char *ptr = NULL, *i = NULL;

	if (n != NULL)
	{
		ptr = _strchr(n->strin, '=');
		for (i = n->strin; i <= ptr; i++)
		{
			_putchar(*i);
		}
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * o_myalia - a function that mimics the alias builtin
 *
 * @inf: is a structure that contains potential arguments,
 *	Used to maintain constant function prototype
 *
 * Return: Always 0 (Success)
*/

int o_myalia(info_t *inf)
{
	int n = 0;
	list_t *nod = NULL;
	char *ptr = NULL;

	if (inf->argc == 1)
	{
		nod = inf->alias;
		while (nod != NULL)
		{
			oprint_alia(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (n = 1; inf->argv[n]; n++)
	{
		ptr = _strchr(inf->argv[n], '=');
		if (ptr != NULL)
		{
			oset_alia(inf, inf->argv[n]);
		}
		else
		{
			oprint_alia(onode_starts_wit(inf->alias, inf->argv[n], '='));
		}
	}
	return (0);
}
