#include "shell.h"

/**
 * display_environment_info_ - prints the current environment
 * @information_: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int display_environment_info_(cmd_t *information_)
{
	printl_string(information_->envlist);
	return (0);
}
/**
 * find_environment_variable_ - gets the value of an environ variable
 * @information_: Structure containing potential arguments. Used to maintain
 * @variable_name_: env var name
 *
 * Return: the value
 */
char *find_environment_variable_(cmd_t *information_,
		const char *variable_name_)
{
	custom_t *current_node_ = information_->envlist;
	char *result_;

	while (current_node_)
	{
		result_ = string_start_with(current_node_->data, variable_name_);
		if (result_ && *result_)
			return (result_);
		current_node_ = current_node_->next_;
	}
	return (NULL);
}
/**
 * configure_environment_  Initialize a new environment variable,
 *             or modify an existing one
 * @information_: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int configure_environment_(cmd_t *information_)
{
	if (information_->argn != 3)
	{
		_eputstr("Incorrect number of arguments\n");
		return (1);
	}
	if (set_environment_variable_(information_, information_->args[1],
				information_->args[2]))
		return (0);
	return (1);
}
/**
 * remove_environment_variable_ - Remove an environment variable
 * @information_: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int remove_environment_variable_(cmd_t *information_)
{
	int index_;

	if (information_->argn == 1)
	{
		_eputstr("Too few arguments.\n");
		return (1);
	}
	for (index_ = 1; index_ <= information_->argn; index_++)
		unset_environment_variable_
			(information_, information_->args[index_]);
	return (0);
}
/**
 * populate_environment_list_ - populates env linked list
 * @information_: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populate_environment_list_(cmd_t *information_)
{
	custom_t *current_node_ = NULL;
	size_t index_;

	while (environ[index_])
	{
		append_node(&current_node_, environ[index_], 0);
		index_++;
	}
	information_->envlist = current_node_;
	return (0);
}
