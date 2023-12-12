#include "shell.h"

/**
 * my_shell_ - main shell loop
 * @shell_info_: the parameter & return info struct
 * @arguments_: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int my_shell_(cmd_t *shell_info_, char **arguments_)
{
	ssize_t read_stat_ = 0;
	int builtin_ret_ = 0;

	while (read_stat_ != -1 && builtin_ret_ != -2)
	{
		_clrinfo(shell_info_);
		if (inter_active_mode(shell_info_))
			_puts_f("$ ");
		_eputchr(BUF_FLUSH);
		read_stat_ = _get_input(shell_info_);
		if (read_stat_ != -1)
		{
			_setinf(shell_info_, arguments_);
			builtin_ret_ = find_builtin_executed(shell_info_);
			if (builtin_ret_ == -1)
				find_comm(shell_info_);
		}
		else if (inter_active_mode(shell_info_))
			_putchar_f('\n');
		_finf(shell_info_, 0);
	}
	_write_hist_(shell_info_);
	_finf(shell_info_, 1);
	if (!inter_active_mode(shell_info_) && shell_info_->status_)
		exit(shell_info_->status_);
	if (builtin_ret_ == -2)
	{
		if (shell_info_->exitn == -1)
			exit(shell_info_->status_);
		exit(shell_info_->exitn);
	}
	return (builtin_ret_);
}

/**
 * find_builtin_executed - finds a builtin command
 * @shell_info_: the parameter & return info struct
 * Return: -1 if builtin not found,
 *0 if builtin executed successfully,
 *1 if builtin found but not successful,
 *-2 if builtin signals exit()
 */

int find_builtin_executed(cmd_t *shell_info_)
{
	int i_ = 0, builtin_ret_ = -1;
	command_table builtintbl[] = {
		{"exit", exit_shell_},
		{"envlist", display_environment_info_},
		{"help", show_help_},
		{"history", _myhistory_},
		{"setenv", configure_environment_},
		{"unsetenv", remove_environment_variable_},
		{"cd", change_directory_},
		{"alias", _myalias_},
		{NULL, NULL}
	};
	i_ = 0;
	while (builtintbl[i_].name)
	{
		if (string_cmp(shell_info->args[0], builtintbl[i_].name) == 0)
		{
			shell_info_->errn++;
			builtin_ret_ = builtintbl[i_].execute(shell_info_);
			break;
		}
		i_++;
	}
	return (builtin_ret_);
}

/**
 * find_command - finds a command in PATH
 * @shell_info_: the parameter & return info struct
 *
 * Return: void
 */

void find_command(cmd_t *shell_info_)
{
	char *cmd = NULL;
	int i_ = 0, k_ = 0;

	shell_info_->cmd = shell_info_->args[0];
	if (shell_info_->count == 1)
	{
		shell_info_->errn++;
		shell_info_->count = 0;
	}
	i_ = 0;
	while (shell_info_->line[i_])
	{
		if (!delimin_is_found(shell_info_->line[i_], " \t\n"))
			k_++;
		i_++;
	}
	if (!k_)
		return;

	cmd = fpath(shell_info_, find_environment_variable_(shell_info, "PATH="),
			shell_info_->args[0]);
	if (cmd)
	{
		shell_info_->cmd = cmd;
		fork_command(shell_info_);
	}
	else
	{
		if ((inter_active_mode(shell_info_) ||
					find_environment_variable_(shell_info, "PATH=")
			|| shell_info_->args[0][0] == '/') &&
				iscommand(shell_info_, shell_info_->args[0]))
			fork_command(shell_info_);
		else if (*(shell_info_->line) != '\n')
		{
			shell_info_->status_ = 127;
			display_error_(shell_info_, "not found\n");
		}
	}
}
/**
 * fork_command - forks a an exec thread to run cmd
 * @shell_info_: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(cmd_t *shell_info_)
{
	pid_t child_pid_;

	child_pid_ = fork();
	if (child_pid_ == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid_ == 0)
	{
		if (execve(shell_info_->cmd, shell_info_->args,
					retrieve_environment_(shell_info_)) == -1)
		{
			_finf(shell_info_, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shell_info_->status_));
		if (WIFEXITED(shell_info_->status_))
		{
			shell_info_->status_ = WEXITSTATUS(shell_info_->status_);
			if (shell_info_->status_ == 126)
				display_error_(shell_info_, "the Permission denied\n");
		}
	}
}
