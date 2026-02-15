#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 64

extern char **environ;

/**
 * get_path - gets PATH variable from environ
 *
 * Return: PATH string or NULL
 */
char *get_path(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * find_path - finds full path of command
 * @cmd: command
 *
 * Return: full path or NULL
 */
char *find_path(char *cmd)
{
	char *path_env, *path_copy, *dir;
	static char full_path[1024];

	if (strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}

	path_env = get_path();
	if (!path_env)
		return (NULL);

	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * main - simple shell with PATH support
 *
 * Return: 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;
	char *args[MAX_ARGS];
	char *token;
	char *cmd_path;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}

		line[strcspn(line, "\n")] = '\0';

		i = 0;
		token = strtok(line, " ");
		while (token && i < MAX_ARGS - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (args[0] == NULL)
			continue;

		cmd_path = find_path(args[0]);

		/* fork only if command exists */
		if (cmd_path == NULL)
		{
			fprintf(stderr, "./hsh: %s: not found\n", args[0]);
			continue;
		}

		pid = fork();
		if (pid == 0)
		{
			execve(cmd_path, args, environ);
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
