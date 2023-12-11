#include "shell.h"

/**
 * strtow - divides a string into words,ignoring repeated delimiters
 * @str: Input string to be split
 * @del: Delimiter string used for splitting
 * Return: Pointer to an array of strings (words), or NULL on failure
 */
char **strtow(char *str, char *del)
{
	char **s;
	int i, j, col, mom, words_cur = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!ois_deli(str[i], del) && (ois_deli(str[i + 1], del) || !str[i + 1]))
			words_cur++;

	if (words_cur == 0)
		return (NULL);
	s = malloc((1 + words_cur) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < words_cur; j++)
	{
		while (ois_deli(str[i], del))
			i++;
		col = 0;
		while (!ois_deli(str[i + col], del) && str[i + col])
			col++;
		s[j] = malloc((col + 1) * sizeof(char));
		if (!s[j])
		{
			for (col = 0; col < j; col++)
				free(s[col]);
			free(s);
			return (NULL);
		}
		for (mom = 0; mom < col; mom++)
			s[j][mom] = str[i++];
		s[j][mom] = 0;
	}
	s[j] = NULL;
	return (s);
}
/**
 * strtow2 - separates a string into words
 * @str: Input string to be divided
 * @dul: Delimiter character used for splitting the string
 * Return: Pointer to an array of resulting strings
 */
char **strtow2(char *str, char dul)
{
	int i, j, col, m, words_cur = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != dul && str[i + 1] == dul) ||
		    (str[i] != dul && !str[i + 1]) || str[i + 1] == dul)
			words_cur++;
	if (words_cur == 0)
		return (NULL);
	s = malloc((1 + words_cur) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < words_cur; j++)
	{
		while (str[i] == dul && str[i] != dul)
			i++;
		col = 0;
		while (str[i + col] != dul && str[i + col] && str[i + col] != dul)
			col++;
		s[j] = malloc((col + 1) * sizeof(char));
		if (!s[j])
		{
			for (col = 0; col < j; col++)
				free(s[col]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < col; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
