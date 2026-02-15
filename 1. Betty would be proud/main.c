#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			print_prompt();

		read = getline(&line, &len, stdin);
		if (read == -1)
			break;

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		args = parse_line(line);
		if (args && args[0])
		{
			if (strcmp(args[0], "exit") == 0)
			{
				free_args(args);
				break;
			}
			execute_command(args, argv[0]);
		}
		free_args(args);
	}
	free(line);
	return (0);
}
