#include "execution.h"

static int	check_child_status(t_executor *exec)
{
	/*
		if (WIFEXITED(exec->status))
		{
			if (WEXITSTATUS(exec->status) == 0)
				return (0);
			else
				return (1);
		}
		else if (WIFSIGNALED(exec->status))
		{
			if (WTERMSIG(exec->status) == SIGINT)
				return (130);
			else if (WTERMSIG(exec->status) == SIGQUIT)
				return (131);
			else
				return (128 + WTERMSIG(exec->status));
		}
	*/
	ft_printf("DEBUG::parent.c: exec->status: %d\n", exec->status);   
	if (exec->status != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putendl_fd(strerror(exec->status), 2);
		return (-1);
	}
	return (0);
}

static int	close_file_descriptors(t_executor *exec, int cmd_index)
{
	if (!exec || !exec->cmds)
		return (-1);
	if (exec->in_fd != 0)
		close(exec->in_fd);
	exec->in_fd = pipe_fd[0];
	close(exec->pipe_fd[1]);
	if (exec->cmds[cmd_index + 1] == NULL)
	{
		waitpid(exec->pid, &(exec->status), 0);
		close(exec->in_fd);
	}
	return (0);
}

int	parent_process(t_executor *exec, int cmd_index)
{
	if (!exec)
		return (-1);
	ft_printf("DEBUG::parent_process\n");
	close_file_descriptors(exec, cmd_index);
	check_child_status(exec);
	return (0);
}
 