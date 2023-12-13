#include "shell.h"

/**
 * retrieve_environment_ - returns the string array copy of our environ
 * @information_: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

char **retrieve_environment_(cmd_t *information_)
{
	if (!information_->environ || information_->envmod)
	{
		information_->environ = _listtostrs(information_->envlist);
		information_->envmod = 0;
	}

	return (information_->environ);
}
/**
 * unset_environment_variable_ - Remove an environment variable
 * @information_: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @variable_: the string env var property
 */
int unset_environment_variable_(cmd_t *information_, char *variable_)
{
	list_t *current_node_ = information_->envlist;
	size_t index_ = 0;
	char *ptr_;

	if (!current_node_ || !variable_)
		return (0);
	while (current_node_)
	{
		ptr_ = string_start_with(current_node_->data_, variable_);
		if (ptr_ && *ptr_ == '=')
		{
			information_->envmod = remove_at_index(&(information_->env_), index_);
			index_ = 0;
			current_node_ = information_->envlist;
			continue;
		}
		current_node_ = current_node_->next_;
		index_++;
	}
	return (information_->envmod);
}
/**
 * set_environment_variable_ - Initialize a new environment variable,
 * or modify an existing one
 * @information_: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @variable_: the string env var property
 * @value_: the string env var value
 * Return: Always 0
 */
int set_environment_variable_(cmd_t *information_,
		char *variable_, char *value_)
{
	char *buffer_ = NULL;
	list_t *current_node_;
	char *ptr_;

	if (!variable_ || !value_)
		return (0);
	buffer_ = malloc_(string_length_(variable_) + string_length_(value_) + 2);
	if (!buffer_)
		return (1);
	copy_string(buffer_, variable_);
	compine_str(buffer_, "=");
	compine_str(buffer_, value_);
	current_node_ = information_->envlist;
	while (current_node_)
	{
		ptr_ = string_start_with(current_node_->data_, variable_);
		if (ptr_ && *ptr_ == '=')
		{
			free_(current_node_->data_);
			current_node_->data_ = buffer_;
			information_->envmod = 1;
			return (0);
		}
		current_node_ = current_node_->next_;
	}
	add_node_end_(&(information_->envlist), buffer_, 0);
	free_(buffer_);
	information_->envmod = 1;
	return (0);
}
