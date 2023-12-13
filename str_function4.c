#include "shell.h"

/**
 * **splits_string_words - splits a string into words.
 * @string_i: the input string
 * @delim_string: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splits_string_words(char *string_i, char *delim_string)
{
	int integer, g, k1, m1, num1 = 0;
	char **s1;

	if (string_i == NULL || string_i[0] == 0)
		return (NULL);
	if (!delim_string)
		delim_string = " ";
	for (integer = 0; string_i[integer] != '\0'; integer++)
		if (!delimin_is_found(string_i[integer], delim_string) &&
				(delimin_is_found(string_i[integer + 1]
						, delim_string) || !string_i[integer + 1]))
			num1++;
	if (num1 == 0)
		return (NULL);
	s1 = malloc((1 + num1) * sizeof(char *));
	if (!s1)
		return (NULL);
	for (integer = 0, g = 0; g < num1; g++)
	{
		while (delimin_is_found(string_i[integer], delim_string))
			integer++;
		k1 = 0;
		while (!delimin_is_found(string_i[integer + k1],
					delim_string) && string_i[integer + k1])
			k1++;
		s1[g] = malloc((k1 + 1) * sizeof(char));
		if (!s1[g])
		{
			for (k1 = 0; k1 < string_i; k1++)
				free(s1[k1]);
			free(s1);
			return (NULL);
		}
		for (m1 = 0; m1 < k1; m1++)
			s1[string_i][m1] = string_i[integer++];
		s1[g][m1] = 0;
	}
	s1[g] = NULL;
	return (s1);
}

/**
 * **splits_string_words2 - splits a string into words
 * @string_i: the input string
 * @delim_string: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **splits_string_words2(char *string_i, char delim_string)
{
	int integer, j, k1, m1, num1 = 0;
	char **s1;

	if (string_i == NULL || string_i[0] == 0)
		return (NULL);
	for (integer = 0; string_i[integer] != '\0'; integer++)
		if ((string_i[integer] != delim_string &&
					string_i[integer + 1] == delim_string) ||
				(!string_i[integer] || string_i[integer] != delim_string))
			num1++;
	if (num1 == 0)
		return (NULL);
	s1 = malloc((1 + num1) * sizeof(char *));
	if (!s1)
		return (NULL);
	integer = 0;
	j = 0;
	while (j < num1)
	{
		for (; string_i[integer] == delim_string; integer++)
			continue;
		k1 = 0;
		for (; string_i[integer + k1] != delim_string &&
				string_i[integer + k1] != '\0'; k1++)
			continue;
		s1[j] = malloc((k1 + 1) * sizeof(char));
		if (!s1[j])
		{
			k1 = 0;
			while (k1 < j)
			{
				free(s1[k1]);
				k1++;
			}
			free(s1);
			return (NULL);
		}
		m1 = 0;
		while (m1 < k1)
		{
			s1[j][m1] = string_i[integer++];
			m1++;
		}
		s1[j][m1] = '\0';
		j++;
	}
	s1[j] = NULL;
	return (s1);
}
