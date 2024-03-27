#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pipes[3][2]; // File descriptors for the pipes
	pid_t pid;

	// Create pipes
	for (int i = 0; i < 3; i++)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	 for (int i = 0; i < 3; i++) {
        if ((pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
	return (0);
}
