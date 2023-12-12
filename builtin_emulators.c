#include "shell.h"

/**
* exit_shell_ terminates the shell program
* @shell_info: a pointer to a structure that contains the arguments
* Return: returns -2 to indicate that the shell should exit
* returns 1 if the exit status is invalid
* returns 0 if the first argument is not "exit"
*/

int exit_shell_(cmd_t *shell_info_)
{
	int exit_check_;

	if (shell_info_->args[1])
	{
		exit_check_ = _erratoint(shell_info_->args[1]);
		if (exit_check_ == -1)
		{
			shell_info_->status_ = 2;
			display_error_(shell_info_, "Illegal number: ");
			_eputstr(shell_info_->args[1]);
			_eputchr('\n');
			return (1);
		}
		shell_info_->exitn = _erratoint(shell_info_->args[1]);
		return (-2);
	}
	shell_info_->exitn = -1;
	return (-2);
}

/**
* change_directory - switches the working directory of the shell
*/
int change_directory_(cmd_t *shell_info_)
{
	char *current_dir_, *home_dir_, buffer_[1024];
	int chdir_ret_;

	current_dir_ = getcwd(buffer_, 1024);
	if (!current_dir_)
		_puts_f("TODO: >>getcwd failure emsg here<<\n");
	if (!shell_info_->args[1])
	{
		home_dir_ = find_environment_variable_(shell_info_, "HOME=");
		if (!home_dir_)
			chdir_ret_ = chdir((home_dir_ = find_environment_variable_
						(shell_info_, "PWD=")) ? home_dir_ : "/");
		else
			chdir_ret_ = chdir(home_dir_);
	}
	else if (string_cmp(shell_info_->args[1], "-") == 0)
	{
		if (!find_environment_variable_(shell_info_, "OLDPWD="))
		{
			_puts_f(current_dir_);
			_putchar_f('\n');
			return (1);
		}
		_puts_f(find_environment_variable_(shell_info_, "OLDPWD=")),
			_putchar_f('\n');
		chdir_ret_ = chdir((home_dir_ = find_environment_variable_
					(shell_info_, "OLDPWD=")) ? home_dir_ : "/");
	}
	else
		chdir_ret_ = chdir(shell_info_->args[1]);
	if (chdir_ret_ == -1)
	{
		display_error_(shell_info_, "can't cd to ");
		_eputstr(shell_info_->args[1]), _eputchr('\n');
	}
	else
	{
		set_environment_variable_(shell_info_, "OLDPWD",
				find_environment_variable_(shell_info_, "PWD="));
		set_environment_variable_(shell_info_, "PWD", getcwd(buffer_, 1024));
	}
	return (0);
}
/**
* show_help - displays the usage information for the shell commands
* @shell_info: a pointer to a structure that contains the arguments
* Return: returns 0 if the help message is shown
*/

int show_help_(cmd_t *shell_info_)
{
	char **arg_array_;

	arg_array_ = shell_info_->args;
	_puts_f("help call works. Function not yet implemented \n");
	if (0)
		_puts_f(*arg_array_);
	return (0);
}
