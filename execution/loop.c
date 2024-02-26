#include "execution.h"

int	setup_pipe(t_executor *executor, int i)
{
	if (executor->cmds[i + 1] != NULL)
        return (0);
    if (pipe(executor->pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	execute_loop(t_executor *executor)
{
	int	    i;
    pid_t   pid;

	i = 0;
    pid = executor->pid;
	while (executor->cmds[i] != NULL)
	{
		if (setup_pipe(executor, i) == -1)
			return (-1);
        printf("loop.c: pipe_fd[0]: %d\n", executor->pipe_fd[0]);
        printf("loop.c: pipe_fd[1]: %d\n", executor->pipe_fd[1]);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0 && child_process(executor, i) == -1)
			return (-1);
1		else if (parent_process(executor, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}
