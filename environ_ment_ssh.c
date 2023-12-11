#include "shell.h"

/**
 * o_myen - a function that prints the current environment
 *
 * @inf: Structure containing potential arguments,
 *	that is used to maintain constant function prototype
 *
 * Return: Always 0 (Success)
*/

int o_myen(info_t *inf)
{
	oprint_list_st(inf->env);
	return (0);
}

/**
 * o_geten - a function that gets the value of an environ variable
 *
 * @inf: is a structure that contains potential arguments,
 *	that is used to maintain constant function prototype
 * @nam: is the variable name of env
 *
 * Return: the value of the environ variable
*/

char *o_geten(info_t *inf, const char *nam)
{
	list_t *node = inf->env;
	char *ptr;

	while (node != NULL)
	{
		ptr = ostarts_wit(node->str, nam);
		if (ptr && *ptr)
		{
			return (ptr);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * o_myseten - a function that Initializes a new environment variable,
 *	or modifies an existing one
 * @inf: is a structure that contains potential arguments,
 *	that is used to maintain constant function prototype
 *
 * Return: Always 0 (Success)
*/

int o_myseten(info_t *inf)
{
	if (inf->argc != 3)
	{
		o_eput("Incorrect number of arguements\n");
		return (1);
	}
	if (o_seten(inf, inf->argv[1], inf->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * o_myunseten - a function that removes an environment variable
 *
 * @inf: is a structure that contains potential arguments,
 *	that is used to maintain constant function prototype
 *
 * Return: Always 0 (Success)
*/

int o_myunseten(info_t *inf)
{
	int i = 1;

	if (inf->argc == 1)
	{
		o_eput("Too few arguements.\n");
		return (1);
	}
	while (i <= inf->argc)
	{
		o_unseten(inf, inf->argv[i]);
		i++;
	}
	return (0);
}

/**
 * opopulate_env_lis - a function that populates
 *	environment linked list
 *
 * @inf: is a structure that contains potential arguments,
 *	that is used to maintain constant function prototype
 *
 * Return: Always 0 (Success)
*/

int opopulate_env_lis(info_t *inf)
{
	list_t *node = NULL;
	size_t i = 0;

	while (environ[i])
	{
		oadd_node_en(&node, environ[i], 0);
		i++;
	}
	inf->env = node;
	return (0);
}
