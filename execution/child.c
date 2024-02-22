#include "execution.h"

static int	assign_output_fd(t_executor *executor, int cmd_index)
{
	if (determine_output_fd(executor, cmd_index) == -1)
        return (-1);
	if (executor->out_fd == -1)
		return (-1);
	dup2(executor->out_fd, STDOUT_FILENO);
	close(executor->out_fd);
	close(executor->pipe_fd[0]);
	return (0);
}

static int	assign_input_fd(t_executor *executor, int cmd_index)
{
	if (determine_input_fd(executor, cmd_index) == -1)
        return (-1);
	if (executor->in_fd == -1)
		return (-1);
	dup2(executor->in_fd, STDIN_FILENO);
	close(executor->in_fd);
	return (0);
}

int	child_process(t_executor *executor, int cmd_index)
{
    char    **argv;
    char    **envp;

    if (!executor || !executor->cmds || !executor->cmds[cmd_index])
        return (-1);
    argv = executor->cmds[cmd_index]->argv;
    envp = executor->cmds[cmd_index]->env->envp;
	if (assign_output_fd(executor, cmd_index) == -1)
		return (-1);
	if (assign_input_fd(executor, cmd_index) == -1)
		return (-1);
	if (execute_command(argv, envp) == -1)
		return (-1);
	return (0);
}