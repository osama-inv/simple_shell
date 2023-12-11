#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { OINFO_INI };
	int stwo = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (stwo)
		: "r" (stwo));

	if (ac == 2)
	{
		stwo = open(av[1], O_RDONLY);
		if (stwo == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				o_eput(av[0]);
				o_eput(": 0: Can't open ");
				o_eput(av[1]);
				o_eputcha('\n');
				o_eputcha(OBUF_FLUS);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = stwo;
	}
	opopulate_env_lis(info);
	oread_histor(info);
	ohs(info, av);
	return (EXIT_SUCCESS);
}
