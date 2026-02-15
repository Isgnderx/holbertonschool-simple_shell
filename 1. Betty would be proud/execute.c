#include "shell.h"

/**
 * execute_command - executes a command
 * @args: arguments
 * @prog_name: program name
 */
void execute_command(char **args, char *prog_name)
{
	pid_t pid;
	char *full_path;

	full_path = find_path(args[0]);
	if (!full_path)
	{
		fprintf(stderr, "%s: 1: %s: not found\n",
			prog_name, args[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, environ);
		perror(prog_name);
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
