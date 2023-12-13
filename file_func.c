#include "shell.h"
/**
 * _get_history_ - builds the history file path
 * @home: the home directory
 * Return: allocated string containing the history file path, or NULL
 */

char *_get_history_(cmd_t *shell_info)
{
	char *buffer, *direc;

	direc = find_environment_variable_(shell_info, "HOME=");
	if (!direc)
		return (NULL);
	buffer = malloc(sizeof(char) * (string_length(direc) +
				string_length(HIST_FILENAME) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	copy_string(buffer, direc);
	compine_str(buffer, "/");
	compine_str(buffer, HIST_FILENAME);
	return (buffer);
}

/**
 * _write_hist_ - creates a file, or appends to an existing file
 * @shell_info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int _write_hist_(cmd_t *shell_info)
{
	ssize_t file_dir;
	char *filename = _get_history_(shell_info);
	custom_t *node = NULL;

	if (!filename)
		return (-1);

	file_dir = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_dir == -1)
		return (-1);
	for (node = shell_info->histlist; node; node = node->next)
	{
		_putstrfd(node->data, file_dir);
		_putiofd('\n', file_dir);
	}
	_putiofd(BUF_FLUSH, file_dir);
	close(file_dir);
	return (1);
}
/**
 * read_hist - reads history from file
 * @shell_info: the parameter struct
 *
 * Return: histn on success, 0 otherwise
 */
int read_hist(cmd_t *shell_info)
{
	int i, last = 0, line_c = 0;
	ssize_t file_dir, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *filename = _get_history_(shell_info);

	if (!filename)
		return (0);

	file_dir = open(filename, O_RDONLY);
	free(filename);
	if (file_dir == -1)
		return (0);
	if (!fstat(file_dir, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(file_dir, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(file_dir);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			_build_hist_(shell_info, buffer + last, line_c++);
			last = i + 1;
		}
	if (last != i)
		_build_hist_(shell_info, buffer + last, line_c++);
	free(buffer);
	shell_info->histn = line_c;
	for (; shell_info->histn >= MAX_HIST_SIZE; shell_info->histn--)
		remove_at_index(&(shell_info->histlist), 0);
	renumber_hist_(shell_info);
	return (shell_info->histn);
}

/**
 * _build_hist_ - adds entry to a history linked list
 * @shell_info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_c: the history line_c, histn
 * Return: Always 0
 */
int _build_hist_(cmd_t *shell_info, char *buffer, int line_c)
{
	custom_t *node = NULL;

	if (shell_info->histlist)
		node = shell_info->histlist;
	append_node(&node, buffer, line_c);

	if (!shell_info->histlist)
		shell_info->histlist = node;
	return (0);
}

/**
 * renumber_hist_ - renumbers the history linked list after changes
 * @shell_info: Structure containing potential arguments. Used to maintain
 * Return: the new histn
 */
int renumber_hist_(cmd_t *shell_info)
{
	custom_t *node = shell_info->histlist;
	int i = 0;

	while (node)
	{
		node->value = i++;
		node = node->next;
	}
	return (shell_info->histn = i);
}
