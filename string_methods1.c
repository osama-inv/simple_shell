#include "shell.h"

/**
 * _strcpy - copies the source string
 * @dest: Destination buffer
 * @src: Source string
 * Return: Pointer to the destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
/**
 * _putchar - outputs the character
 * c to standard output
 * @c: Character to be written
 * Return: 1 on success,
 * -1 on error with errno set accordingly
 */
int _putchar(char ch)
{
	static int index;
	static char buffer[OWRITE_BUF_SIZ];

	if (ch == OBUF_FLUS || index >= OWRITE_BUF_SIZ)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (ch != OBUF_FLUS)
	{
		buffer[index++] = ch;
	}
	return (1);
}
/**
 * _strdup - creates a copy of the given string
 * @str: String to be duplicated
 * Return: Pointer to the newly duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *stil;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		len++;
	}
	stil = malloc(sizeof(char) * (len + 1));
	if (!stil)
	{
		return (NULL);
	}
	for (len++; len--;)
	{
		stil[len] = *--str;
	}
	return (stil);
}
/**
 * _puts - outputs a given
 * string to standard output
 * @str: String to be printed
 * Return: None (void function)
 */
void _puts(char *str)
{
	int index = 0;

	if (!str)
	{
		return;
	}
	while (str[index] != '\0')
	{
		_putchar(str[index]);
		index++;
	}
}
