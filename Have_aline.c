#include "shell.h"
/**
 * oinput_bu - buffers a sequence of commands
 * @info: Struct for passing parameters
 * @buffer: Pointer to the buffer's address
 * @long_of: Pointer to the variable storing the length
 * Return: Number of bytes read
 */
ssize_t oinput_bu(info_t *info, char **buffer, size_t *long_of)
{
	ssize_t imr = 0;
	size_t savep = 0;

	if (!*long_of)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, osigintHandle);
#if OUSE_GETLIN
		imr = getline(buffer, &savep, stdin);
#else
		imr = o_getlin(info, buffer, &savep);
#endif
		if (imr > 0)
		{
			if ((*buffer)[imr - 1] == '\n')
			{
				(*buffer)[imr - 1] = '\0';
				imr--;
			}
			info->linecount_flag = 1; /* check info */
			oremove_comment(*buffer);
			obuild_history_lis(info, *buffer, info->histcount++);
			{
				*long_of = imr;
				info->cmd_buf = buffer;
			}
		}
	}
	return (imr);
}
/**
 * osigintHandle - blocks ctrl-C
 * @sig_num: the  number
 * Return: void
 */
void osigintHandle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(OBUF_FLUS);
}
/**
 * oget_inpu - deal with input
 * @info: info struct
 *
 * Return: num of b
 */
ssize_t oget_inpu(info_t *info)
{
	static char *buffer;
	char **w_buff = &(info->arg), *p;
	static size_t i, j, long_of;
	ssize_t imr = 0; /* see imr */

	_putchar(OBUF_FLUS);
	imr = oinput_bu(info, &buffer, &long_of);
	if (imr == -1)
		return (-1);
	if (long_of)
	{
		j = i; /* i and j */
		p = buffer + i;
		ocheck_chai(info, buffer, &j, i, long_of);
	for (; j < long_of; j++) /* goal is long_of */
	{
		if (ois_chai(info, buffer, &j))
			break;
	}
	i = j + 1;
	if (i >= long_of)
	{
		i = long_of = 0; /* check right */
		info->cmd_buf_type = OCMD_NOR;
	} /* return len of THIS command */
		*w_buff = p;
		return (_strlen(p));
	}
	*w_buff = buffer;
	return (imr);
}
/**
 * oread_bu - the buffer
 * @info: p for struct
 * @buffer: buffer
 * @i: size
 * Return: imr
 */
ssize_t oread_bu(info_t *info, char *buffer, size_t *i)
{
	ssize_t imr = 0;

	if (*i)
	{
		return (0);
	}
	imr = read(info->readfd, buffer, OREAD_BUF_SIZ);
	if (imr >= 0)
	{
		*i = imr;
	}
	return (imr);
}
/**
 * o_getlin - retrieves the next line of input from standard input (STDIN)
 * @info: Struct containing function parameters
 * @ptr: Address of the buffer pointer, either preallocated or NULL
 * @length: Size of the preallocated buffer pointed by ptr, if not NULL
 * Return: A string containing the input line
 */
int o_getlin(info_t *info, char **ptr, size_t *length)
{
	char *p = NULL, *Nouveau_p = NULL, *Kal;
	static char buffer[OREAD_BUF_SIZ];
	static size_t i, long_of;
	ssize_t imr = 0, s = 0;
	size_t Cay;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == long_of)
		i = long_of = 0;

	imr = oread_bu(info, buffer, &long_of);
	if (imr == -1 || (imr == 0 && long_of == 0))
		return (-1);

	Kal = _strchr(buffer + i, '\n');
	Cay = Kal ? 1 + (unsigned int)(Kal - buffer) : long_of;
	Nouveau_p = o_reallo(p, s, s ? s + Cay : Cay + 1);
	if (!Nouveau_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(Nouveau_p, buffer + i, Cay - i);
	else
		_strncpy(Nouveau_p, buffer + i, Cay - i + 1);

	s += Cay - i;
	i = Cay;
	p = Nouveau_p;
	if (length)
	{
		*length = s;
	}
	*ptr = p;
	return (s);
}
