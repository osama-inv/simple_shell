#include "shell.h"

/**
 * offre - free all
 * @poi: string of strings
 */
void offre(char **poi)
{
	char **get_p = poi;

	if (!poi)
	{
		return;
	}

	while (*poi)
	{
		free(*poi++);
	}
	free(get_p);
}
/**
 * o_memse - populates a memory area with a specific byte
 * @esta: Pointer to the memory block to be filled
 * @getb: Byte value used for filling
 * @n: Number of bytes to fill in the memory block
 * Return: A pointer to the memory area 'esta'
 */
char *o_memse(char *esta, char getb, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		esta[index] = getb;
	return (esta);
}
/**
 * o_reallo - resizes a previously allocated memory block
 * @ptr: Pointer to the previously allocated memory block
 * @rid_size: Size in bytes of the previous memory block
 * @nouveau_size: Size in bytes of the new memory block
 * Return: Pointer to the newly allocated memory block
 */
void *o_reallo(void *ptr, unsigned int rid_size, unsigned int nouveau_size)
{
	char *pointer;

	if (!ptr) /* check empty*/
	{
		return (malloc(nouveau_size));
	}
	if (!nouveau_size)
	{
		return (free(ptr), NULL);
	}
	if (nouveau_size == rid_size) /* equal? */
	{
		return (ptr);
	}
	pointer = malloc(nouveau_size);
	if (!pointer)
	{
		return (NULL);
	}

	rid_size = rid_size < nouveau_size ? rid_size : nouveau_size;
	while (rid_size--)
	{
		pointer[rid_size] = ((char *)ptr)[rid_size];
	}
	free(ptr);
	return (pointer);
}
