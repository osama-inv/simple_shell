#include "shell.h"

/**
 * oget_enviro - a function that returns the copy of the string array
 *	of the environment
 * @inf: is the structure that contains potential arguments,
 *	used in maintainingconstant function prototype
 *
 * Return: Always 0 (Success)
*/

char **oget_enviro(info_t *inf)
{
	if (inf->env_changed || !inf->environ)
	{
		inf->environ = olist_to_string(inf->env);
		inf->env_changed = 0;
	}
	return (inf->environ);
}

/**
 * o_unseten - a function that removes an environment variable
 *
 * @inf: is the structure that contains potential arguments,
 *	used in maintaining a constant function prototype
 * @var: is the string environent variable property
 *
 * Return: 1 on delete, otherwise return 0
*/

int o_unseten(info_t *inf, char *var)
{
	size_t i = 0;
	list_t *nod = inf->env;
	char *ptr;

	if (var == NULL || nod == NULL)
	{
		return (0);
	}
	while (nod != NULL)
	{
		ptr = ostarts_wit(nod->str, var);
		if (ptr && *ptr == '=')
		{
			inf->env_changed = odelete_node_at_inde(&(inf->env), i);
			i = 0;
			nod = inf->env;
			continue;
		}
		nod = nod->next;
		i++;
	}
	return (inf->env_changed);
}

/**
 * o_seten - a function that initialize a new environment variable,
 *	or modifies an existing one
 *
 * @inf: is a structure that contains potential arguments,
 *	used to maintain a constant function prototype
 * @var: is the string environment variable property
 * @valu: is the string environment variable value
 *
 * Return: Always 0 (Success)
*/

int o_seten(info_t *inf, char *var, char *valu)
{
	char *buff = NULL;
	list_t *nod;
	char *ptr;

	if (var == NULL || valu == NULL)
	{
		return (0);
	}
	buff = malloc(_strlen(var) + _strlen(valu) + 2);

	if (!buff)
	{
		return (1);
	}
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, valu);
	nod = inf->env;

	while (nod != NULL)
	{
		ptr = ostarts_wit(nod->str, var);
		if (ptr && *ptr == '=')
		{
			free(nod->str);
			nod->str = buff;
			inf->env_changed = 1;
			return (0);
		}
		nod = nod->next;
	}
	oadd_node_en(&(inf->env), buff, 0);
	free(buff);
	inf->env_changed = 1;
	return (0);
}
