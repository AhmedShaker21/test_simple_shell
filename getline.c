#include "shell.h"

/**
 * sigint_Hand - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigint_Hand(attribute((unused))int sinum)
{
	_puts_f("\n");
	_puts_f("$ ");
	_putchar_f(BUF_FLUSH);
}

/**
 * _input_buffer - buffers chained commands
 * @shell_info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t _input_buffer(cmd_t *shell_info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!len)/* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_Hand);

#if ENABLE_GETLINE

		r = getline(buf, &len_p, stdin);
#else
		r = get_line_(shell_info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(buf)[r - 1] = '\0'; /* remove trailing newline */
					r--;
			}
			shell_info->count = 1;
			remove_cmts_(*buf);
			_build_hist_(shell_info, *buf, shell_info->histn++);
			{
				*len = r;
				shell_info->chain = buf;
			}
		}
	}
	return (r);
}

/**
 * _get_input - gets a line minus the newline
 * @shell_info: parameter struct
 * Return: bytes read
 */
ssize_t _get_input(cmd_t *shell_info)
{
	static char *buf; /
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(shell_info->line), *p;

	_putchar_f(BUF_FLUSH);
	r = _input_buffer(shell_info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_cha_(shell_info, buf, &j, i, len);

		for (; j < len; j++)
		{
			if (is_cha_(shell_info, buf, &j))
				break;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			shell_info->chaintype = CMD_NORMAL;
		}
		*buf_p = p;
		return (string_length(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * read_buffer - reads a buffer
 * @shell_info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buffer(cmd_t *shell_info, char *buf, size_t *i)
{
	ssize_t n = 0;

	if (*i)
		return (0);
	n = read(shell_info->readfd, buf, READ_BUF_SIZE);
	if (n >= 0)
		*i = n;
	return (n);
}

/**
 * get_line_ - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int get_line_(cmd_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buffer(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = custom_strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = resize_memory(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		custom_strncat(new_p, buffer + i, k - i);
	else
		custom_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
