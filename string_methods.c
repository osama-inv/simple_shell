#include "shell.h"

/**
 * _strlen - calculates the length
 * of a given string
 * @s: String to measure
 * Return: Length of the string as an integer
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
	{
		return (0);
	}

	while (*s++)
	{
		i++;
	}

	return (i);
}
/**
 * _strcat - appends the source
 * string to the destination string
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to the destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;
	return (ret);
}
/**
 * _strcmp - compares two strings lexicographically
 * @s1: The first string
 * @s2: The second string
 * Return: Negative if s1 < s2, positive
 * if s1 > s2, zero if s1 is equal to s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}

		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}

/**
 * ostarts_wit - if begins with the needle substring.
 * @getto: String to be searched.
 * @needle: Substring to locate.
 * Return: Pointer to the character.
 */
char *ostarts_wit(const char *getto, const char *needle)
{
	while (*needle)
		if (*needle++ != *getto++)
		{
			return (NULL);
		}
	return ((char *)getto);
}
