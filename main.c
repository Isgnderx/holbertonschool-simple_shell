#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	int status;
	char *args[2];
	char *start;
	char *end;

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

		/* Trim leading spaces */
		start = line;
		while (*start == ' ' || *start == '\t')
			start++;

		/* Trim trailing spaces */
		end = start + strlen(start) - 1;
		while (end > start && (*end == ' ' || *end == '\t'))
		{
			*end = '\0';
			end--;
		}

		if (*start == '\0')
			continue;

		pid = fork();
		if (pid == 0)
		{
			args[0] = start;
			args[1] = NULL;

			execve(start, args, NULL);
			perror("./hsh");
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
