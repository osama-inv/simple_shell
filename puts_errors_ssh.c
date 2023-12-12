#include "shell.h"

/**
 * o_eputcha - a function that writes the character ch to stderr
 *
 * @ch: is the character to be printed
 *
 * Return: On success 1,On error
 *	returrn -1 , and the err no is set appropriately
*/

int o_eputcha(char ch)
{
	static int i;
	static char buff[OWRITE_BUF_SIZ];

	if (i >= OWRITE_BUF_SIZ || ch == OBUF_FLUS)
	{
		write(2, buff, i);
		i = 0;
	}
	if (ch != OBUF_FLUS)
	{
		buff[i++] = ch;
	}
	return (1);
}

/**
 * o_eput - a function that prints an input string
 *
 * @strin: is the string that will be printed
 *
 * Return: void
*/

void o_eput(char *strin)
{
	int i;

	if (strin == NULL)
	{
		return;
	}
	for (i = 0; strin[i] != '\0'; i++)
	{
		o_eputcha(strin[i]);
	}
}

/**
 * o_putf - a function that writes the character ch to a given fdes
 *
 * @ch: is the character to be printed
 * @fdes: is the file descriptor that will be writen to
 *
 * Return: On success 1, On error return -1 ,
 *	and the err no is set appropriately
*/

int o_putf(char ch, int fdes)
{
	static int i;
	static char buff[OWRITE_BUF_SIZ];

	if (i >= OWRITE_BUF_SIZ || ch == OBUF_FLUS)
	{
		write(fdes, buff, i);
		i = 0;
	}
	if (ch != OBUF_FLUS)
	{
		buff[i++] = ch;
	}
	return (1);
}

/**
 * o_putsf - a function that prints an input string
 *
 * @strin: is the string to be printed
 * @fdes: is the file descriptor to be writen to
 *
 * Return: the number of put chars
*/

int o_putsf(char *strin, int fdes)
{
	int i = 0;

	if (strin == NULL)
	{
		return (0);
	}
	while (*strin)
	{
		i = i + o_putf(*strin++, fdes);
	}
	return (i);
}
