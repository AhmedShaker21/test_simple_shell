#include "shell.h"

/**
 * is_cha_ - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_cha_(cmd_t *info_, char *buf_, size_t *p_)
{
	size_t j_ = *p_;

	if (buf_[j_] == '|' && buf_[j_ + 1] == '|')
	{
		buf_[j_] = 0;
		j_++;
		info_->chaintype = COMMAND_CONDITIONAL_OR;
	}
	else if (buf_[j_] == '&' && buf_[j_ + 1] == '&')
	{
		buf_[j_] = 0;
		j_++;
		info_->chaintype = COMMAND_CONDITIONAL_AND;
	}
	else if (buf_[j_] == ';')
	{
		buf_[j_] = 0;
		info_->chaintype = COMMAND_CHAINING;
	}
	else
		return (0);
	*p_ = j_;
	return (1);
}

void check_cha_(cmd_t *info_, char *buf_, size_t *p_, size_t i_, size_t len_)
{
	size_t j_ = *p_;

	if (info_->chaintype == COMMAND_CONDITIONAL_AND)
	{
		if (info_->status_)
		{
			buf_[i_] = 0;
			j_ = len_;
		}
	}
	if (info_->chaintype == COMMAND_CONDITIONAL_OR)
	{
		if (!info_->status_)
		{
			buf_[i_] = 0;
			j_ = len_;
		}
	}
	*p_ = j_;
}

/**
 * rep_alia_ - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int rep_alia_(cmd_t *info_)
{
	int integer_;
	custom_t *node_;
	char *p_;

	for (integer_ = 0; integer_ < 10; integer_++)
	{
		node_ = search_node_by_prefix(info_->aliaslist, info_->args[0], '=');
		if (!node_)
			return (0);
		free(info_->args[0]);
		p_ = custom_strchr(node_->data, '=');
		if (!p_)
			return (0);
		p_ = dupl_func(p_ + 1);
		if (!p_)
			return (0);
		info_->args[0] = p_;
	}
	return (1);
}

/**
 * rep_var_ - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int rep_var_(cmd_t *info_)
{
	int integer_ = 0;
	custom_t *node_;

	for (integer_ = 0; info_->args[integer_]; integer_++)
	{
		if (info_->args[integer_][0] != '$' ||
				!info_->args[integer_][1])
			continue;
		if (!string_cmp(info_->args[integer_], "$?"))
		{
			rep_str_(&(info_->args[integer_]),
					dupl_func(transform_number_(info_->status_, 10, 0)));
			continue;
		}
		if (!string_cmp(info_->args[integer_], "$$"))
		{
			rep_str_(&(info_->args[integer_]),
					dupl_func(transform_number_(getpid(), 10, 0)));
			continue;
		}
		node_ = search_node_by_prefix(info_->envlist, &info_->args[integer_][1],
				'=');
		if (node_)
		{
			rep_str_(&(info_->args[integer_]),
					dupl_func(custom_strchr(node_->data, '=') + 1));
			continue;
		}
	rep_str_(&info_->args[integer_], dupl_func(""));
	}
	return (0);
}

/**
 * rep_str_ - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str_(char **old_, char *new_)
{
	free(*old_);
	*old_ = new_;
	return (1);
}
