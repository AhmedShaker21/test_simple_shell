#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORMAL	                0
#define COMMAND_CONDITIONAL_OR		1
#define COMMAND_CONDITIONAL_AND	    2
#define COMMAND_CHAINING	        3

/* for convert_number() */
#define LOWER_CASE_FLAG	1
#define UNSIGNED_FLAG	2

/* 1 if using system getline() */
#define ENABLE_GETLINE 0

#define HIST_FILENAME	".simple_shell_history"
#define MAX_HIST_SIZE	4096

extern char **environ;
/**
*struct custom_node - a linked list of strings
*@value: an integer value associated with the string
*@data: a pointer to a null-terminated string
*@next: a pointer to the next node in the list
*/
typedef struct custom_node
{
	int value;
	char *data;
	struct custom_node *next;
} custom_t;

/**
*struct cmdinfo - contains information to pass into a function,
*allowing uniform prototype for function pointer struct
*@line: a string obtained from getline containing arguments
*@args: an array of strings parsed from line
*@cmd: a string command for the current execution
*@argn: the number of arguments
*@errn: the error number
*@exitn: the exit code for exit()s
*@count: a flag to indicate if this line of input should be counted
*@file: the program filename
*@envlist: linked list local copy of environ
*@envp: custom modified copy of environ from LL envlist
*@histlist: the history node
*@aliaslist: the alias node
*@envmod: a flag to indicate if environ was modified
*@status: the return status of the last executed command
*@chain: address of pointer to chain, on if chaining
*@chaintype: CMD_type ||, &&, ;
*@readfd: the file descriptor from which to read line input
*@histn: the history line number count
*/

typedef struct cmdinfo
{
	char *line;
	char **args;
	char *cmd;
	int argn;
	unsigned int errn;
	int exitn;
	int count;
	char *file;
	custom_t *envlist;
	custom_t *histlist;
	custom_t *aliaslist;
	char **environ;
	int envmod;
	int status_;
	char **chain;
	int chaintype;
	int readfd;
	int histn;
} cmd_t;

#define INFO_DATA \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

typedef struct command
{
	char *name;
	int (*execute)(cmd_t *);
} command_table;

/* builtin_emulators.c */
int exit_shell_(cmd_t *shell_info_);
int change_directory_(cmd_t *shell_info_);
int show_help_(cmd_t *shell_info_);

/*  builtin_emulators2.c */
int convert_string_to_int_(char *str_);
int _myalias_(cmd_t *shell_info_);

/* err_string_functions.c */
void _eputstr(char *);
int _eputchr(char);
int _putiofd(char char_input, int filede_scriptor);
int _putstrfd(char *string_fd, int filede_scriptor);

/* path.c */
char *fpath(cmd_t *shell_info, char *pstr, char *cmd);
char *_dupchar(char *pstr, int start, int end);
int _iscmd_(cmd_t *shell_info, char *path);

/* file_io_functions.c */
char *_get_history_(cmd_t *shell_info);
int read_hist(cmd_t *shell_info);
int _write_hist_(cmd_t *shell_info);
int renumber_hist_(cmd_t *shell_info);
int _build_hist_(cmd_t *shell_info, char *buffer, int line_c);

/* getline.c module */
void sigint_Hand(__attribute__((unused))int sinum);
ssize_t _get_input(cmd_t *shell_info);
int get_line_(cmd_t *info, char **ptr, size_t *length);

/* chain.c */
int is_chain_(cmd_t *info_, char *buf_, size_t *p_);
void check_chain_(cmd_t *info_, char *buf_,
		size_t *p_, size_t i_, size_t len_);
int replace_alias_(cmd_t *info_);
int replace_vars_(cmd_t *info_);
int replace_string_(char **old_, char *new_);

/* my_shell_ */
int my_shell_(cmd_t *, char **);
int find_builtin_executed(cmd_t *);
void find_comm(cmd_t *);
void fork_command(cmd_t *);

/* path.c */
int iscommand(cmd_t *, char *);
char _dupchar(char *, int, int);
char *fpath(info_t *, char *, char *);


/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputstr(char *);
int _eputchr(char);
int _putiofd(char c, int fd);
int _putstrfd(char *str, int fd);

/* string_functions.c */
int string_length(char *);
int string_cmp(char *, char *);
char *string_start_with(const char *, const char *);
char *compine_str(char *, char *);

/* string_functions2.c */
char *copy_string(char *, char *);
char *dupl_func(const char *);
void _puts_f(char *);
int _putchar_f(char);

/* string_functions3.c */
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/* string_functions4.c */
char **splits_string_words(char *, char *);
char **splits_string_words2(char *, char);

/* memory_functions */
char *fill_memory(char *, char, unsigned int);
void free_2d_array(char **);
void *resize_memory(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int free_ptr(void **);

/* more_functions.c */
int inter_active_mode(info_t *);
int delimin_is_found(char, char *);
int check_alpha(int);
int atoi_func(char *);

#endif
