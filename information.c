#include "shell.h"

/**
 * _clrinfo - initialize cmd_t struct
 * @info: struct address
 */


void _clrinfo(cmd_t *info)
{
	info->line = NULL;
	info->args = NULL;
	info->cmd = NULL;
	info->argn = 0;
}


void _setinf(cmd_t *info, char **av)
{
	int j = 0;

	info->file = av[0];
	if (info->line)
	{
		info->args = splits_string_words(info->line, " \t");
		if (!info->args)
		{
			info->args = malloc(sizeof(char *) * 2);
			if (info->args)
			{
				info->args[0] = dupl_func(info->line);
				info->args[1] = NULL;
			}
		}
		j = 0;
		while (info->args && info->args[j])
			j++;
		info->argn = j;
		rep_alia_(info);
		rep_var_(info);
	}
}

/**
 * _finf - frees cmd_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */

void _finf(cmd_t *info, int all)
{
	free_2d_array(info->args);
	info->args = NULL;
	info->cmd = NULL;
	switch (all)
	{
		case 1:
			if (!info->chain)
			{
				free(info->line);
			}
			if (info->envlist)
				free_table(&(info->envlist));
			if (info->histlist)
				free_table(&(info->histlist));
			if (info->aliaslist)
				free_table(&(info->aliaslist));
			free_2d_array(info->environ);
			info->environ = NULL;
			free_ptr((void **)info->chain);
			if (info->readfd > 2)
				close(info->readfd);
			_putchar_f(BUF_FLUSH);
			break;
		default:
			break;
	}
}
