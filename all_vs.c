#include "shell.h"

/**
 * ois_chai - checks if the current character in the buffer
 * @info: Struct containing function parameters
 * @buffer: Character buffer
 * @p: Address of the current position in the buffer
 * Return: 1 if it is a chain delimiter, 0 otherwise
 */
int ois_chai(info_t *info, char *buffer, size_t *p)
{
	size_t num_j = *p;

	if (buffer[num_j] == '|' && buffer[num_j + 1] == '|')
	{ /* check */
		buffer[num_j] = 0;
		num_j++;
		info->cmd_buf_type = OCMD_O;
	}
	else if (buffer[num_j] == '&' && buffer[num_j + 1] == '&')
	{
		buffer[num_j] = 0;
		num_j++;
		info->cmd_buf_type = OCMD_AN;
	}
	else if (buffer[num_j] == ';')
	{
		buffer[num_j] = 0;
		info->cmd_buf_type = OCMD_CHAI;
	}
	else
	{
		return (0);
	}
	*p = num_j;
	return (1);
}
/**
 * oreplace_string - replaces an existing string
 * with a new one
 * @old: Address of the original string
 * @nouveau: New string to replace with
 * Return: 1 if replacement is successful, 0 otherwise
 */
int oreplace_strin(char **old, char *nouveau)
{
	free(*old);
	*old = nouveau;
	return (1);
}
/**
 * ocheck_chai - determines whether to continue chaining
 * @info: Struct containing function parameters
 * @buf: Character buffer
 * @p: Address of the current position in the buffer
 * @i: Starting position in the buffer
 * @len: Length of the buffer
 *
 * Return: None (void function)
 */
void ocheck_chai(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t nre_j = *p;

	if (info->cmd_buf_type == OCMD_AN)
	{
		if (info->status)
		{
			buf[i] = 0;
			nre_j = len;
		}
	}
	if (info->cmd_buf_type == OCMD_O)
	{
		if (!info->status)
		{
			buf[i] = 0;
			nre_j = len;
		}
	}
	*p = nre_j;
}
/**
 * oreplace_alia - substitutes aliases
 * @info: Struct containing function parameters
 * Return: 1 if an alias is replaced, 0 otherwise
 */
int oreplace_alia(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = onode_starts_wit(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
		{
			return (0);
		}
		ptr = _strdup(ptr + 1);
		if (!ptr)
		{
			return (0);
		}
		info->argv[0] = ptr;
	}
	return (1);
}
/**
 * oreplace_var - substitutes variables
 * @info: Struct containing function parameters
 * Return: 1 if a variable is replaced, 0 otherwise
 */
int oreplace_var(info_t *info)
{
	int index = 0;
	list_t *node;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
		{
			continue;
		}
		if (!_strcmp(info->argv[index], "$?"))
		{
			oreplace_strin(&(info->argv[index]),
				_strdup(oconvert_numbe(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[index], "$$"))
		{
			oreplace_strin(&(info->argv[index]),
				_strdup(oconvert_numbe(getpid(), 10, 0)));
			continue;
		}
		node = onode_starts_wit(info->env, &info->argv[index][1], '=');
		if (node)
		{
			oreplace_strin(&(info->argv[index]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		oreplace_strin(&info->argv[index], _strdup(""));

	}
	return (0);
}
