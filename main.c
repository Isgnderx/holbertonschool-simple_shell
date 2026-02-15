#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t pid;
    int status;

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

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (line[0] == '\0')
            continue;

        pid = fork();
        if (pid == 0)
        {
            char *args[] = {line, NULL};

            execve(line, args, NULL);
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
