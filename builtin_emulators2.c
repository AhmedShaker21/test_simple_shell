#include "shell.h"

/**
* _myhistory - prints the history list, showing each command on a new line.
* @shell_info: a pointer to a structure that contains the arguments.
* Return: returns 0 if the history list is printed successfully
*/
int _myhistory_(cmd_t *shell_info_)
{
	print_list_f(shell_info_->histlist);
	return (0);
}

/**
* unset_alias_ removes an alias from the alias list
* @shell_info: a pointer to a structure that contains the arguments
* @data: a string that contains the alias name and value
* Return: returns 0 if the alias is successfully removed
*/
int unset_alias_(cmd_t *shell_info_, char *data)
{
	char *print_alia_, setC_;
	int return_;

	print_alia_ = custom_strchr(data, '=');
	if (!print_alia_)
		return (1);
	setC_ = *print_alia_;
	*print_alia_ = 0;
	(return_) = remove_at_index(&(shell_info_->aliaslist),
			_getnodei(shell_info_->aliaslist,
				search_node_by_prefix(shell_info_->aliaslist_, data, -1)));
	*print_alia_ = setC_;
	return (return_);
}

/**
 * set_alias_ assigns a value to an alias or deletes it if the value is empty
 * @shell_info: a pointer to a structure that contains the arguments
 * @data: a string that contains the alias name and value
 * Return: returns 0 if the alias is successfully set or unset.
 */

int set_alias_(cmd_t *shell_info_, char *data)
{
	char *print_alia_;

	print_alia_ = custom_strchr(data, '=');
	if (!print_alia_)
		return (1);
	if (!*++print_alia_)
		return (unset_alias_(shell_info_, data));
	unset_alias_(shell_info_, data);
	return (append_node(&(shell_info_->aliaslist), data, 0) == NULL);
}

/**
*print_alia - displays an alias name and value
*@node: a pointer to a node that contains the alias string
*Return: returns 0 if the alias is printed successfully.
*/
int print_alias_(custom_t *node_)
{
	char *print_alia_ = NULL, *alia_ = NULL;

	if (node_)
	{
		print_alia_ = custom_strchr(node_->data, '=');
		for (alia_ = node_->data; alia_ <= print_alia_; alia_++)
			_putchar_f(*alia_);
		_putchar_f('\'');
		_puts_f(print_alia_ + 1);
		_puts_f("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias_ mimics the alias builtin (man alias)
 * @shell_info: Structure containing potential arguments. Used to maintain
 *   constant function prototype.
 *  Return: Always 0
 */

int _myalias_(cmd_t *shell_info_)
{
	int integer_ = 0;
	char *print_alia_ = NULL;
	custom_t *node_ = NULL;


	if (shell_info_->argn == 1)
	{
		node_ = shell_info_->aliaslist;
		while (node_)
		{
			print_alias_(node_);
			node_ = node_->next;
		}
		return (0);
	}
	integer_ = 1;
	while (shell_info_->args[integer_])
	{
		print_alia_ = custom_strchr(shell_info_->args[integer_], '=');
		if (print_alia_)
			set_alias_(shell_info_, shell_info_->args[integer_]);
		else
			print_alias_(search_node_by_prefix(shell_info_->aliaslist,
						shell_info_->args[integer_], '='));
		integer_++;
	}
	return (0);
}
