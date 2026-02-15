#include "shell.h"

/**
 * free_args - frees args array
 * @args: arguments array
 */
void free_args(char **args)
{
	if (args)
		free(args);
}
