#include "shell.h"

/**
 * obfre - deallocates memory and
 * resets the pointer to NULL
 * @pointer: Address of the pointer to be freed
 * Return: 1 on successful memory
 * deallocation, 0 otherwise
 */
int obfre(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
