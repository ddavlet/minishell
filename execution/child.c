#include "execution.h"

static int	manage_output_redir(t_executor *executor, int cmd_index)
{
	if (executor->cmds[cmd_index + 1] != NULL)
	{
		dup2(executor->pipe_fd[1], STDOUT_FILENO);
	}
	if (executor->cmds[cmd_index]->redirs != NULL)
	{
		if (executor->out_fd != STDOUT_FILENO)
			close(executor->out_fd);
		executor->out_fd = find_last_output_redir(executor, cmd_index);
		if (executor->out_fd == -1)
			return (-1);
	}
    printf("out_fd: %d\n", executor->out_fd);
	dup2(executor->out_fd, STDOUT_FILENO);
	if (executor->out_fd != STDOUT_FILENO)
		close(executor->out_fd);
	return (0);
}

static int	manage_input_redir(t_executor *executor, int cmd_index)
{
	if (executor->cmds[cmd_index]->redirs != NULL)
	{
		if (executor->in_fd != STDIN_FILENO)
			close(executor->in_fd);
		executor->in_fd = find_last_input_redir(executor, cmd_index);
		if (executor->in_fd == -1)
			return (-1);
	}
    printf("in_fd: %d\n", executor->in_fd);
	dup2(executor->in_fd, STDIN_FILENO);
	if (executor->in_fd != STDIN_FILENO)
		close(executor->in_fd);
	return (0);
}

int	child_process(t_executor *executor, int cmd_index)
{
    char    **argv;
    char    **envp;

    if (!executor || !executor->cmds || !executor->cmds[cmd_index])
	{
        return (-1);
	}
    printf("child_process\n");
    printf("pipe_fd[0]: %d\n", executor->pipe_fd[0]);
    printf("pipe_fd[1]: %d\n", executor->pipe_fd[1]);
	manage_input_redir(executor, cmd_index);
	close(executor->pipe_fd[1]);
	// close(executor->pipe_fd[0]);
    argv = executor->cmds[cmd_index]->argv;
    envp = executor->cmds[cmd_index]->env->envp;
	execute_command(argv, envp);
	return (0);
	manage_output_redir(executor, cmd_index);
}