/**
 * custom_strncpy - Copies a portion of the source string
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @n: The number of characters to be copied.
 *
 * Return: A pointer to the concatenated string.
 */

char *custom_strncpy(char *destination,  char *source, int n)
{
	int i;

	for (i = 0; i < n - 1; i++)
	{
		destination[i] = source[i];
	}
	destination[n - 1] = '\0';
	return (destination);
}
/**
 * custom_strncat - Concatenates two strings.
 * @destination: The first string.
 * @source: The second string.
 * @n: The maximum number of bytes to be used.
 *
 * Return: A pointer to the concatenated string.
 */
char *custom_strncat(char *destination, const char *source, int n)
{
	int dest_len = 0;

	while (destination[dest_len] != '\0')
		dest_len++;
	for (int i = 0; source[i] != '\0' && i < n; i++)
	{
		destination[dest_len] = source[i];
		dest_len++;
	}
	if (dest_len < n)
		destination[dest_len] = '\0';
	return (destination);
}

/**
 * custom_strchr - Finds the first occurrence of a character in a string.
 * @haystack: The input string to search.
 * @needle: The target character to find.
 *
 * Return: A pointer to the first occurrence of 'needle' in 'haystack',
 *         or NULL if not found.
 */
char *custom_strchr(char *haystack, char needle)
{
	if (haystack == NULL)
		return (NULL);
	while (*haystack != '\0')
	{
		if (*haystack == needle)
			return (haystack);
		haystack++;
	}
	return (NULL);
}
