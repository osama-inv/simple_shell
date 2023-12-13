#include "shell.h"

/**
 * olist_le - a function that determines the length of the linked list
 *
 * @head: is a pointer to first the node
 *
 * Return: the size of the linked list
*/

size_t olist_le(const list_t *head)
{
	size_t i;

	for (i = 0; head; i++)
	{
		head = head->next;
	}
	return (i);
}

/**
 * olist_to_string - a function that returns an array of strings
 *	of the (list->str)
 *
 * @head: is a pointer to the first node
 *
 * Return: an array of strings
*/

char **olist_to_string(list_t *head)
{
	list_t *nod = head;
	size_t i = olist_le(head), j = 0;
	char *str;
	char **str_n;

	if (!head || !i)
	{
		return (NULL);
	}
	str_n = malloc(sizeof(char *) * (i + 1));

	if (!str_n)
	{
		return (NULL);
	}
	for (i = 0; nod; nod = nod->next, i++)
	{
		str = malloc(_strlen(nod->str) + 1);
		if (!str)
		{
			while (j < i)
			{
				free(str_n[j]);
				j++;
			}
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, nod->str);
		str_n[i] = str;
	}
	str_n[i] = NULL;
	return (str_n);
}


/**
 * oprint_lis - a function that prints all rhe elements
 *	of the list_t linked list
 *
 * @head: pointer to first node
 *
 * Return: the size of the linked list
*/

size_t oprint_lis(const list_t *head)
{
	size_t i = 0;

	while (head != NULL)
	{
		_puts(oconvert_numbe(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * onode_starts_wit - a function that returns the node
 *	whose string starts with prefix
 *
 * @nod: is a pointer to the head list
 * @prefix: is a string to match with
 * @ch: the next character after prefix to match
 *
 * Return: the matched node or NULL
*/

list_t *onode_starts_wit(list_t *nod, char *prefix, char ch)
{
	char *ptr = NULL;

	while (nod != NULL)
	{
		ptr = ostarts_wit(nod->str, prefix);
		if (ptr && ((*ptr == ch) || (ch == -1)))
		{
			return (nod);
		}
		nod = nod->next;
	}
	return (NULL);
}

/**
 * oget_node_inde - a function that gets the index of a node
 *
 * @head: is a pointer to the list head
 * @nod: is a pointer to the node
 *
 * Return: the index of the node or return -1
*/

ssize_t oget_node_inde(list_t *head, list_t *nod)
{
	size_t n = 0;

	while (head != NULL)
	{
		if (head == nod)
		{
			return (n);
		}
		head = head->next;
		n++;
	}
	return (-1);
}
