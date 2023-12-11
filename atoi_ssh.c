#include "shell.h"

/**
 * ointeractiv - a function that returns true if shell is interactive mode
 *
 * @inf: is the address of the struct
 *
 * Return: 1 if interactive mode, Otherwise return 0
*/

int ointeractiv(info_t *inf)
{
	return (inf->readfd <= 2 && isatty(STDIN_FILENO));
}

/**
 * ois_deli - a function that checks if character is a delimiter
 *
 * @ch: is the char to be checked
 * @deli: is a delimiter string
 *
 * Return: if true return 1, 0 when false
*/

int ois_deli(char ch, char *deli)
{
	while (*deli)
	{
		if (*deli++ == ch)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * o_isalph - a function that checks for alphabetic character
 *
 * @ch: is the character to input
 *
 * Return: 1 if c is alphabetic, otherwise return 0
*/

int o_isalph(int ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * o_ato - a function that converts a string to an integer
 *
 * @str: is the string that will be converted
 *
 * Return: if no numbers in string return 0,
 *	otherwise return a converted number
*/

int o_ato(char *str)
{
	int n, mark = 1, flag_n = 0, prod;
	unsigned int res = 0;

	for (n = 0;  str[n] != '\0' && flag_n != 2; n++)
	{
		if (str[n] == '-')
		{
			mark = mark * -1;
		}
		if (str[n] <= '9' && str[n] >= '0')
		{
			flag_n = 1;
			res = res * 10;
			res = res + (str[n] - '0');
		}
		else if (flag_n == 1)
		{
			flag_n = 2;
		}
	}
	if (mark == -1)
	{
		prod = -res;
	}
	else
	{
		prod = res;
	}
	return (prod);
}
