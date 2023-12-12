#include "shell.h"
/**
 * _erratoint - converts a string to an integer
 * @str_: the string to be converted
 */

int _erratoint(char *str_)
{
	int index_ = 0;
	unsigned long int result_ = 0;

	if (*str_ == '+')
		str_++;
	while (str_[index_] != '\0')
	{
		if (str_[index_] >= '0' && str_[index_] <= '9')
		{
			result_ *= 10;
			result_ += (str_[index_] - '0');
			if (result_ > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		index_++;
	}
	return (result_);
}

/**
 * display_error_ - prints an error message
 * @information_: the parameter & return information struct
 * @error_string_: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void display_error_(cmd_t *information_, char *error_string_)
{
	_eputstr(information_->file);
	_eputstr(": ");
	print_decimal_(information_->errn, STDERR_FILENO);
	_eputstr(": ");
	_eputstr(information_->args[0]);
	_eputstr(": ");
	_eputstr(error_string_);
}

/**
 * print_decimal_ - function prints a decimal (integer) number (base 10)
 * @input_: the input
 * @fd_: the filedescriptor to write to
 * Return: number of characters printed
 */
int print_decimal_(int input_, int fd_)
{
	int (*_putchar_f)(char) = _putchar_f;
	int index_, count_ = 0;
	unsigned int absolute_value_, current_;

	if (fd_ == STDERR_FILENO)
		_putchar_f = _eputchr;
	if (input_ < 0)
	{
		absolute_value_ = -input_;
		_putchar_f('-');
		count_++;
	}
	else
		absolute_value_ = input_;
	current_ = absolute_value_;
	index_ = 1000000000;
	while (index_ > 1)
	{
		if (absolute_value_ / index_)
		{
			_putchar_f('0' + current_ / index_);
			count_++;
		}
		current_ %= index_;
		index_ /= 10;
	}
	_putchar_f('0' + current_);
	count_++;
	return (count_);
}

/**
 * transform_number_ - converter function, a clone of itoa
 * @number_: number
 * @base_: base
 * @flags_: argument flags
 * Return: string
 */
char *transform_number_(long int number_, int base_, int flags_)
{
	static char *character_array_;
	static char buffer_[50];
	char sign_ = 0;
	char *pointer_;
	unsigned long n_ = number_;

	if (!(flags_ & UNSIGNED_FLAG) && number_ < 0)
	{
		n_ = -number_;
		sign_ = '-';
	}
	character_array_ = flags_ & LOWER_CASE_FLAG ?
		"0123456789abcdef" : "0123456789ABCDEF";
	pointer_ = &buffer_[49];
	*pointer_ = '\0';
	while (n_ != 0)
	{
		*--pointer_ = character_array_[n_ % base_];
		n_ /= base_;
	}
	if (sign_)
		*--pointer_ = sign_;
	return (pointer_);
}

/**
 * remove_cmts_ - function replaces first instance of '#' with '\0'
 * @buffer_: address of the string to modify
 * Return: Always 0;
 */
void remove_cmts_(char *buffer_)
{
	int index_ = 0;

	while (buffer_[index_] != '\0')
	{
		if (buffer_[index_] == '#' && (!index_ || buffer_[index_ - 1] == ' '))
		{
			buffer_[index_] = '\0';
			break;
		}
		index_++;
	}
}
