#include "shell.h"
/**
 * o_myhel - provides help information for shell commands
 * @info: Struct encapsulating potential arguments, utilized for
 *        maintaining a consistent function prototype.
 *  Return: Always returns 0
 */
int o_myhel(info_t *info)
{
	char **this_ar;

	this_ar = info->argv; /* copy to this_ar */
	_puts("help call works. Function not yet implemented \n");
	if (0)
	{
		_puts(*this_ar);
	}
	return (0);
}
/**
 * o_myexi - function to terminate the shell
 * @info: Struct holding possible arguments, ensuring
 *        uniformity in function signature.
 *  Return: terminates and returns an exit code
 *           (0) if info.argv[0] is not "exit"
 */
int o_myexi(info_t *info)
{
	int getch; /* initiate getch */

	if (info->argv[1])
	{
		getch = o_errato(info->argv[1]);
		if (getch == -1)
		{
			info->status = 2;
			oprint_erro(info, "Illegal number: ");
			o_eput(info->argv[1]);
			o_eputcha('\n');
			return (1);
		}
		info->err_num = o_errato(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * o_myc - modifies the process's current working directory
 * @info: Struct that holds possible arguments, ensuring
 *        a consistent function signature.
 *  Return: Always returns 0
 */
int o_myc(info_t *info)
{
	char *s, *dir, buffer[1024];
	int dirchh;

	s = getcwd(buffer, 1024); /* get the cwd */
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = o_geten(info, "HOME=");
		if (!dir)
			dirchh = chdir((dir = o_geten(info, "PWD=")) ? dir : "/");
		else
			dirchh = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!o_geten(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n'); /* _putchar */
			return (1);
		}
		_puts(o_geten(info, "OLDPWD=")), _putchar('\n');
		dirchh = /* set dirchh */
			chdir((dir = o_geten(info, "OLDPWD=")) ? dir : "/");
	}
	else
	dirchh = chdir(info->argv[1]);
	if (dirchh == -1) /* dirchh == -1 */
	{
		oprint_erro(info, "can't cd to ");
		o_eput(info->argv[1]), o_eputcha('\n');
	}
	else
	{
		o_seten(info, "OLDPWD", o_geten(info, "PWD="));
		o_seten(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
