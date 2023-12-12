#include "shell.h"


int iscommand(cmd_t *shell_info, char *cmd)
{
	struct stat st;

	(void)shell_info;
	if (!cmd || stat(cmd, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

char *_dupchar(char *pstr, int start, int end)
{
	static char buf[1024];
	int i = 0, k = 0;

	i = start;
	while (i < end)
	{
		if (pstr[i] != ':')
			buf[k++] = pstr[i];
		i++
	}
	buf[k] = 0;
	return (buf);
}

char *fpath(cmd_t *shell_info, char *pstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *cmd;

	if (!pstr)
		return (NULL);
	if ((string_length(cmd) > 2) && string_start_with(cmd, "./"))
	{
		if (iscommand(shell_info, cmd))
			return (cmd);
	}
	for (i = 0; ; i++)
	{
		if (!pstr[i] || pstr[i] == ':')
		{
			cmd = _dupchar(pstr, curr_pos, i);
			if (!*cmd)
				compine_str(cmd, cmd);
			else
			{
				compine_str(cmd, "/");
				compine_str(cmd, cmd);
			}
			if (iscommand(shell_info, cmd))
				return (cmd);
			if (!pstr[i])
				break;
			curr_pos = i}
	}
	return (NULL);
}
