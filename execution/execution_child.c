#include "execution.h"

static int assign_output_fd(t_executor *executor, int i)
{
    determine_output_fd(executor, i);
    if (executor->out_fd == -1)
        return (-1);
    dup2(executor->out_fd, STDOUT_FILENO);
    close(executor->out_fd);
    close(executor->pipe_fd[0]);
}

static int assign_input_fd(t_executor *executor, int i)
{
	determine_input_fd(executor);
	if (executor->in_fd == -1)
		return (-1);
    dup2(executor->in_fd, STDIN_FILENO);
    close(executor->in_fd);
}

int	child_process(t_executor *executor, int i)
{
	if (executor->cmds[i + 1] != NULL && assign_output_fd(executor, i) == -1)
		return (-1);
	if (assign_input_fd(executor, i) == -1)
        return (-1);
	if (execute_command(executor, i) == -1)
		return (-1);
	return (0);
}