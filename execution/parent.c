#include "execution.h"

static int	check_child_status(t_executor *executor)
{
	/*
		if (WIFEXITED(executor->status))
		{
			if (WEXITSTATUS(executor->status) == 0)
				return (0);
			else
				return (1);
		}
		else if (WIFSIGNALED(executor->status))
		{
			if (WTERMSIG(executor->status) == SIGINT)
				return (130);
			else if (WTERMSIG(executor->status) == SIGQUIT)
				return (131);
			else
				return (128 + WTERMSIG(executor->status));
		}
	*/
    ft_printf("parent.c: executor->status: %d\n", executor->status);   
	if (executor->status != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putendl_fd(strerror(executor->status), 2);
		return (-1);
	}
	return (0);
}

static int	close_file_descriptors(t_executor *executor, int cmd_index)
{
	int		in_fd;
	int		*pipe_fd;
	pid_t	pid;
	t_cmd	**cmds;
    int		status;

	if (!executor || !executor->cmds)
		return (-1);
	cmds = executor->cmds;
	in_fd = executor->in_fd;
	pid = executor->pid;
	pipe_fd = executor->pipe_fd;
    status = executor->status;
	if (in_fd != 0)
		close(in_fd);
	in_fd = pipe_fd[0];
	close(pipe_fd[1]);
	if (cmds[cmd_index + 1] == NULL)
    {
        waitpid(pid, &status, 0);
		close(in_fd);
    }
    return (0);
}

int	parent_process(t_executor *executor, int cmd_index)
{
	if (!executor)
		return (-1);
    ft_printf("parent_process\n");
	close_file_descriptors(executor, cmd_index);
	check_child_status(executor);
	return (0);
}
