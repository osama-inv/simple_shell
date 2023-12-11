#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

/* OCONVERT_LOWERCAS and UNSIGNE */
#define OCONVERT_LOWERCAS	1
#define OCONVERT_UNSIGNE	2

#define OUSE_GETLIN 0
#define OREAD_BUF_SIZ 1024
#define OWRITE_BUF_SIZ 1024
#define OBUF_FLUS -1
#define OUSE_STRTO 0

/* dif vars */
#define OCMD_NOR	0
#define OCMD_O		1
#define OCMD_CHAI	3
#define OHIST_FIL	".simple_shell_history"
#define OHIST_MA	4096
#define OCMD_AN		2

extern char **environ;

/**
 * struct str_list - definition of a singly linked list
 * @num: Integer field in the node
 * @str: String field in the node
 * @next: Pointer to the next node in the list
 */
typedef struct str_list
{
	int num;
	char *str;
	struct str_list *next;
} list_t;
/**
 * struct infopass - structure to store pseudo-arguments
 * @arg: String obtained from getline containing arguments
 * @argv: Array of strings derived from arg
 * @path: String representing the path of the current command
 * @argc: Count of arguments
 * @line_count: Count of lines processed
 * @err_num: Error code for use in exit() scenarios
 * @linecount_flag: Flag
 * @fname: Filename of the program
 * @env: Linked list representing a local copy of the variables
 * @environ: Custom modified copy of linked list env
 * @history: Node representing command history
 * @alias: Node for storing aliases
 * @env_changed: Flag indicating if the environment was modified
 * @status: Return status of the last executed command
 * @cmd_buf: Address of the pointer
 * @cmd_buf_type: Type of command chaining (CMD_type, ||, &&, ;)
 * @readfd: File descriptor for reading line input
 * @histcount: Counter for history line numbers
 */
typedef struct infopass
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num; /* err_num */
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define OINFO_INI \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct built_in - represents a built-in command
 * @type: Flag identifying the built-in command
 * @func: Function to be executed for the built-in command
 */
typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* methods for string */
int _strlen(char *);
int _strcmp(char *, char *);
char *ostarts_wit(const char *, const char *);
char *_strcat(char *, char *);

/* methods for string */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
void ofree_lis(list_t **);
size_t olist_le(const list_t *);
int oreplace_alia(info_t *);
int oreplace_var(info_t *);
char **olist_to_string(list_t *);
size_t oprint_lis(const list_t *);
list_t *onode_starts_wit(list_t *, char *, char);
ssize_t oget_node_inde(list_t *, list_t *);

/* all_vs */
int ois_chai(info_t *, char *, size_t *);
void ocheck_chai(info_t *, char *, size_t *, size_t, size_t);
int _putchar(char);

/* the big lists */
list_t *oadd_nod(list_t **, const char *, int);
list_t *oadd_node_en(list_t **, const char *, int);
size_t oprint_list_st(const list_t *);
int odelete_node_at_inde(list_t **, unsigned int);
int oreplace_strin(char **, char *);

/* oexits  */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* the token */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* process_of_reallocation */
char *o_memse(char *, char, unsigned int);
void offre(char **);
void *o_reallo(void *, unsigned int, unsigned int);

/* through_shell */
int ohs(info_t *, char **);
int ofind_builti(info_t *);
char *o_geten(info_t *, const char *);
int o_myen(info_t *);
int o_myseten(info_t *);
int o_myunseten(info_t *);
int opopulate_env_lis(info_t *);
char **oget_enviro(info_t *);
int o_unseten(info_t *, char *);
int o_seten(info_t *, char *, char *);
char *oget_history_fil(info_t *info);
int owrite_histor(info_t *info);
void ofind_cm(info_t *);
void ofork_cm(info_t *);

/* get_it_parsed */
int ois_cm(info_t *, char *);
char *odup_char(char *, int, int);
char *ofind_pat(info_t *, char *, char *);
int oloophs(char **);

/* err */
void o_eput(char *);
int o_eputcha(char);
int o_putf(char c, int fd);
int o_putsf(char *str, int fd);

/* memoire */
int obfre(void **);
int ointeractiv(info_t *);
int ois_deli(char, char *);
int o_isalph(int);
int o_ato(char *);
int o_errato(char *);
void oprint_erro(info_t *, char *);
int oprint_(int, int);
char *oconvert_numbe(long int, int, int);
void oremove_comment(char *);

/* builtin */
int o_myexi(info_t *);
int o_myc(info_t *);
int o_myhel(info_t *);
void ofree_inf(info_t *, int);
int oread_histor(info_t *info);
int o_myhistor(info_t *);
int o_myalia(info_t *);

/* Have_aline.c */
ssize_t oget_inpu(info_t *);
int o_getlin(info_t *, char **, size_t *);
void osigintHandle(int);
void oclear_inf(info_t *);
void oset_inf(info_t *, char **);
int obuild_history_lis(info_t *info, char *buf, int linecount);
int orenumber_histor(info_t *info);

#endif
