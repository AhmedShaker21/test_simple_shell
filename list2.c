#include "shell.h"

/**
 * _listlen - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t _listlen(const custom_t *h)
{
	size_t i = 0;
	const custom_t *node = h;

	for (node = h; node != NULL; node = node->next, i++)
	{
	}
	return (i);
}

/**
 * _listtostrs - returns an array of strings of the list->data
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **_listtostrs(custom_t *head)
{
	custom_t *node = head;
	size_t i = _listlen(head), j;
	char **strs;
	char *data;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (node != NULL)
	{
		data = malloc(string_length(node->data) + 1);
		if (!data)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		data = copy_string(data, node->data);
		strs[i] = data;
		i++;
		node = node->next;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * print_list_f - prints all elements of a custom_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_f(const custom_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts_f(transform_number_(h->num, 10, 0));
		_putchar_f(':');
		_putchar_f(' ');
		_puts_f(h->data ? h->data : "(nil)");
		_puts_f("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * search_node_by_prefix - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
custom_t *search_node_by_prefix(custom_t *node, char *prefix, char c)
{
	char *p = NULL;
	custom_t *current = node;

	for (current = node; current != NULL; current = current->next)
	{
		p = string_start_with(current->data, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (current);
	}
	return (NULL);
}
/**
 * _getnodei - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t _getnodei(custom_t *head, custom_t *node)
{
	size_t i = 0;
	custom_t *current = head;

	for (current = head; current != NULL; current = current->next, i++)
	{
		if (current == node)
			return (i);
	}
	return (-1);
}
