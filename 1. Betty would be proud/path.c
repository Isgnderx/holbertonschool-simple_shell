#include "shell.h"

/**
 * find_path - finds command in PATH
 * @cmd: command name
 *
 * Return: full path or NULL
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *dir;
	static char buffer[1024];

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	dir = strtok(path_copy, ":");

	while (dir)
	{
		sprintf(buffer, "%s/%s", dir, cmd);
		if (access(buffer, X_OK) == 0)
		{
			free(path_copy);
			return (buffer);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
