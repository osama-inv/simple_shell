#include "shell.h"

/**
 * o_errato - a function that converts a string into an integer
 *
 * @strin: is the string that will be converted
 *
 * Return: if no numbers in the string return 0,
 *	-1 on error, otherwise converted number
*/

int o_errato(char *strin)
{
	int i = 0;
	unsigned long int res = 0;

	if (*strin == '+')
	{
		strin++;
	}
	while (strin[i] != '\0')
	{
		if (strin[i] >= '0' && strin[i] <= '9')
		{
			res = res * 10;
			res = res + (strin[i] - '0');
			if (res > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
		i++;
	}
	return (res);
}

/**
 * oprint_ - a function that prints a decimal number (base 10)
 *
 * @input: is the input
 * @fdess: is the file descriptor to be written to
 *
 * Return: number of characters printed
*/

int oprint_(int input, int fdess)
{
	int (*__putchar)(char) = _putchar;
	int n, count = 0;
	unsigned int n_abs, curr;

	if (fdess == STDERR_FILENO)
	{
		__putchar = o_eputcha;
	}
	if (input < 0)
	{
		n_abs = -input;
		__putchar('-');
		count++;
	}
	else
	{
		n_abs = input;
	}
	curr = n_abs;

	for (n = 1000000000; n > 1; n = n / 10)
	{
		if (n_abs / i)
		{
			__putchar('0' + curr / n);
			count++;
		}
		curr = curr % n;
	}
	__putchar('0' + curr);
	count++;
	return (count);
}

/**
 * oprint_erro - a function that prints error message
 *
 * @inf: is the parameter and it returns information struct
 * @strerr: is a string that contains specified error type
 *
 * Return: if no numbers in string return 0,
 *	converted number otherwise -1 on error
*/

void oprint_erro(info_t *inf, char *strerr)
{
	o_eput(inf->fname);
	o_eput(": ");
	oprint_(inf->line_count, STDERR_FILENO);
	o_eput(": ");
	o_eput(inf->argv[0]);
	o_eput(": ");
	o_eput(strerr);
}

/**
 * oconvert_numbe - is a conversion function that serves as a clone of itoa
 *
 * @n: is a number
 * @base: is the base of the argument
 * @flags: is the flags of the argument
 *
 * Return: a string
*/

char *oconvert_numbe(long int n, int base, int flags)
{
	static char *ary;
	static char buff[50];
	unsigned long num = n;
	char mark = 0;
	char *ptr;

	if (!(flags & OCONVERT_UNSIGNE) && n < 0)
	{
		num = -n;
		mark = '-';

	}
	ary = flags & OCONVERT_LOWERCAS ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	do	{
		*--ptr = arry[num % base];
		num = num / base;
	} while (num != 0);

	if (mark)
	{
		*--ptr = mark;
	}
	return (ptr);
}

/**
 * oremove_comment - a function that replaces first instance of '#' with '\0'
 *
 * @buff: is the address of the string to be modified
 *
 * Return: Always 0 (Success)
*/

void oremove_comment(char *buff)
{
	int i = 0;

	while (buff[i] != '\0')
	{
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
		i++;
	}
}
