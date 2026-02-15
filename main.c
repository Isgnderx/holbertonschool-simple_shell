#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 64

extern char **environ;

/**
 * main - simple shell with arguments support
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
		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (args[0] == NULL)
			continue;

		pid = fork();
		if (pid == 0)
		{
			execve(args[0], args, environ);
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
