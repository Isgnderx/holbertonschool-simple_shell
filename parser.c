#include "shell.h"

/**
 * parse_line - splits input into arguments
 * @line: input line
 *
 * Return: array of arguments
 */
char **parse_line(char *line)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * MAX_ARGS);
	if (!args)
		return (NULL);

	token = strtok(line, " ");
	while (token && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}
