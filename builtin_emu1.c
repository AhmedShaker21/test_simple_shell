#include "shell.h"

/**
 * exit_shell_ - terminates the shell program
 * @shell_info_: a pointer to a structure that contains the arguments
 *
 * Description: This function checks if the first argument is "exit" and
 * returns -2 to indicate that the shell should exit. If the second argument
 * is present, it validates it as a valid exit status and sets the exitn
 * field of the shell_info_ structure accordingly. If the exit status is
 * invalid, it displays an error message and returns 1.
 *
 * Return: returns -2 if the shell should exit, 1 if the exit status is invalid,
 * or 0 if the first argument is not "exit"
 */
int exit_shell_(cmd_t *shell_info_)
{
	int exit_check_;

	if (shell_info_->args[1])
	{
		exit_check_ = erratoint(shell_info->args[1]);
		if (exit_check_ == -1)
		{
			shell_info_->status_ = 2;
			display_error_(shell_info_, "Illegal number: ");
			eputstr(shell_info->args[1]);
			_eputchr('\n');
			return (1);
		}
		shell_info_->exitn = erratoint(shell_info->args[1]);
		return (-2);
	}
	shell_info_->exitn = -1;
	return (-2);
}

/**
 * change_directory_ - switches the working directory of the shell
 * @shell_info_: a pointer to a structure that contains the arguments
 *
 * Description: This function changes the current working directory of the
 * shell based on the first argument. If no argument is given, it changes
 * to the home directory. If the argument is "-", it changes to the previous
 * working directory. It also updates the environment variables PWD and OLDPWD
 * accordingly. If the argument is invalid, it displays an error message and
 * returns 1.
 *
 * Return: returns 0 on success, or 1 on failure
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
			puts_f(current_dir);
			_putchar_f('\n');
			return (1);
		}
		puts_f(find_environment_variable(shell_info_, "OLDPWD=")),
			_putchar_f('\n');
		chdir_ret_ = chdir((home_dir_ = find_environment_variable_
					(shell_info_, "OLDPWD=")) ? home_dir_ : "/");
	}
	else
		chdir_ret_ = chdir(shell_info_->args[1]);
	if (chdir_ret_ == -1)
	{
		display_error_(shell_info_, "can't cd to ");
		eputstr(shell_info->args[1]), _eputchr('\n');
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
 * show_help_ - displays the usage information for the shell commands
 * @shell_info_: a pointer to a structure that contains the arguments
 *
 * Description: This function prints the help message for the shell commands
 * based on the first argument. If no argument is given, it prints the general
 * help message. If the argument is not a valid shell command, it prints an
 * error message and returns 1.
 *
 * Return: returns 0 on success, or 1 on failure
 */
int show_help_(cmd_t *shell_info_)
{
	char **arg_array_;

	arg_array_ = shell_info_->args;
	_puts_f("help call works. Function not yet implemented \n");
	if (0)
		puts_f(*arg_array);
	return (0);
}
