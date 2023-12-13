#include "shell.h"

/**
 *_eputstr - prints an input string
 * @string_c: the string to be printed
 *
 * Return: Nothing
 */
void _eputstr(char *string_c)
{
	int integer = 0;

	if (!string_c)
		return;
	for (integer = 0; string_c[integer] != '\0'; integer++)
	{
		_eputchr(string_c[integer]);
	}
}

/**
 * _eputchr - writes the character c to stderr
 * @char_eput: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchr(char char_eput)
{
	static int integer;
	static char buf[WRITE_BUF_SIZE];

	if (char_eput == BUF_FLUSH || integer >= WRITE_BUF_SIZE)
	{
		write(2, buf, integer);
		integer = 0;
	}
	if (char_eput != BUF_FLUSH)
		buf[integer++] = char_eput;
	return (1);
}

/**
 * _putiofd - writes the character c to given fd
 * @char_input: The character to print
 * @filede_scriptor: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putiofd(char char_input, int filede_scriptor)
{
	static int integer_num;
	static char bufer[WRITE_BUF_SIZE];

	if (char_input == BUF_FLUSH || integer_num >= WRITE_BUF_SIZE)
	{
		write(filede_scriptor, bufer, integer_num);
		integer_num = 0;
	}
	if (char_input != BUF_FLUSH)
		buf[integer_num++] = char_input;
	return (1);
}

/**
 *_putstrfd - prints an input string
 * @string_fd: the string to be printed
 * @filede_scriptor: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putstrfd(char *string_fd, int filede_scriptor)
{
	int integer_num = 0;

	if (!string_fd)
		return (0);
	while (*string_fd)
	{
		integer_num += _putiofd(*string_fd++, filede_scriptor);
	}
	return (i);
}
