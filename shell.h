#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 64

extern char **environ;

void print_prompt(void);
char **parse_line(char *line);
char *find_path(char *cmd);
void execute_command(char **args, char *prog_name);
void free_args(char **args);

#endif /* SHELL_H */
