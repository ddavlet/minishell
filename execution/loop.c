#include "execution.h"

int	setup_pipe(t_executor *exec, int i)
{
	if (exec->cmds[i + 1] != NULL)
		return (0);
	if (pipe(exec->pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	execute_loop(t_executor *exec)
{
	int		i;

	i = 0;
	while (exec->cmds[i] != NULL)
	{
        setup_pipe(exec, i);
		exec->pid = fork();
		if (exec->pid == -1)
			return (-1);
		if (exec->pid == 0 && child_process(exec, i) == -1)
			return (-1);
		else if (parent_process(exec, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

		// ft_printf("DEBUG:loop.c: pipe_fd[0]: %d\n", exec->pipe_fd[0]);
		// ft_printf("DEBUG:loop.c: pipe_fd[1]: %d\n", exec->pipe_fd[1]);