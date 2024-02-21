#include "execution.h"

int	setup_pipe(t_executor executor, int i)
{
	if (executor->cmds[i + 1] != NULL)
	{
		if (pipe(executor->pipe_fd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

int	forkerror(t_executor executor)
{
	perror("fork");
	return (-1);
}

void	child_process(void)
{
	executor->in_fd = determine_input_fd(executor->cmds[i], executor->in_fd);
	if (executor->in_fd == -1)
		terminate_execution(executor);
	if (executor->cmds[i + 1] != NULL)
	{
		executor->out_fd = determine_output_fd(executor->cmds[i],
				executor->pipe_fd[1]);
		if (executor->out_fd == -1)
			terminate_execution(executor->cmds, executor->envp);
		dup2(executor->out_fd, STDOUT_FILENO);
		close(executor->out_fd);
		close(executor->pipe_fd[0]);
	}
	if (executor->in_fd != 0)
	{
		dup2(executor->in_fd, STDIN_FILENO);
		close(executor->in_fd);
	}
	execute_command(executor->cmds[i], executor->envp);
	exit(0);
}

void	parent_process(void)
{
	waitpid(pid, &status, 0);
	if (executor->in_fd != 0)
		close(executor->in_fd);
	executor->in_fd = executor->pipe_fd[0];
	close(executor->pipe_fd[1]);           
	if (executor->cmds[i + 1] == NULL)
		close(in_fd);
}

int	execute_loop(t_executor executor)
{
	int	i;

	i = 0;
	while (executor->cmds[i] != NULL)
	{
		if (setup_pipe(executor, i) == -1)
			return (-1);
		executor->pid = fork();
		if (executor->pid == -1)
			return (forkerror(executor));
		if (executor->pid == 0 && child_process() == -1)
			return (EXIT_FAILURE);
		else if (parent_process() == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (0);
}
