#include "shell.h"

/**
 * inter_active_mode - returns true if shell is interactive mode
 * @first_info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */
int inter_active_mode(cmd_t *first_info)
{
	return (isatty(STDIN_FILENO) && first_info->readfile <= 2);
}

/**
 * delimin_is_found - checks if character is a delimeter
 * @char_check: the char to check
 * @delimin_check: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delimin_is_found(char char_check, char *delimin_check)
{
	while (*delimin_check)
		if (*delimin_check++ == char_check)
			return (1);
	return (0);
}

/**
 *check_alpha - checks for alphabetic character
 *@check_symbol: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */
int check_alpha(int check_symbol)
{
	if ((check_symbol >= 'a' && check_symbol <= 'z') ||
			(check_symbol >= 'A' && check_symbol <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *atoi_func - converts a string to an integer
 *@string_atoi: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */
int atoi_func(char *string_atoi)
{
	int integer, sign_integer = 1, flag_atoi = 0, out_put;
	unsigned int result_func = 0;

	integer = 0;
	while (string_atoi[integer] != '\0' && flag_atoi != 2)
	{
		if (string_atoi[integer] == '-')
			sign_integer *= -1;
		if (string_atoi[integer] >= '0' && string_atoi[integer] <= '9')
		{
			flag_atoi = 1;
			result_func *= 10;
			result_func += (string_atoi[integer] - '0');
		}
		else if (flag_atoi == 1)
			flag_atoi = 2;
		integer++;
	}
	if (sign_integer == -1)
		out_put = -result_func;
	else
		out_put = result_func;
	return (out_put);
}
