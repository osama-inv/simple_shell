#include "shell.h"

/**
 * _strncpy - a function that copies a string
 *
 * @dest: is the destination string to be copied to
 * @src: is the source string
 * @amnt: the amount of characters to be copied
 *
 * Return: the concatenated string of the copied amount
 *	with the source string
*/

char *_strncpy(char *dest, char *src, int amnt)
{
	int i, j;
	char *str = dest;

	for (i = 0; src[i] != '\0' && i < amnt - 1; i++)
	{
		dest[i] = src[i];
	}
	if (i < amnt)
	{
		for (j = i; j < amnt; j++)
		{
			dest[j] = '\0';
		}
	}
	return (str);
}

/**
 * _strncat - a function that concatenates two strings
 *
 * @dest: is the name of the first string
 * @src: is the name of the second string
 * @amnt: is the amount of bytes that will be maximally used
 *
 * Return: the resulted concatenated string
*/
char *_strncat(char *dest, char *src, int amnt)
{
	int i, j = 0;
	char *str = dest;

	for (i = 0; dest[i] != '\0'; i++)
		;
	while (src[j] != '\0' && j < amnt)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < amnt)
	{
		dest[i] = '\0';
	}
	return (str);
}

/**
 * _strchr - a function that locates a character in a string
 *
 * @strin: is the string that will be parsed
 * @ch: is the character to look for
 *
 * Return: a pointer to the memory area strin
*/

char *_strchr(char *strin, char ch)
{
	do {
		if (*strin == ch)
		{
			return (strin);
		}
	} while (*strin++ != '\0');

	return (NULL);
}
