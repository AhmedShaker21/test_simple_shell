#include "shell.h"

/**
 *copy_string - copies a string
 *@place: the destination
 */
char *copy_string(char *place,  char *cpy_w)
{
	int i = 0;

	if (place == cpy_w || cpy_w == 0)
		return (place);
	for (i = 0 ; cpy_w[i] != '\0'; i++)
	{
		place[i] = cpy_w[i];
	}
	place[i] = 0;
	return (place);
}
/**
 * dupl_func - duplicates a string
 * @first_char: the string to duplicate
 */

char *dupl_func(const char *first_char)
{
	int k = 0;
	char *mem;
	int i = 0;

	if (first_char == NULL)
		return (NULL);

	for (; first_char[i]; i++)
		k++;

	mem = malloc(sizeof(char) * (k + 1));
	if (!mem)
		return (NULL);
	for (int i = 0; i < k; i++)
		mem[i] = first_char[i];
	return (mem);
}





/**
 * _putchar_f writes a character to the standard output
 * It takes a character as a parameter and returns 1 on success, -1 on error
*/
int _putchar_f(char ch)
{
	static int index;
	static char buffer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || index >= WRITE_BUF_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (ch != BUF_FLUSH)
	{
		buffer[index++] = ch;
	}
	return (1);
}

/**
 *_puts_f - prints an input string
 *@data: the string to be printed
 */
void _puts_f(char *data)
{
	int n;

	if (!data)
		return;

	for (n = 0; data[n] != '\0'; n++)
	{
		_putchar_f(data[n]);
	}
}
