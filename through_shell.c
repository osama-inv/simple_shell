#include "shell.h"

/**
 * ohs - the primary loop for the shell execution
 * @info: Struct containing parameters and return information
 * @inva: Argument vector passed from main()
 * Return: 0 for successful execution,
 * 1 for errors, or other specific error codes
 */
int ohs(info_t *info, char **inva)
{
	ssize_t ku = 0;
	int origin = 0;

	while (ku != -1 && origin != -2)
	{
		oclear_inf(info);
		if (ointeractiv(info))
			_puts("$ ");
		o_eputcha(OBUF_FLUS);
		ku = oget_inpu(info);
		if (ku != -1)
		{
			oset_inf(info, inva);
			origin = ofind_builti(info);
			if (origin == -1)
				ofind_cm(info);
		}
		else if (ointeractiv(info))
			_putchar('\n');
		ofree_inf(info, 0);
	}
	owrite_histor(info);
	ofree_inf(info, 1);
	if (!ointeractiv(info) && info->status)
		exit(info->status);
	if (origin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (origin);
}
/**
 * ofork_cm - creates a fork and executes
 * a command in a new thread
 * @info: Struct containing parameters
 * Return: None (void function)
 */
void ofork_cm(info_t *info)
{
	pid_t enfant;

	enfant = fork(); /* get the fork */
	if (enfant == -1)
	{
		perror("Error:");
		return;
	}
	if (enfant == 0)
	{
		if (execve(info->path, info->argv, oget_enviro(info)) == -1)
		{
			ofree_inf(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else /* didn't work? */
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				oprint_erro(info, "Permission denied\n");
		}
	}
}
/**
 * ofind_builti - identifies and executes command
 * @info: Struct containing parameters
 * Return: -1 if command is not found,
 *  0 if builtin command is executed successfully,
 *  1 if builtin command is found but execution is not,
 *  -2 if  builtin command triggers an exit()
 */
int ofind_builti(info_t *info)
{
	int index, thebultin = -1;
	builtin_table builtintbl[] = {
		{"exit", o_myexi},
		{"env", o_myen},
		{"help", o_myhel},
		{"history", o_myhistor},
		{"setenv", o_myseten},
		{"unsetenv", o_myunseten},
		{"cd", o_myc},
		{"alias", o_myalia},
		{NULL, NULL}
	};
	for (index = 0; builtintbl[index].type; index++)
		if (_strcmp(info->argv[0], builtintbl[index].type) == 0)
		{
			info->line_count++;
			thebultin = builtintbl[index].func(info);
			break;
		}
	return (thebultin);
}
/**
 * ofind_cm - locates a specified
 * command within the system PATH
 * @info: Struct that holds parameters
 * Return: None (void function)
 */
void ofind_cm(info_t *info)
{
	int i, coll;
	char *the_p = NULL; /* begin with null */

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, coll = 0; info->arg[i]; i++)
		if (!ois_deli(info->arg[i], " \t\n"))
			coll++;
	if (!coll)
		return; /* return it */
	the_p = ofind_pat(info, o_geten(info, "PATH="), info->argv[0]);
	if (the_p)
	{
		info->path = the_p;
		ofork_cm(info);
	}
	else
	{
		if ((ointeractiv(info) || o_geten(info, "PATH=")
			|| info->argv[0][0] == '/') && ois_cm(info, info->argv[0]))
			ofork_cm(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			oprint_erro(info, "not found\n");
		}
	}
}
