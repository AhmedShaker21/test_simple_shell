#include <shell.h>

custom_t *prepend_node(custom_t **head, const char *data, int value)
{
	custom_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(custom_t));
	if (!new_head)
		return (NULL);
	fill_memory((void *)new_head, 0, sizeof(custom_t));
	new_head->value = value;
	if (data)
	{
		new_head->data = dupl_func(data);
		if (!new_head->data)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * append_node - adds a node to the end of the list
 * @head: address of pointer to head node
 * @data: data field of node
 * @value: node index used by history
 *
 * Return: size of list
 */
custom_t *append_node(custom_t **head, const char *data, int value)
{
	custom_t *new_node, *node;

	if (!head)
		return (NULL);
	node = *head;
	new_node = malloc(sizeof(custom_t));
	if (!new_node)
		return (NULL);
	fill_memory((void *)new_node, 0, sizeof(custom_t));
	new_node->value = value;
	if (data)
	{
		new_node->data = dupl_func(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
 * printl_string - prints only the str element of a custom_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printl_string(const custom_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts_f(h->data ? h->data : "(nil)");
		_puts_f("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * remove_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int remove_at_index(custom_t **head, unsigned int index)
{
	custom_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->data);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->data);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_table - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_table(custom_t **head_ptr)
{
	custom_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->data);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

