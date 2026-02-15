#include "shell.h"

/**
 * trim - removes leading and trailing spaces
 * @str: input string
 * Return: trimmed string
 */
char *trim(char *str)
{
	char *end;

	while (*str == ' ' || *str == '\t')
		str++;

	if (*str == 0)
		return (str);

	end = str + strlen(str) - 1;

	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;

	*(end + 1) = '\0';

	return (str);
}

/**
 * execute_command - executes a command using fork and execve
 * @command: command to execute
 * @prog_name: name of shell program
 * @line_count: current line number
 */
void execute_command(char *command, char *prog_name, int line_count)
{
	pid_t pid;
	int status;
	char *args[2];

	if (access(command, X_OK) == -1)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_count, command);
		return;
	}

	pid = fork();

	if (pid == 0)
	{
		args[0] = command;
		args[1] = NULL;

		execve(command, args, environ);
		perror(prog_name);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
	}
}

/**
 * main - simple shell entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int line_count = 0;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		line_count++;

		line[strcspn(line, "\n")] = '\0';
		line = trim(line);

		if (line[0] == '\0')
			continue;

		execute_command(line, argv[0], line_count);
	}

	free(line);
	return (0);
}
