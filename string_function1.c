#include "shell.h"

/**
 * string_length - returns the length of a string
 * @data: the string whose length to check
 */
int string_length(char *data)
{
	int c = 0;

	if (data == NULL)
		return (0);
	for (c = 0; *data != '\0'; c++)
	{
		*data++;
	}
	return (c);
}

/**
 * string_cmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first string
 * @str2: the second string
 */

int string_cmp(const char *str1, const char *str2)
{
	while (*str1 != NULL)
	{
		if (*str2 == '\0')
			return (1);
		if (*str2 < *str1)
			return (1);
		if (*str1 < *str2)
			return (-1);
		str1++;
		str2++;
	}
	if (*str2 != '\0')
		return (-1);
	else
		return (0);
}

char *string_start_with(const char *string, const char *word)
{
	while (*word)
		if (*word++ != *string++)
			return (NULL);
	return ((char *)string);
}

char *compine_str(char *first_w, char *second_w)
{
	char *full_w = first_w;

	while (*first_w)
		*first_w++;
	while (*second_w)
	{
		*first_w = *second_w;
		*second_w++;
		*first_w++;
	}
	return (full_w);
}
